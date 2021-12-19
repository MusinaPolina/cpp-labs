#include "bmp.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static uint32_t padding(uint32_t x) {
  return x * 3 + (4 - (x * 3) % 4) % 4;
}

static void init_BMP(BMP *bmp, int h, int w) {
  assert(bmp);
  bmp->fileh = malloc(sizeof(BITMAPFILEHEADER));
  assert(bmp->fileh);
  bmp->infoh = malloc(sizeof(BITMAPINFOHEADER));
  assert(bmp->infoh);
  
  bmp->pixel_array = malloc(h * sizeof(unsigned char *));
  assert(bmp->pixel_array);
  for (int i = 0; i < h; i++) {
    bmp->pixel_array[i] = malloc(padding(w) * sizeof(unsigned char));
    assert(bmp->pixel_array[i]);
  }
}

void free_BMP(BMP *bmp) {
  assert(bmp);
  assert(bmp->infoh);
  
  int h = bmp->infoh->biHeight;
  
  for (int i = 0; i < h; i++) {
    assert(bmp->pixel_array[i]);
    free(bmp->pixel_array[i]);
  }
  free(bmp->pixel_array);
  free(bmp->fileh);
  free(bmp->infoh);
  free(bmp);
}


BMP* load_bmp(FILE *input_file) {
  assert(input_file);
  BITMAPFILEHEADER *fileh = malloc(sizeof(BITMAPFILEHEADER));
  assert(fileh);
  
  BITMAPINFOHEADER *infoh = malloc(sizeof(BITMAPINFOHEADER));
  assert(infoh);
  
  fread(fileh, sizeof(BITMAPFILEHEADER), 1, input_file);
  fread(infoh, sizeof(BITMAPINFOHEADER), 1, input_file);
  
  BMP *bmp = malloc(sizeof(BMP));
  assert(bmp);
  init_BMP(bmp, infoh->biHeight, infoh->biWidth);
  
  memcpy(bmp->fileh, fileh, sizeof(BITMAPFILEHEADER));
  memcpy(bmp->infoh, infoh, sizeof(BITMAPINFOHEADER));
  
  free(fileh);
  free(infoh);
 
  for (int i = 0; i < infoh->biHeight; i++) {
    fread(bmp->pixel_array[i], sizeof(unsigned char), padding(infoh->biWidth), input_file);
  }
  return bmp;
}



BMP* crop(BMP *bmp, int x, int y, int w, int h) {
  assert(bmp);

  BMP *curr = malloc(sizeof(BMP));
  assert(curr);
  
  uint32_t new_sz = h * padding(w);
  init_BMP(curr, h, w);
  
  memcpy(curr->fileh, bmp->fileh, sizeof(BITMAPFILEHEADER));
  memcpy(curr->infoh, bmp->infoh, sizeof(BITMAPINFOHEADER));
  
  curr->infoh->biHeight = h;
  curr->infoh->biWidth = w;
  
  curr->infoh->biSizeImage = new_sz;
  curr->fileh->bfSize = new_sz + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  
  for (int i = 0; i < h; i++) {
    memcpy(curr->pixel_array[i], bmp->pixel_array[i + x] + sizeof(unsigned char) * 3 * y, sizeof(unsigned char) * w * 3);
  }
  return curr;
}

BMP* rotate(BMP *bmp) {
  assert(bmp);

  BMP *curr = malloc(sizeof(BMP));
  assert(curr);
  
  int w = bmp->infoh->biHeight;
  int h = bmp->infoh->biWidth;
  
  uint32_t new_sz = h * padding(w);
  init_BMP(curr, h, w);
  
  memcpy(curr->fileh, bmp->fileh, sizeof(BITMAPFILEHEADER));
  memcpy(curr->infoh, bmp->infoh, sizeof(BITMAPINFOHEADER));
  
  curr->infoh->biHeight = h;
  curr->infoh->biWidth = w;
  
  curr->infoh->biSizeImage = new_sz;
  curr->fileh->bfSize = new_sz + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      memcpy(curr->pixel_array[i] + sizeof(unsigned char) * 3 * j, 
             bmp->pixel_array[j] + sizeof(unsigned char) * 3 * (h - 1 - i), sizeof(unsigned char) * 3);
    }
  }
  return curr;
}

void save_bmp(BMP *bmp, FILE *output_file) {
  assert(bmp);
  assert(output_file);
  fwrite(bmp->fileh, sizeof(BITMAPFILEHEADER), 1, output_file);
  fwrite(bmp->infoh, sizeof(BITMAPINFOHEADER), 1, output_file);
  
  for (int i = 0; i < bmp->infoh->biHeight; i++) {
    fwrite(bmp->pixel_array[i], sizeof(unsigned char), padding(bmp->infoh->biWidth), output_file);
  }
}
