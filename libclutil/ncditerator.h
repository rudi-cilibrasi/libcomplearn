#ifndef __NCDITERATOR_H
#define __NCDITERATOR_H

#include <complearn.h>

#include "ncditeratortype.h"
#include "directoryiterator.h"
#include "singlefileiterator.h"
#include "filenamelistiterator.h"

struct NCDIterator {
  enum NCDIteratorType iteratorType;
  struct NCDDirectoryIterator idir;
  struct NCDSingleFileIterator sdir;
  struct NCDFilenameListIterator fdir;
};

struct CLRichDatum {
  struct CLDatum datum;
  char *label_utf8;
};

void ncdiOpenIterator(struct NCDIterator *i, char *name,
                      enum NCDIteratorType type);
struct CLRichDatum ncdiNextIterator(struct NCDIterator *i,
                                enum NCDIteratorStepType s,
                                         int *succeeded);
void ncdiCloseIterator(struct NCDIterator *i);

#endif
