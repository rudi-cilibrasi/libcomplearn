#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "charholder.h"

#define STARTING_CHAR_SIZE 24

void newCharHolder(struct CharHolder *dh) {
  dh->alloc = STARTING_CHAR_SIZE;
  dh->val = malloc(sizeof(char)*dh->alloc);
  dh->count = 0;
}

void freeCharHolder(struct CharHolder *dh) {
  if (dh->val) {
    free(dh->val);
    dh->val = 0;
    dh->alloc = 0;
  }
  dh->count = 0;
}

void pushCharHolder(struct CharHolder *dh, char d) {
  if (!dh->val) {
    fprintf(stderr, "Cannot push onto freed CharHolder.\n");
    exit(1);
  }
  if (dh->count + 1 >= dh->alloc) {
    int nextStep = dh->alloc * 2;
    char *nextVal = malloc(sizeof(char) * nextStep);
    memcpy(nextVal, dh->val, sizeof(char) * dh->count);
    free(dh->val);
    dh->val = nextVal;
    dh->alloc = nextStep;
  }
  dh->val[dh->count] = d;
  dh->count += 1;
}

char *getCharHolderData(struct CharHolder *dh) {
  return dh->val;
}

uint32_t getCharHolderCount(struct CharHolder *dh) {
  return dh->count;
}
