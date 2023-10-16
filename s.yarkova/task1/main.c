#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ulimit.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	char options[] = "fdgispucvU:C:V:";  /* valid options */
	int c, invalid = 0, dflg = 0, fflg = 0, gflg = 0;
	char* f_ptr, * g_ptr;
	printf("argc equals %d\n", argc);
	struct rlimit ul;
	extern char** environ;
	char* buf = (char*)malloc(sizeof(char)*512);

	if (argc <= 1) {
		printf("too few arguments\n");
		exit(0);
	}

	while ((c = getopt(argc, argv, options)) != EOF) {

		switch (c) {
			case 'd':
				printf("current directory: %s\n", getcwd(buf, 511));
				break;

			case 'i':
				printf("real user id: %d\n", getuid());
				printf("real group id: %d\n", getgid());
				printf("effective user id: %d\n", geteuid());
				printf("effective group id: %d\n", getegid());
				break;

			case 's':
				setpgid(0,0);
				printf("The process became the leader of the group");
				break;

			case 'p':
				printf("Process ID: %d\n", getpid());
				printf("ID of the parent process: %d\n", getppid());
				printf("ID of the group for the process: %d \n", getpgrp());
				break;

			case 'u':	
				printf("strict restriction: %ld\n", ulimit(UL_GETFSIZE));
				break;

			case 'c':
				
				getrlimit(RLIMIT_CORE, &ul);
				printf("cur core file size: %ld\n", ul.rlim_cur);
				break;

			case 'v':
				while (*environ != NULL) {
					printf("%s\n", *environ);
					environ++;
				}
				break;

			case 'C':
				ul.rlim_cur = (rlim_t)atol(optarg);
				setrlimit(RLIMIT_CORE, &ul);
				printf("cur limit is %lld\n", ul.rlim_cur);
				break;

			case 'U':
				if (ulimit(UL_SETFSIZE, atoi(optarg)) == -1) {
					perror("");
				}
				break;

			case 'V':
				if (setenv(optarg, optarg, 2) == -1) {
					printf("there wasn't enough space in Wednesday's memory");
				}
				break;

			case '?':
				printf("invalid option is %c\n", optopt);
				invalid++;

		}

	}
	printf("dflg equals %d\n", dflg);
	if (fflg)
		printf("f_ptr points to %s\n", f_ptr);
	if (gflg)
		printf("g_ptr points to %s\n", g_ptr);
		printf("invalid equals %d\n", invalid);
		printf("optind equals %d\n", optind);
	if (optind < argc)
		printf("next parameter = %s\n", argv[optind]);
}