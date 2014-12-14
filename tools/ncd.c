#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <dirent.h>

#include <complearn.h>

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
	uint32_t cSizeCount[2];
	double *cSizeLine[2];
	char **labels[2];
	double **cSizeRect;
};

int isFile(char *filename);

extern const char *NCDHelpMessage;

void printHelp(FILE *whichFp) {
	fprintf(whichFp, "%s", NCDHelpMessage);
}

struct CLDatum readFile(char *filename);

struct NCDDirectoryIterator {
	char *dirname;
	DIR *dir;
};

void ncdiOpenDirectoryIterator(struct NCDDirectoryIterator *i,
char *dirname) {
	i->dirname = strdup(dirname);
	i->dir = opendir(i->dirname);
}

struct CLDatum ncdiNextDirectoryIterator(struct NCDDirectoryIterator *i,
int *succeeded) {
	for (;;) {
		struct dirent *d = readdir(i->dir);
		struct CLDatum result;
		result.length = 0;
		result.data = NULL;
		if (d == NULL) {
			*succeeded = 0;
			return result;
		}
		char *lastPart = d->d_name;
		char bigFilename[32768];
		sprintf(bigFilename, "%s/%s", i->dirname, lastPart);
		if (isFile(bigFilename)) {
			*succeeded = 1;
			return readFile(bigFilename);
		}
	}
}

void ncdiCloseDirectoryIterator(struct NCDDirectoryIterator *i) {
	free(i->dirname);
	i->dirname = NULL;
	closedir(i->dir);
	i->dir = NULL;
}

struct NCDFilenameListIterator {
	char *filename;
	FILE *fp;
};

#define DIRECTORY_ITERATOR 1
#define FILENAME_ITERATOR 2
struct NCDIterator {
	int iteratorType;
	struct NCDDirectoryIterator idir;
	struct NCDFilenameListIterator fdir;
};

struct CLDatum ncdiNextIterator(struct NCDIterator *i,
  int *succeeded) {
	switch (i->iteratorType) {
		case DIRECTORY_ITERATOR:
			return ncdiNextDirectoryIterator(&i->idir, succeeded);
	}
	struct CLDatum bad;
	bad.data = NULL;
	bad.length = 0;
	return bad;
}

void ncdiOpenIterator(struct NCDIterator *i, char *dirname, int itype) {
	switch (itype) {
		case DIRECTORY_ITERATOR:
			i->iteratorType = itype;
			ncdiOpenDirectoryIterator(&i->idir, dirname);
			return;
	}
}
void ncdiCloseIterator(struct NCDIterator *i) {
	switch (i->iteratorType) {
		case DIRECTORY_ITERATOR:
			ncdiCloseDirectoryIterator(&i->idir);
			return;
	}
}

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
	if (arg1isDir) {
		ncdiOpenIterator(&i1, arg1, DIRECTORY_ITERATOR);
		printf("Would do dir iterator.\n");
		for (;;) {
			int succeeded;
			struct CLDatum result = ncdiNextIterator(&i1, &succeeded);
			if (succeeded) {
				printf("%d ", result.length);
			} else {
				break;
			}
		}
	}
	if (arg2 == NULL) {
		
	}
}

uint64_t fileLength(char *filename)
{
	struct stat stbuf;
	int retval;
	retval = stat(filename, &stbuf);
	if (retval != 0) {
		fprintf(stderr, "Error, cannot stat %s\n", filename);
		printHelp(stderr);
		exit(1);
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
    fprintf(stderr, "Error, %s is a directory\n", filename);
		printHelp(stderr);
    exit(1);
  }
  return stbuf.st_size;
}

struct CLDatum clDatumCat(struct CLDatum a, struct CLDatum b) {
  struct CLDatum r;
  r.length = a.length + b.length;
  r.data = malloc(r.length);
  memcpy(r.data, a.data, a.length);
  memcpy(r.data+a.length, b.data, b.length);
  return r;
}

struct CLDatum readFile(char *filename)
{
  if (!isFile(filename)) {
    fprintf(stderr, "Error, %s is not a file\n", filename);
    exit(1);
  }
  struct CLDatum result;
  result.length = fileLength(filename);
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
	struct CLWorkContext work;
	if (ncdclo.isBasic) {
		doBasicBytes(&work, &ncdclo, comp, &clConfig, firstAxis, secondAxis);
		printf("Did bytes.\n");
		exit(0);
	}
  if (optind == argc-1 && !ncdclo.isSquare && !ncdclo.isRectangle && ncdclo.isDefaultCommand) {
		if (isFile(argv[optind])) {
			struct CLDatum input = readFile(argv[optind]);
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
	int needsSingleD = 0;
	int isTwoD = ncdclo.isSquare || ncdclo.isRectangle;
	if (!isTwoD) {
		if (ncdclo.isFilenameList) {
			fprintf(stderr, "Cannot use filename list without square or rectangle.\n");
			printHelp(stderr);
			exit(1);
		}
    struct CLDatum a = readFile(firstAxis);
    struct CLDatum b = readFile(secondAxis);
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
