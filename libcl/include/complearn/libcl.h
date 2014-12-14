#ifndef __LIBCL_H
#define __LIBCL_H

#include "compressor_base.h"

#define MAX_COMPRESSOR 1024

struct CompressorList {
	char *compressor_names[MAX_COMPRESSOR];
	struct CLCompressor *compressor[MAX_COMPRESSOR];
	int count;
};

void clAddCompressor(struct CLCompressor clc);

extern struct CompressorList clgs_CompressorList;
extern int haveInitted;

#endif
