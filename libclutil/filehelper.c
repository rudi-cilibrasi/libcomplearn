#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "clutil.h"

int isFile(char *filename)
{
	struct stat stbuf;
	int retval;
	retval = stat(filename, &stbuf);
	if (retval != 0) {
		fprintf(stderr, "Error, cannot stat %s\n", filename);
		exit(1);
	}
	return (stbuf.st_mode & S_IFMT) != S_IFDIR;
}

int isDir(char *filename)
{
	return !isFile(filename);
}

