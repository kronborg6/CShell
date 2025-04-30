#include "cd.h"
#include "cShell.h"
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
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
	strncpy(system_path, "/home/kronborg", system_path_max_len);
	system_path[PATH_MAX - 1] = '\0';
	return 0;
}
