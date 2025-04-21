#ifndef INPUT_H
#define INPUT_H

/* int getch(); */
/* void redraw(const char *buffer, int length, int index); */
char *input();
void deinitHistory();
void initHistory(int count);

#endif // INPUT_H
