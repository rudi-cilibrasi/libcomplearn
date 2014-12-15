#ifndef __DIRECTORYITERATOR_H
#define __DIRECTORYITERATOR_H

#include <dirent.h>

#include "ncditeratortype.h"

struct NCDDirectoryIterator {
  char *dirname;
  DIR *dir;
};

void ncdiOpenDirectoryIterator(struct NCDDirectoryIterator *i, char *dirname);
struct CLRichDatum ncdiNextDirectoryIterator(struct NCDDirectoryIterator *i,
                                enum NCDIteratorStepType s,
                                         int *succeeded);
void ncdiCloseDirectoryIterator(struct NCDDirectoryIterator *i);

#endif
