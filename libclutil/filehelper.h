#ifndef __FILEHELPER_H
#define __FILEHELPER_H

#include <complearn.h>

int isFile(char *filename);
int isDir(char *filename);
struct CLDatum clReadFile(char *filename);
uint64_t clFileLength(char *filename);

#endif
