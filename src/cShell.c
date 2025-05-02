#include "cShell.h"
#include "helpers.h"
#include <stddef.h>
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
		char **sliced;
		char **home_sliced;
		int sliced_path_len = 0;
		int home_sliced_len = 0;
		char *home = getenv("HOME");
		if (home != NULL) {
			sliced = splitString(system_path, '/');
			home_sliced = splitString(home, '/');

			while (sliced[sliced_path_len] != NULL) {
				sliced_path_len++;
			}
			while (home_sliced[home_sliced_len] != NULL) {
				home_sliced_len++;
			}
			if (sliced_path_len >= 2 && home_sliced_len >= 2) {
				if (strcmp(sliced[0], home_sliced[0]) == 0 && strcmp(sliced[1], home_sliced[1]) == 0) {
					/* system_path = "~"; */
				}
			}

			char *out = malloc(system_path_max_len);

			char *p = out;
			*p++ = '~';
			for (size_t i = 2; i < sliced_path_len; ++i) {
				*p++ = '/';
				size_t sliced_path_len = strlen(sliced[i]);
				memcpy(p, sliced[i], sliced_path_len);
				p += sliced_path_len;
			}
			*p = '\0';
			system_path = out;
		}
		/* printf("%s\n", system_path); */
		return 0;
	} else {
		return 1;
	}
}

void deinit_system_path() { free(system_path); }
