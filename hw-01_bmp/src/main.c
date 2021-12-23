#include "bmp.h"
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  assert(argc == 8);
  
  if (strcmp(argc[1], "crop-rotate")) {
    FILE *fin = fopen(argv[2], "rb");
    assert(fin);
  
    BMP *bmp = load_bmp(fin);
    fclose(fin);
  
    int x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);
    y = bmp->infoh.biHeight - y - h;
  
    BMP *crp = crop(bmp, x, y, w, h);
  
    BMP *rtt = rotate(crp);
  
    FILE *fout = fopen(argv[3], "wb");
    assert(fout);
  
    save_bmp(rtt, fout);
    fclose(fout);
  
    free_BMP(bmp);
    free_BMP(crp);
    free_BMP(rtt);
  } else {
    assert(0);
  }
  return 0;
}
