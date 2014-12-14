#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/complearn.h"

struct CompressorList clgs_CompressorList;
int haveInitted;

struct CLCompressor makeCLZLib(void);

void cliAddCompressor(struct CLCompressor clc);

struct CLCompressorConfig clNewConfig(void) {
  struct CLCompressorConfig result;
  memset(&result, 0, sizeof(result));
  return result;
}

void clErrorExit(void) {
	exit(1);
}

void ensureInitted(void) {
	if (haveInitted == 0) {
		fprintf(stderr, "Error, must call clInit before any other function.\n");
		clErrorExit();
	}
}


void clInit(void) {
	cliAddCompressor(makeCLZLib());
	haveInitted = 1;
}

void clListCompressors(char ***list, int *pcount) {
	ensureInitted();
	int count = clgs_CompressorList.count;
	*pcount = count;
	*list = malloc(sizeof(char *) * (count + 1));
	int i;
	for (i = 0; i < count; ++i) {
		(*list)[i] = strdup(clgs_CompressorList.compressor_names[i]);
	}
	(*list)[i] = NULL;
}

void cliAddCompressor(struct CLCompressor clc) {
	struct CLCompressor *c = malloc(sizeof(struct CLCompressor));
	*c = clc;
	int count = clgs_CompressorList.count;
	clgs_CompressorList.compressor[count] = c;
	clgs_CompressorList.compressor_names[count] = strdup(c->name());
	clgs_CompressorList.count += 1;
}

void clAddCompressor(struct CLCompressor clc) {
	ensureInitted();
  cliAddCompressor(clc);
}

struct CLCompressor clLoadCompressor(char *name) {
  int i;
	ensureInitted();
  for (i = 0; i < clgs_CompressorList.count; ++i) {
    if (strcmp(clgs_CompressorList.compressor_names[i], name) == 0) {
      return *clgs_CompressorList.compressor[i];
    }
  }
  fprintf(stderr, "Error, unknown compressor %s\n", name);
  clErrorExit();
  struct CLCompressor removeWarning;
  return removeWarning;
}

double clNCD(double a, double b, double ab) {
  double min = a, max = a;
  if (a < b) { max = b; }
  if (a > b) { min = b; }
  return (ab - min) / max;
}
