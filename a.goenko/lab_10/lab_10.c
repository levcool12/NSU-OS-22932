#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int subprocess = fork();
	if (subprocess == 0) {
		printf("The subprocess is working\n");
		execvp(argv[1], &argv[1]);
		exit(0);
	}
	else if (subprocess == -1) {
		perror("Subprocess not created");
		exit(1);
	}
	else {
		int exit_s;
		printf("The process is working\n");
		printf("Subprocess id: %d\n", subprocess);
		wait(&exit_s);
		printf("Subprocess completion code: %d\n", WEXITSTATUS(exit_s));
	}
	return 0;
}
