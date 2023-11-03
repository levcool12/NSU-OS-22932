#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
	int subprocess = fork();
	if (subprocess == 0) {
		printf("The subprocess is working\n");
		execlp("cat", "cat", "test.txt", NULL);
		exit(0);
	}
	else if (subprocess == -1) {
		perror("Subprocess not created");
		exit(1);
	}
	else {
		printf("The process is working\n");
		printf("Subprocess id: %d\n", subprocess);
		wait(0);
		printf("The work of the subprocess is finished");
	}
	return 0;
}
