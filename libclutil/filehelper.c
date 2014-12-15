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

struct CLDatum clReadFile(char *filename)
{
  struct CLDatum result;
  result.length = clFileLength(filename);
  result.data = malloc(result.length);
  FILE *fp = fopen(filename, "rb");
  int rv = fread(result.data, 1, result.length, fp);
  if (rv != result.length) {
    fprintf(stderr, "Error, short read\n");
    exit(1);
  }
  fclose(fp);
  return result;
}

uint64_t clFileLength(char *filename)
{
	struct stat stbuf;
	int retval;
	retval = stat(filename, &stbuf);
	if (retval != 0) {
		fprintf(stderr, "Error, cannot stat %s\n", filename);
		exit(1);
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
    fprintf(stderr, "Error, %s is a directory\n", filename);
    exit(1);
  }
  return stbuf.st_size;
}


