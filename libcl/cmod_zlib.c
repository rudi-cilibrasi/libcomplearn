#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "include/complearn/compressor_base.h"

static char *icl_zlib_name(void) {
  return "zlib";
}

static char *icl_zlib_description(void) {
  return "Lempel-Ziv zlib LZ77 Huffman used in gzip";
}

static char *icl_zlib_parameters(void) {
  return "\"level\"\n  numeric 1-9\n  defaults 9\n  specifying how much CPU to use to compress";
}

#include <zlib.h>

static char *icl_zlib_version(void) {
  return ZLIB_VERSION;
}

static int64_t icl_zlib_windowSize(void) {
  return 32768;
}

struct ZLibConfiguration {
  int32_t level;
};

void icl_zlib_updateConfiguration(struct CLCompressorConfig *conf, const char *k, const char *v)
{
  struct ZLibConfiguration *zlib_conf = (struct ZLibConfiguration *) conf;
  if (strcmp(k, "level") == 0 && v) {
    zlib_conf->level = atoi(v);
  }
}

static uint64_t icl_zlib_compressedSize(struct CLDatum input, struct CLCompressorConfig *conf) {
  if (input.length > 1e9) {
    fprintf(stderr, "zlib cannot compress files larger than 1GB in this mode\n");
    exit(1);
  }
  uLongf p = (uint32_t)(input.length*1.2) + 12;
  struct ZLibConfiguration *zlib_conf = (struct ZLibConfiguration *) conf;
  unsigned char *dbuff = (unsigned char*)malloc(p);
  int level = 9;
  if (zlib_conf && zlib_conf->level) {
    level = zlib_conf->level;
  }
  int s = compress2(dbuff,&p,input.data,input.length,level);
  if (s != 0) {    /* Z_OK */
    fprintf(stderr, "Unknown error: zlibBuff returned %d", s);
    exit(1);
  }
  uint64_t result = p;
  free(dbuff);
  return result;
}

struct CLCompressor makeCLZLib(void) {
  struct CLCompressor result;
  memset(&result, 0, sizeof(result));
  result.name = icl_zlib_name;
  result.version = icl_zlib_version;
  result.description = icl_zlib_description;
  result.parameters = icl_zlib_parameters;
  result.windowSize = icl_zlib_windowSize;
  result.updateConfiguration = icl_zlib_updateConfiguration;
  result.compressedSize = icl_zlib_compressedSize;
  return result;
}

