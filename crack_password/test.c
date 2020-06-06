#include <stdio.h>
#include <string.h>

int main(void) {

	char string[] = "hello";
	string[strlen(string)] = '5';
	// string[strlen(string)] = '\0';
	printf("string = %s\n", string);

	return 0;
}
