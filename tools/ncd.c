#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <compressor_base.h>

int main(int argc, char **argv)
{
  struct CLDatum cld;
  char *str = "aabaaa";
  int len = strlen(str);
  cld.length = len;
  cld.data = str;
  printf("%d\n",library_func1(cld));
  exit(0);
}
