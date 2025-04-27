#include "cShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *system_path = NULL;

int init() { return 0; }

int init_system_path() {
	long size;
	char *buf;
	size = pathconf(".", _PC_PATH_MAX);

	if ((buf = (char *)malloc((size_t)size)) != NULL) {
		system_path = getcwd(buf, (size_t)size);
		/* printf("%s\n", system_path); */
		return 0;
	} else {
		return 1;
	}
}

void deinit_system_path() { free(system_path); }
