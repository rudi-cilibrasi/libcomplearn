#ifndef __CHARHOLDER_H
#define __CHARHOLDER_H

#include <stdint.h>

struct CharHolder {
  uint32_t count, alloc;
  char *val;
};

void newCharHolder(struct CharHolder *ch);
void freeCharHolder(struct CharHolder *ch);
void pushCharHolder(struct CharHolder *ch, char c);
char *getCharHolderData(struct CharHolder *ch);
uint32_t getCharHolderCount(struct CharHolder *ch);

#endif

