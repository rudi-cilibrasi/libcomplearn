#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complearn.h>
#include "clutil.h"


void ncdiOpenDirectoryIterator(struct NCDDirectoryIterator *i,
char *dirname) {
	i->dirname = strdup(dirname);
	i->dir = opendir(i->dirname);
}

struct CLRichDatum ncdiNextDirectoryIterator(struct NCDDirectoryIterator *i,
                                enum NCDIteratorStepType s,
int *succeeded) {
	for (;;) {
		struct dirent *d = readdir(i->dir);
		struct CLRichDatum result;
		result.datum.length = 0;
		result.datum.data = NULL;
		if (d == NULL) {
			*succeeded = 0;
			return result;
		}
		char *lastPart = d->d_name;
		char bigFilename[32768];
		sprintf(bigFilename, "%s/%s", i->dirname, lastPart);
		if (isFile(bigFilename)) {
			*succeeded = 1;
			result.datum = clReadFile(bigFilename);
			return result;
		}
	}
}

void ncdiCloseDirectoryIterator(struct NCDDirectoryIterator *i) {
	free(i->dirname);
	i->dirname = NULL;
	closedir(i->dir);
	i->dir = NULL;
}

