//
// RUN COMMAND: gcc -g temp/input.c -o temp/run && ./temp/run
//
// TODO need to add a way to delete (show you delete)

#include <stdio.h>

int main() {
	FILE *fp = fopen("./.temp", "rb+");
	/* FILE *fp = fopen("./.temp", "w"); */

	/* fprintf(fp, "\nkronborg"); */
	/* /1* printf("hello\n"); *1/ */
	char online[200];
	while (1) {
		fscanf(fp, "%s", online);
		clearerr(fp);
		fseek(fp, 0, SEEK_SET);

		printf(": %s\n", online);
	}
	fclose(fp);
	/* printf("home dir: %s\n", home_path); */
	/* int i = 0; */
	/* printf("i is: %d\n", i); */
	/* i = 10; */
	/* printf("i is: %d\n", i); */
	return 0;
}
