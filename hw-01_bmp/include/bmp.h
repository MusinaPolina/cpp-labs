#pragma once
#include <stdint.h>
#include <stdio.h>

#pragma pack (push, 1)
typedef struct tagBITMAPFILEHEADER {
  uint16_t bfType;
  uint32_t bfSize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  uint32_t biSize;
  int32_t  biWidth;
  int32_t  biHeight;
  uint16_t  biPlanes;
  uint16_t  biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t  biXPelsPerMeter;
  int32_t  biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
} BITMAPINFOHEADER;

typedef struct tapPixel {
  unsigned char r, g, b;
} Pixel;

typedef struct tagBMP {
  BITMAPFILEHEADER fileh;
  BITMAPINFOHEADER infoh;
  Pixel **pixel_array;
} BMP;
#pragma pack (pop)


BMP * load_bmp(BMP *bmp, FILE *input_file);
BMP * crop(BMP *bmp, int x, int y, int w, int h);
BMP * rotate(BMP *bmp);
void save_bmp(BMP *bmp, FILE *output_file);

void free_pixel_array(BMP *bmp);
void free_BMP(BMP *bmp);
