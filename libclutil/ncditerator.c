#include <stdlib.h>
#include <stdio.h>
#include "clutil.h"

void ncdiOpenIterator(struct NCDIterator *i, char *name,
                      enum NCDIteratorType type) {
  switch (type) {
    case NCDIteratorTypeDirectory:
      ncdiOpenDirectoryIterator(&i->idir, name);
      break;
    default:
      fprintf(stderr, "Unrecognized iterator type: %d\n", type);
      exit(1);
  }
}

struct CLRichDatum ncdiNextIterator(struct NCDIterator *i,
                                enum NCDIteratorStepType s,
                                         int *succeeded) {
}

#if 0
struct CLDatum oldncdiNextIterator(struct NCDIterator *i,
  int *succeeded);

struct CLDatum oldncdiNextIterator(struct NCDIterator *i,
  int *succeeded) {
  switch (i->iteratorType) {
    case DIRECTORY_ITERATOR:
      return ncdiNextDirectoryIterator(&i->idir, 0, succeeded);
  }
  struct CLDatum bad;
  bad.data = NULL;
  bad.length = 0;
  return bad;
}

void oldncdiOpenIterator(struct NCDIterator *i, char *dirname, int itype) {
  switch (itype) {
    case DIRECTORY_ITERATOR:
      i->iteratorType = itype;
      ncdiOpenDirectoryIterator(&i->idir, dirname);
      return;
  }
}
void oldncdiCloseIterator(struct NCDIterator *i) {
  switch (i->iteratorType) {
    case DIRECTORY_ITERATOR:
      ncdiCloseDirectoryIterator(&i->idir);
      return;
  }
}

#endif
