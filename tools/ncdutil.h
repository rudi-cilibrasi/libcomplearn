#ifndef __NCDUTIL_H
#define __NCDUTIL_H

#include <stdint.h>

struct DoubleHolder {
  uint32_t count, alloc;
  double *val;
};

struct StringHolder {
  uint32_t count, alloc;
  char **val;
};

void newDoubleHolder(struct DoubleHolder *dh);
void freeDoubleHolder(struct DoubleHolder *dh);
void pushDoubleHolder(struct DoubleHolder *dh, double d);
double *getDoubleHolderData(struct DoubleHolder *dh);
uint32_t getDoubleHolderCount(struct DoubleHolder *dh);

void newStringHolder(struct StringHolder *dh);
void pushStringHolder(struct StringHolder *dh, const char *str);
void freeStringHolder(struct StringHolder *dh);
char **getStringHolderData(struct StringHolder *dh);
uint32_t getStringHolderCount(struct StringHolder *dh);

#endif
