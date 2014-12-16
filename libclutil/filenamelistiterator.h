#ifndef __FILENAMELISTITERATOR_H
#define __FILENAMELISTITERATOR_H

#include "charholder.h"

#include "ncditeratortype.h"

struct NCDFilenameListIterator {
  FILE *fp;
};

void ncdiOpenFilenameListIterator(struct NCDFilenameListIterator *i, char *filenamelistfilename);
struct CLRichDatum ncdiNextFilenameListIterator(struct NCDFilenameListIterator *i,
                                enum NCDIteratorStepType s,
                                         int *succeeded);
void ncdiCloseFilenameListIterator(struct NCDFilenameListIterator *i);

#endif
