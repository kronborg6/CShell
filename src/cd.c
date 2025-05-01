#include "cd.h"
#include "cShell.h"
#include "helpers.h"
#include <dirent.h>
#include <iso646.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int change_system_path(char *new_system_path) {
	if (new_system_path != NULL && system_path_max_len >= strlen(new_system_path)) {
		if (new_system_path[0] == '/') {
			DIR *dir = opendir(new_system_path);
			if (dir) {
				closedir(dir);
				system_path = new_system_path;
			} else {
				printf("path does not exites: %s\n", new_system_path);
			}
		} else if (new_system_path[0] == '.' && new_system_path[1] == '.') {
			char **slash;
			slash = splitString(system_path, '/');
			int len = 0;
			while (slash[len] != NULL) {
				len++;
			}
			char *out = malloc(system_path_max_len + 1);
			if (!out)
				return 2;

			// 4) Copy pieces in
			char *p = out;
			for (size_t i = 0; i < len - 1; ++i) {
				*p++ = '/';
				size_t len = strlen(slash[i]);
				memcpy(p, slash[i], len);
				p += len;
			}
			*p = '\0';
			for (size_t i = 0; slash[i] != NULL; ++i) {
				free(slash[i]);
			}
			free(slash);
			system_path = out;

		} else {
			char original[system_path_max_len];
			strncpy(original, system_path, system_path_max_len);
			original[PATH_MAX - 1] = '\0'; // ensure null-termination

			snprintf(system_path, PATH_MAX, "%s/%s", original, new_system_path);

			DIR *dir = opendir(system_path);
			if (dir) {
				closedir(dir);
			} else {
				strncpy(system_path, original, system_path_max_len);
				system_path[PATH_MAX - 1] = '\0';
				printf("path does not exites: %s\n", new_system_path);
			}
		}
		return 0;
	}
	char *home_dir = getenv("HOME");
	strncpy(system_path, home_dir, system_path_max_len);
	system_path[PATH_MAX - 1] = '\0';
	return 0;
}
