#ifndef __STRINGHOLDER_H
#define __STRINGHOLDER_H

#include <stdint.h>

struct StringHolder {
  uint32_t count, alloc;
  char **val;
};

void newStringHolder(struct StringHolder *dh);
void pushStringHolder(struct StringHolder *dh, const char *str);
void freeStringHolder(struct StringHolder *dh);
char **getStringHolderData(struct StringHolder *dh);
uint32_t getStringHolderCount(struct StringHolder *dh);

#endif
