#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "include/complearn.h"

static char *s_xzpath;

static char *icl_xz_name(void) {
  return "xz";
}

static char *icl_xz_description(void) {
  return "LZMA used in xz";
}

static char *icl_xz_parameters(void) {
  return "\"level\"\n  numeric 1-9\n  defaults 9\n  specifying how much CPU and memory to use to compress\n"
         "\"extreme\"\n  numeric 0-1\n  defaults 0\n  enable extreme CPU modes"
  ;
}

static char *icl_xz_version(void) {
  return "5.0.x";
}

static int64_t icl_xz_windowSize(void) {
  return 32768;
}

struct XZConfiguration {
  int32_t level;
  int32_t extreme;
};

void icl_xz_updateConfiguration(struct CLCompressorConfig *conf, const char *k, const char *v)
{
  struct XZConfiguration *xz_conf = (struct XZConfiguration *) conf;
  if (strcmp(k, "level") == 0 && v) {
    xz_conf->level = atoi(v);
  }
  if (strcmp(k, "extreme") == 0 && v) {
    xz_conf->extreme = atoi(v);
  }
}

static uint64_t icl_xz_compressedSize(struct CLDatum input, struct CLCompressorConfig *conf) {
  struct XZConfiguration *xz_conf = (struct XZConfiguration *) conf;
  int level = 9;
  int extreme = 0;
  if (xz_conf && xz_conf->level) {
    level = xz_conf->level;
  }
  if (xz_conf && xz_conf->extreme) {
    extreme = xz_conf->extreme;
  }
	char goodcmd[32768];
	sprintf(goodcmd, "%s -%d %s --compress", s_xzpath, level, extreme ? "-e":"");
  uint64_t result = runCommandCount(input, goodcmd);
  return result;
}

struct CLCompressor makeCLXZ(const char *xzpath) {
  struct CLCompressor result;
	s_xzpath = strdup(xzpath);
  memset(&result, 0, sizeof(result));
  result.name = icl_xz_name;
  result.version = icl_xz_version;
  result.description = icl_xz_description;
  result.parameters = icl_xz_parameters;
  result.windowSize = icl_xz_windowSize;
  result.updateConfiguration = icl_xz_updateConfiguration;
  result.compressedSize = icl_xz_compressedSize;
  return result;
}

