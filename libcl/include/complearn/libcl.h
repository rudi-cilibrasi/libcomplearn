#ifndef __LIBCL_H
#define __LIBCL_H

#include "compressor_base.h"

#define MAX_COMPRESSOR 1024

struct CompressorList {
	char *compressor_names[MAX_COMPRESSOR];
	struct CLCompressor *compressor[MAX_COMPRESSOR];
	int count;
};


void clInit(void);
void clAddCompressor(struct CLCompressor clc);
void clListCompressors(char ***list, int *pcount);
struct CLCompressor clLoadCompressor(char *name);
int clHasCompressor(char *name);

double clCompressedSize(struct CLCompressor compressor,
                        struct CLDatum cld,
                        struct CLCompressorConfig *config
);
double clNCD(double ca, double cb, double cab);

extern struct CompressorList clgs_CompressorList;
extern int haveInitted;

#endif
