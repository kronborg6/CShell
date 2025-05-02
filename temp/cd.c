#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	/* long size; */
	/* char *buf; */
	/* char *ptr; */
	/* size = pathconf(".", _PC_PATH_MAX); */
	char *foo = getenv("HOME");
	printf("%s\n", foo);

	/* if ((buf = (char *)malloc((size_t)size)) != NULL) { */
	/* 	ptr = getcwd(buf, (size_t)size); */
	/* 	printf("%s\n", ptr); */
	/* } */

	return 0;
}
