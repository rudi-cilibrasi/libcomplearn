#ifndef __COMPRESSOR_BASE_H
#define __COMPRESSOR_BASE_H

#include <stdint.h>

struct CLDatum {
  unsigned char *data;
  uint64_t length;
};

int library_func1(int a, int b);

#endif
