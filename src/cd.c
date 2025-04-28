#include "cd.h"
#include "cShell.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int change_system_path(char *new_system_path) {
	if (system_path_max_len >= strlen(new_system_path)) {
		DIR *dir = opendir(new_system_path);
		if (dir) {
			closedir(dir);
			system_path = new_system_path;
		} else {
			printf("path does not exites: %s\n", new_system_path);
		}
		return 0;
	}
	return 1;
}
