#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complearn.h>
#include "clutil.h"


void ncdiOpenSingleFileIterator(struct NCDSingleFileIterator *i,
char *filename) {
	i->filename = strdup(filename);
}

struct CLRichDatum ncdiNextSingleFileIterator(struct NCDSingleFileIterator *i,
                                enum NCDIteratorStepType s,
                                int *succeeded) {
  struct CLRichDatum result;
  memset(&result, 0, sizeof(result));
  if (i->filename) {
    if (s == NCDDataAndLabels || s == NCDNoLabels) {
      result.datum = clReadFile(i->filename);
    }
    if (s == NCDDataAndLabels || s == NCDNoData) {
      result.label_utf8 = strdup(i->filename);
    }
    free(i->filename);
    i->filename = NULL;
    *succeeded = 1;
  }
  else {
    *succeeded = 0;
  }
  return result;
}

void ncdiCloseSingleFileIterator(struct NCDSingleFileIterator *i) {
  if (i->filename) {
    free(i->filename);
    i->filename = NULL;
  }
}

