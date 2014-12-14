#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

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

int main(int argc, char **argv)
{
  struct CLDatum cld;
	struct NCDCommandLineOptions ncdclo;
  char *str = "aabaaa";
  int len = strlen(str);
	memset(&ncdclo, 0, sizeof(ncdclo));
	ncdclo.compressor = "zlib";
	ncdclo.isDefaultCommand = 1;
  cld.length = len;
  cld.data = (unsigned char *) str;
  printf("%d\n",library_func1(cld));
  int filename_list_flag = 0;
  int compressor_list_command_flag = 0;
  int help_command_flag = 0;
  char *cvalue = NULL;
	char *options[256];
	int option_count = 0;
  int index;
  int c;

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
	char *firstAxis = NULL, *secondAxis = NULL;
	if (ncdclo.isSquare) {
		if (optind >= argc) {
			fprintf(stderr, "Error, must supply at least one argument.\n");
			exit(1);
		}
		if (optind < argc-1) {
			fprintf(stderr, "Error, too many arguments.\n");
			exit(1);
		}
		firstAxis = strdup(argv[optind]);
		secondAxis = strdup(firstAxis);
	} else {
		if (optind >= argc-1) {
			fprintf(stderr, "Error, must supply at least two arguments.\n");
			exit(1);
		}
		if (optind < argc-2) {
			fprintf(stderr, "Error, too many arguments.\n");
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
			exit(1);
		}
	}
	printf("%s %s\n", firstAxis, secondAxis);

  exit(0);
}
