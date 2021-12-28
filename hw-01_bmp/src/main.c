#include "bmp.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "stego.h"

BMP * read_bmp(BMP *bmp, char *link) {
  FILE *fin = fopen(link, "rb");
  assert(fin);
  
  load_bmp(bmp, fin);
  fclose(fin);
  
  return bmp;
}

void write_bmp(BMP *bmp, char *link) {
  FILE *fout = fopen(link, "wb");
  assert(fout);
  
  save_bmp(bmp, fout);
  fclose(fout);
}

void read_key(char *link, Keys *key, BMP *bmp) {
  FILE *fin = fopen(link, "r");
  assert(fin);
  key->keys = malloc(sizeof(Key) * bmp->infoh.biSizeImage);
  assert(key);
  while (fscanf(fin, "%d %d %c", &key->keys[key->size].x, &key->keys[key->size].y, &key->keys[key->size].c) == 3) {
    key->keys[key->size].y = bmp->infoh.biHeight - 1 - key->keys[key->size].y;
    key->size++;
  }
  fclose(fin);
}


char * read_msg(char *link, BMP *bmp) {
  FILE *fin = fopen(link, "r");
  assert(fin);
  
  char *msg = malloc(sizeof(char) * bmp->infoh.biSizeImage);
  assert(msg);
  fgets(msg, bmp->infoh.biSizeImage, fin);
  
  fclose(fin);
    
  return msg;
}


void write_msg(char *msg, char *link) {
  FILE *fout = fopen(link, "w");
  assert(fout);
  
  fprintf(fout, "%s\n", msg);
  fclose(fout);
}


int main(int argc, char **argv) {
  assert(argc > 1);
  BMP bmp;
  Keys key;
  key.size = 0;
  
  if (strcmp(argv[1], "crop-rotate") == 0) {  
    assert(argc == 8);
    
    read_bmp(&bmp, argv[2]);
    int x = atoi(argv[4]), y = atoi(argv[5]);
    int w = atoi(argv[6]), h = atoi(argv[7]);
    y = bmp.infoh.biHeight - y - h;
  
    BMP *crp = crop(&bmp, x, y, w, h);
    BMP *rtt = rotate(crp);
    write_bmp(rtt, argv[3]);
  
    free_BMP(crp);
    free_BMP(rtt);
    
  } else if (strcmp(argv[1], "insert") == 0) {
    assert(argc == 6);
    
    read_bmp(&bmp, argv[2]);
    read_key(argv[4], &key, &bmp);
    char *msg = read_msg(argv[5], &bmp);
    
    insert(&bmp, &key, msg);   
    write_bmp(&bmp, argv[3]);
     
    free(msg);
    
  } else if (strcmp(argv[1], "extract") == 0) {
    assert(argc == 5);
    
    read_bmp(&bmp, argv[2]);
    read_key(argv[3], &key, &bmp);
    char *msg = extract(&bmp, &key);
    write_msg(msg, argv[4]);
    
    free(msg);
    
  } else {
    assert(0);
  }
  return 0;
}
