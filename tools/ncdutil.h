#ifndef __NCDUTIL_H
#define __NCDUTIL_H

#include <stdint.h>

struct DoubleHolder {
  uint32_t count, alloc;
  double *val;
};

void newDoubleHolder(struct DoubleHolder *dh);
void freeDoubleHolder(struct DoubleHolder *dh);
void pushDoubleHolder(struct DoubleHolder *dh, double d);
double *getDoubleHolderData(struct DoubleHolder *dh);
uint32_t getDoubleHolderCount(struct DoubleHolder *dh);

#endif
