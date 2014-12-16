#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complearn.h>
#include "clutil.h"


void ncdiOpenFilenameListIterator(struct NCDFilenameListIterator *i,
char *filename) {
	i->fp = fopen(filename, "rb");
}

struct CLRichDatum ncdiNextFilenameListIterator(struct NCDFilenameListIterator *i,
                                enum NCDIteratorStepType s,
int *succeeded) {
  struct CLRichDatum result;
  result.datum.data = NULL;
  result.datum.length = 0;
  char buf[65536]; // TODO: fix with charholder.h
  memset(buf, 0, sizeof(buf));
  if (i->fp) {
    char *resultLine = fgets(buf, sizeof(buf)-1, i->fp);
    if (resultLine) {
      strtok(resultLine, "\r\n");
      result.datum = clReadFile(resultLine);
      *succeeded = 1;
    } else {
      *succeeded = 0;
    }
    return result;
  }
  *succeeded = 0;
  return result;
}

void ncdiCloseFilenameListIterator(struct NCDFilenameListIterator *i) {
  if (i->fp) {
    fclose(i->fp);
    i->fp = NULL;
  }
}

