#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>

#include <complearn.h>
#include <clutil.h>

#include "ncdutil.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

static struct option long_options[] = {
{"compressor", required_argument, 0, 'c'},
{"info", no_argument, 0, 'i'},
{"option", required_argument, 0, 'o'},
{"square", no_argument, 0, 's'},
{"basic", no_argument, 0, 'b'},
{"rectangle", no_argument, 0, 'r'},
{"list-compressors", no_argument, 0, 'l'},
{"filename-list", no_argument, 0, 'f'},
{"help", no_argument, 0, 'h'},
{0, 0, 0, 0}
};

struct CLWorkContext {
	double cSizePoint;
	struct DoubleHolder cSizeLine[2];
	struct StringHolder labels[2];
	double **cSizeRect;
};

void printCompressedSize(double result);
struct CLDatum clDatumCat(struct CLDatum a, struct CLDatum b);

extern const char *NCDHelpMessage;

void printHelp(FILE *whichFp) {
	fprintf(whichFp, "%s", NCDHelpMessage);
}

struct NCDFilenameListIterator {
	char *filename;
	FILE *fp;
};

#define DIRECTORY_ITERATOR 1
#define FILENAME_ITERATOR 2
struct NCDCommandLineOptions {
	char *compressor;
	char *compressor_options[256];
	int optionCount;
	int isSquare;
	int isBasic;
	int isRectangle;
	int isFilenameList;
	int isDefaultCommand;
	int isInfoCommand;
	int isListCompressorsCommand;
	int isHelpCommand;
};

void doBasicBytes(struct CLWorkContext *work,
                  struct NCDCommandLineOptions *cliopt,
                  struct CLCompressor comp,
									struct CLCompressorConfig *clConfig,
             char *arg1, char *arg2) {
	struct NCDIterator i1, i2;
	if (arg1 == NULL) {
		fprintf(stderr, "Not enough arguments.\n");
		printHelp(stderr);
		exit(1);
	}
	int arg1isDir = isDir(arg1);
	if (arg2 == NULL) {
    if (arg1isDir) {
      ncdiOpenIterator(&i1, arg1, DIRECTORY_ITERATOR);
      for (;;) {
        int succeeded;
        struct CLRichDatum result = ncdiNextIterator(&i1, 0, &succeeded);
        if (succeeded) {
          printf("%lu ", result.datum.length);
        } else {
          break;
        }
      }
    } else {
      if (cliopt->isFilenameList) {
        printf("TODO\n");
      } else {
        struct CLDatum input = clReadFile(arg1);
        work->cSizePoint = comp.compressedSize(input, clConfig);
        printCompressedSize(work->cSizePoint);
        printf("\n");
        exit(0);
      }
    }
    fprintf(stderr, "Error, should not be here A1.\n");
    exit(1);
  }
	int arg2isDir = isDir(arg2);
  if (!cliopt->isFilenameList) {
    if (!arg1isDir && !arg2isDir) {
      struct CLDatum input1 = clReadFile(arg1);
      struct CLDatum input2 = clReadFile(arg2);
      struct CLDatum input = clDatumCat(input1, input2);
      work->cSizePoint = comp.compressedSize(input, clConfig);
      printCompressedSize(work->cSizePoint);
      printf("\n");
      exit(0);
    }
    if (arg1isDir && !arg2isDir) {
      // TODO
    }
  }
}

struct CLDatum clDatumCat(struct CLDatum a, struct CLDatum b) {
  struct CLDatum r;
  r.length = a.length + b.length;
  r.data = malloc(r.length);
  memcpy(r.data, a.data, a.length);
  memcpy(r.data+a.length, b.data, b.length);
  return r;
}

void printNCD(double result)
{
  if (result == floor(result) && result == ((double) ((int) result))) {
    printf("%d", (int) result);
  } else {
    printf("%f", result);
  }
}

void printCompressedSize(double result)
{
  if (result == floor(result) && result == ((double) ((int) result))) {
    printf("%d", (int) result);
  } else {
    printf("%f", result);
  }
}

int main(int argc, char **argv)
{
	struct NCDCommandLineOptions ncdclo;
	memset(&ncdclo, 0, sizeof(ncdclo));
	clInit();
	ncdclo.compressor = "zlib";
	ncdclo.isDefaultCommand = 1;
  int c;
  struct CLCompressor comp;
	if (clHasCompressor("xz")) {
		ncdclo.compressor = "xz";
	}

  opterr = 0;
  while (1) {
  int option_index = 0;
		c = getopt_long (argc, argv, "bc:fhilo:rs", long_options, &option_index);
		if (c == -1) {
			break;
		}

    switch (c)
      {
			case 'b':
				ncdclo.isBasic = 1;
				break;
      case 'c':
        ncdclo.compressor = strdup(optarg);
        break;
      case 'f':
				ncdclo.isFilenameList = 1;
        break;
      case 'h':
				ncdclo.isHelpCommand = 1;
				ncdclo.isDefaultCommand = 0;
				break;
      case 'i':
				ncdclo.isInfoCommand = 1;
				ncdclo.isDefaultCommand = 0;
				break;
			case 'l':
				ncdclo.isListCompressorsCommand = 1;
				ncdclo.isDefaultCommand = 0;
				break;
			case 'o':
				ncdclo.compressor_options[ncdclo.optionCount++] = strdup(optarg);
				break;
			case 'r':
				ncdclo.isRectangle = 1;
				ncdclo.isSquare = 0;
				break;
			case 's':
				ncdclo.isSquare = 1;
				ncdclo.isRectangle = 0;
				break;
      default:
        abort ();
      }
	}
  clInit();
  comp = clLoadCompressor(ncdclo.compressor);
  struct CLCompressorConfig clConfig;
  clConfig = clNewConfig();
	int i;
	for (i = 0; i < ncdclo.optionCount; i += 1) {
		char *cur = strdup(ncdclo.compressor_options[i]);
		char *fieldLeft = strtok(cur, "=");
		if (fieldLeft == NULL) { free(cur); continue; }
		char *fieldRight = strtok(NULL, "=");
		if (fieldRight == NULL) { fieldRight = ""; }
		comp.updateConfiguration(&clConfig, fieldLeft, fieldRight);
		free(cur);
	}
  if (ncdclo.isHelpCommand) {
		printHelp(stdout);
		exit(0);
	}
  if (ncdclo.isListCompressorsCommand) {
    char **clist;
    int count;
    clListCompressors(&clist, &count);
    printf("%d compressors:\n", count);
    int i;
    for (i = 0; i < count; ++i) {
      printf("%s\n", clist[i]);
    }
		printf("Default compressor: %s\n", ncdclo.compressor);
    exit(0);
  }
	char *firstAxis = NULL, *secondAxis = NULL;
	if (optind < argc) {
		firstAxis = argv[optind];
	}
	if (optind < argc-1) {
		secondAxis = argv[optind+1];
	}
  if (optind < argc-2) {
    fprintf(stderr, "Error: too many arguments\n");
    exit(1);
  }
	struct CLWorkContext work;
  newDoubleHolder(&work.cSizeLine[0]);
  newDoubleHolder(&work.cSizeLine[1]);
  newStringHolder(&work.labels[0]);
  newStringHolder(&work.labels[1]);
	if (ncdclo.isBasic) {
		doBasicBytes(&work, &ncdclo, comp, &clConfig, firstAxis, secondAxis);
		printf("Did bytes.\n");
		exit(0);
	}
  if (optind == argc-1 && !ncdclo.isSquare && !ncdclo.isRectangle && ncdclo.isDefaultCommand) {
		if (isFile(argv[optind])) {
			struct CLDatum input = clReadFile(argv[optind]);
			double result = comp.compressedSize(input, &clConfig);
			printCompressedSize(result);
			printf("\n");
			exit(0);
		} else {
		}
  }
	if (ncdclo.isSquare) {
		if (optind >= argc) {
			fprintf(stderr, "Error, must supply at least one argument.\n");
			printHelp(stderr);
			exit(1);
		}
		if (optind < argc-1) {
			fprintf(stderr, "Error, too many arguments.\n");
			printHelp(stderr);
			exit(1);
		}
		firstAxis = strdup(argv[optind]);
		secondAxis = strdup(firstAxis);
	} else {
		if (optind >= argc-1) {
			fprintf(stderr, "Error, must supply one or more arguments.\n");
			printHelp(stderr);
			exit(1);
		}
		if (optind < argc-2) {
			fprintf(stderr, "Error, too many arguments.\n");
			printHelp(stderr);
			exit(1);
		}
		firstAxis = strdup(argv[optind]);
		secondAxis = strdup(argv[optind+1]);
	}
	int isTwoD = ncdclo.isSquare || ncdclo.isRectangle;
	if (!isTwoD) {
		if (ncdclo.isFilenameList) {
			fprintf(stderr, "Cannot use filename list without square or rectangle.\n");
			printHelp(stderr);
			exit(1);
		}
    struct CLDatum a = clReadFile(firstAxis);
    struct CLDatum b = clReadFile(secondAxis);
    struct CLDatum ab = clDatumCat(a,b);
    if (ncdclo.isBasic) {
      double result = comp.compressedSize(ab, &clConfig);
      printCompressedSize(result);
      printf("\n");
      exit(0);
    } else {
      double ca = comp.compressedSize(a, &clConfig);
      double cb = comp.compressedSize(b, &clConfig);
      double cab = comp.compressedSize(ab, &clConfig);
      double ncd = clNCD(ca, cb, cab);
      printNCD(ncd);
      printf("\n");
      exit(0);
    }
	}
	printf("%s %s\n", firstAxis, secondAxis);

  exit(0);
}
