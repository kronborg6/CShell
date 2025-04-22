#ifndef HISTORY_H
#define HISTORY_H

extern char **history;
extern int maxleng;
extern int historyLen;
extern int max_history_item_len;

void deinitHistory();
void initHistory(int count);
void appendHistory(char *string);

#endif // !HISTORY_H
