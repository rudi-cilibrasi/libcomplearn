#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doubleholder.h"

#define STARTING_DOUBLE_SIZE 16

void newDoubleHolder(struct DoubleHolder *dh) {
  dh->alloc = STARTING_DOUBLE_SIZE;
  dh->val = malloc(sizeof(double)*dh->alloc);
  dh->count = 0;
}

void freeDoubleHolder(struct DoubleHolder *dh) {
  if (dh->val) {
    free(dh->val);
    dh->val = 0;
    dh->alloc = 0;
  }
  dh->count = 0;
}

void pushDoubleHolder(struct DoubleHolder *dh, double d) {
  if (!dh->val) {
    fprintf(stderr, "Cannot push onto freed DoubleHolder.\n");
    exit(1);
  }
  if (dh->count + 1 >= dh->alloc) {
    int nextStep = dh->alloc * 2;
    double *nextVal = malloc(sizeof(double) * nextStep);
    memcpy(nextVal, dh->val, sizeof(double) * dh->count);
    free(dh->val);
    dh->val = nextVal;
    dh->alloc = nextStep;
  }
  dh->val[dh->count] = d;
  dh->count += 1;
}

double *getDoubleHolderData(struct DoubleHolder *dh) {
  return dh->val;
}

uint32_t getDoubleHolderCount(struct DoubleHolder *dh) {
  return dh->count;
}
