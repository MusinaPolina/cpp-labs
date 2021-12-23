#include "bmp.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


static uint32_t padding(uint32_t x) {
  return (4 - (x * 3) % 4) % 4;
}


static void init_BMP(BMP *bmp, int h, int w) {
  assert(bmp);

  bmp->pixel_array = malloc(h * sizeof(Pixel *));
  assert(bmp->pixel_array);
  
  for (int i = 0; i < h; i++) {
    bmp->pixel_array[i] = malloc(w * sizeof(Pixel));
    assert(bmp->pixel_array[i]);
  }
}


void free_BMP(BMP *bmp) {
  assert(bmp);
  
  int h = bmp->infoh.biHeight;
  
  for (int i = 0; i < h; i++) {
    assert(bmp->pixel_array[i]);
    free(bmp->pixel_array[i]);
  }
  free(bmp->pixel_array);
  free(bmp);
}


BMP* load_bmp(FILE *input_file) {
  assert(input_file);
  
  BMP *bmp = malloc(sizeof(BMP));
  assert(bmp);
  
  fread(&bmp->fileh, sizeof(BITMAPFILEHEADER), 1, input_file);
  fread(&bmp->infoh, sizeof(BITMAPINFOHEADER), 1, input_file);
  
  init_BMP(bmp, bmp->infoh.biHeight, bmp->infoh.biWidth);
 
  for (int i = 0; i < bmp->infoh.biHeight; i++) {
    fread(bmp->pixel_array[i], sizeof(Pixel), bmp->infoh.biWidth, input_file);
    assert(!fseek(input_file, padding(bmp->infoh.biWidth), SEEK_CUR));
  }
  return bmp;
}


static BMP * header_copy(BMP *bmp, int h, int w) {
  BMP *curr = malloc(sizeof(BMP));
  assert(curr);
  
  uint32_t new_sz = h * w * 3 + padding(w);
  
  curr->fileh = bmp->fileh;
  curr->infoh = bmp->infoh;
  
  curr->infoh.biHeight = h;
  curr->infoh.biWidth = w;
  
  curr->infoh.biSizeImage = new_sz;
  curr->fileh.bfSize = new_sz + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  
  init_BMP(curr, h, w);
  
  return curr;
}


BMP* crop(BMP *bmp, int x, int y, int w, int h) {
  assert(bmp);
  
  BMP *curr = header_copy(bmp, h, w);
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      curr->pixel_array[i][j] = bmp->pixel_array[i + y][j + x];
    }
  }
  return curr;
}

BMP* rotate(BMP *bmp) {
  assert(bmp);
  
  int w = bmp->infoh.biHeight;
  int h = bmp->infoh.biWidth;
  
  BMP *curr = header_copy(bmp, h, w);
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      curr->pixel_array[i][j] = bmp->pixel_array[j][h - 1 - i];
    }
  }
  return curr;
}

void save_bmp(BMP *bmp, FILE *output_file) {
  assert(bmp);
  assert(output_file);
  
  fwrite(&bmp->fileh, sizeof(BITMAPFILEHEADER), 1, output_file);
  fwrite(&bmp->infoh, sizeof(BITMAPINFOHEADER), 1, output_file);
  
  for (int i = 0; i < bmp->infoh.biHeight; i++) {
    fwrite(bmp->pixel_array[i], sizeof(Pixel), bmp->infoh.biWidth, output_file);
    fwrite("000", sizeof(char), padding(bmp->infoh.biWidth), output_file);
  }
}
