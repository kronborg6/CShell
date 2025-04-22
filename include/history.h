#ifndef HISTORY_H
#define HISTORY_H

#include <stddef.h>
extern char **history;
extern int maxleng;
extern int historyLen;
extern int max_history_item_len;

void deinitHistory();
void initHistory(int count);
void appendHistory(char *string);
void appandfile(const char *command, size_t len);
void createFileIfNotExist();
#endif // !HISTORY_H
