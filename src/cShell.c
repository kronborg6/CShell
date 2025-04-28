#include "cShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *system_path = NULL;
long int system_path_max_len = 0;

int init() { return 0; }

int init_system_path() {
	/* long size; */
	char *buf;
	system_path_max_len = pathconf(".", _PC_PATH_MAX);

	if ((buf = (char *)malloc((size_t)system_path_max_len)) != NULL) {
		system_path = getcwd(buf, (size_t)system_path_max_len);
		/* printf("%s\n", system_path); */
		return 0;
	} else {
		return 1;
	}
}

void deinit_system_path() { free(system_path); }
