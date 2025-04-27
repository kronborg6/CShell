#ifndef CSHELL_H
#define CSHELL_H

#include <stdbool.h>

extern bool run;
extern char *system_path;

int init_system_path();
void deinit_system_path();

#endif // !CSHELL_H
