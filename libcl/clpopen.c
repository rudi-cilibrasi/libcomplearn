#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "include/complearn/cltop.h"
#include "clpopen.h"

char *absolutePathForCommand(const char *cmd) {
	int cmdlen = strlen(cmd);
	char *goodcmd = malloc(cmdlen + 128);
	sprintf(goodcmd, "which %s", cmd);
	FILE *fp = popen(goodcmd, "r");
	char buf[32768];
	int rv;
	char *result = NULL;
	if ((rv = fread(buf, 1, sizeof(buf)-1, fp)) > 0) {
		buf[rv] = 0;
		result = strdup(buf);
		strtok(result, "\r\n");
	}
	free(goodcmd);
	pclose(fp);
	return result;
}

int64_t runCommandCount(struct CLDatum inp, const char *cmd) {
	char tmpbuf[256];
	strcpy(tmpbuf, "/tmp/complearn.XXXXXX");
	mktemp(tmpbuf);
	FILE *fp = fopen(tmpbuf, "wb");
	fwrite(inp.data, 1, inp.length, fp);
	fclose(fp);
	int cmdlen = strlen(cmd);
	char *goodcmd = malloc(cmdlen + 128);
	sprintf(goodcmd, "%s <%s", cmd, tmpbuf);
	fp = popen(goodcmd, "r");
	char buf[8192];
	int rv;
	uint64_t count = 0;
	while ((rv = fread(buf, 1, sizeof(buf), fp)) > 0) {
		count += rv;
	}
	unlink(tmpbuf);
	free(goodcmd);
	if (rv < 0) {
		return -1;
	}
	pclose(fp);
	return count;
}

