#include "bmp.h"
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  assert(argc == 8);
  
  FILE *fin = fopen(argv[2], "rb");
  assert(fin);
  
  BMP *bmp = load_bmp(fin);
  fclose(fin);
  
  //printf("loaded\n");
  int x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);
  y = bmp->infoh.biHeight - 1 - y;
  
  BMP *crp = crop(bmp, x, y, w, h);
  
  //crp = crp;
  //printf("croped\n");
  
  BMP *rtt = rotate(crp);
  
  //rtt = rtt;
  //printf("rotated\n");
  
  FILE *fout = fopen(argv[3], "wb");
  assert(fout);
  
  save_bmp(rtt, fout);
  fclose(fout);
  
  //printf("saved\n");
  
  free_BMP(bmp);
  free_BMP(crp);
  free_BMP(rtt);
  
  return 0;
}
