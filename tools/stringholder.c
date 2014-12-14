#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ncdutil.h"

#define STARTING_STRING_SIZE 16

void newStringHolder(struct StringHolder *dh) {
  dh->alloc = STARTING_STRING_SIZE;
  dh->val = malloc(sizeof(char *)*dh->alloc);
  dh->count = 0;
}

void freeStringHolder(struct StringHolder *dh) {
  if (dh->val) {
    int i;
    for (i = 0; i < dh->alloc; ++i) {
      free(dh->val[i]);
      dh->val[i] = 0;
    }
    free(dh->val);
    dh->val = 0;
    dh->alloc = 0;
  }
  dh->count = 0;
}

void pushStringHolder(struct StringHolder *dh, const char *str) {
  if (!dh->val) {
    fprintf(stderr, "Cannot push onto freed StringHolder.\n");
    exit(1);
  }
  if (dh->count + 1 >= dh->alloc) {
    int nextStep = dh->alloc * 2;
    char **nextVal = malloc(sizeof(char *) * nextStep);
    memcpy(nextVal, dh->val, sizeof(char *) * dh->count);
    free(dh->val);
    dh->val = nextVal;
    dh->alloc = nextStep;
  }
  dh->val[dh->count] = strdup(str);
  dh->count += 1;
}

char **getStringHolderData(struct StringHolder *dh) {
  return dh->val;
}

uint32_t getStringHolderCount(struct StringHolder *dh) {
  return dh->count;
}
