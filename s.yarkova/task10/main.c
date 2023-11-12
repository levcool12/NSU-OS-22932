#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char* argv[]) {

	pid_t pid = fork();
	printf("Pid process %d\n", pid);

	int status;
	if (argc <= 1) {
		printf("too few arguments");
		exit(1);
	}

	if (pid == 0) {
		printf("pid child process: %d\n", getpid());
		execvp(argv[1],argv+1);
		exit(0);
	}
	else if (pid > 0) {
		waitpid(pid, &status, 0);
		printf("Status process: %d\n", WEXITSTATUS(status));
	}
	else perror("child process not created\n");
	return 0;
}