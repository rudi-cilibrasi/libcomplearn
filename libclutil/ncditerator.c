#include <stdlib.h>
#include <stdio.h>
#include "clutil.h"

void ncdiOpenIterator(struct NCDIterator *i, char *name,
                      enum NCDIteratorType type) {
  switch (type) {
    case NCDIteratorTypeSingleFile:
      ncdiOpenSingleFileIterator(&i->sdir, name);
      break;
    case NCDIteratorTypeDirectory:
      ncdiOpenDirectoryIterator(&i->idir, name);
      break;
    case NCDIteratorTypeFilenameList:
      ncdiOpenFilenameListIterator(&i->fdir, name);
      break;
    default:
      fprintf(stderr, "Unrecognized iterator type: %d\n", type);
      exit(1);
  }
  i->iteratorType = type;
}

struct CLRichDatum ncdiNextIterator(struct NCDIterator *i,
                                enum NCDIteratorStepType s,
                                         int *succeeded) {
  struct CLRichDatum result;
  switch (i->iteratorType) {
    case NCDIteratorTypeDirectory:
      result = ncdiNextDirectoryIterator(&i->idir, s, succeeded);
      break;
    case NCDIteratorTypeSingleFile:
      result = ncdiNextSingleFileIterator(&i->sdir, s, succeeded);
      break;
    case NCDIteratorTypeFilenameList:
      result = ncdiNextFilenameListIterator(&i->fdir, s, succeeded);
      break;
    default:
      fprintf(stderr, "Unrecognized iterator type: %d\n", i->iteratorType);
      exit(1);
  }
  return result;
}

void ncdiCloseIterator(struct NCDIterator *i) {
  switch (i->iteratorType) {
    case NCDIteratorTypeSingleFile:
      ncdiCloseSingleFileIterator(&i->sdir);
      return;
    case NCDIteratorTypeFilenameList:
      ncdiCloseFilenameListIterator(&i->fdir);
      return;
    case NCDIteratorTypeDirectory:
      ncdiCloseDirectoryIterator(&i->idir);
      return;
    default:
      fprintf(stderr, "Unrecognized iterator type: %d\n", i->iteratorType);
      exit(1);
  }
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
