#ifndef __SINGLEFILEITERATOR_H
#define __SINGLEFILEITERATOR_H

#include "ncditeratortype.h"

struct NCDSingleFileIterator {
  char *filename;
};

void ncdiOpenSingleFileIterator(struct NCDSingleFileIterator *i, char *dirname);
struct CLRichDatum ncdiNextSingleFileIterator(struct NCDSingleFileIterator *i,
                                enum NCDIteratorStepType s,
                                         int *succeeded);
void ncdiCloseSingleFileIterator(struct NCDSingleFileIterator *i);

#endif
