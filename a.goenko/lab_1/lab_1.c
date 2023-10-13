#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>

int getopt(int argc, char* const* argv, const char* optstring);

typedef struct ar {
	char c;
	char** v;
}argum;
int invalid = 0;
argum buff[10000];
extern char* optarg;
extern int optind, opterr, optopt;

int main(int argc, char* argv[], char** envp) {
	char options[] = "dispucvU:C:V:";
	int c;
	int j = 0;
	struct rlimit a;
	printf("argc equals %d\n", argc);
	while ((c = getopt(argc, argv, options)) != EOF) {
		if (c == '?') {
			printf("invalid option is %c\n", optopt);
			invalid++;
		}
		else {
			buff[j].c = c;
			if (c == 'U' || c == 'C') {
				buff[j].v = malloc(2*sizeof(char));
				for(int i = 0; i < strlen(argv[optind-1]); i++)
					if (argv[optind-1][i] > 57 || argv[optind-1][i] < 48) {
							printf("invalid option is %c\n", c);
							invalid++;
							break;
						}
				if (invalid != 0)
					break;
				else {
					buff[j].v[0] = malloc((strlen(argv[optind-1])+1)*sizeof(char));
					strcpy(buff[j].v[0], argv[optind-1]);
				}
			}
			else 
				if (c == 'V') {
					buff[j].v = malloc(3*sizeof(char));
					buff[j].v[0] = malloc((strlen(argv[optind-1])+1)*sizeof(char));
					strcpy(buff[j].v[0], argv[optind-1]);
					buff[j].v[1] = malloc((strlen(argv[optind])+1)*sizeof(char));
					strcpy(buff[j].v[1], argv[optind]);
				}
				j++;
		}
	}
	char* buf;
	if (invalid == 0) {
		while (j!=-1) {
			c = buff[j].c;
			switch (c) {
			case 'd':
				buf = (char*)malloc(sizeof(char) * 1024);
				printf("%s\n", getcwd(buf, 1024));
				break;
			case 'i':
				printf("real user ID %d\n", getuid());
				printf("effective user ID %d\n", geteuid());
				printf("real ID of the group %d\n", getgid());
				printf("effective group ID %d\n", getegid());
				break;
			case 's':
				printf("the process becomes the leader of the group %d\n", setpgid(0, 0));
				break;
			case 'p':
				printf("process ID %d\n", getpid());
				printf("ID of the parent process %d\n", getppid());
				printf("ID of the process group %d\n", getpgrp());
				break;
			case 'u':
				getrlimit(RLIMIT_FSIZE, &a);
				printf("ulimit %ld\n", a.rlim_max);
				break;
			case 'U':
				a.rlim_cur = atol(buff[j].v[0]);
				a.rlim_max = atol(buff[j].v[0]);
				setrlimit(RLIMIT_FSIZE, &a);
				printf("ulimit %ld\n", a.rlim_max);
				break;
			case 'c':
				getrlimit(RLIMIT_CORE ,&a);
				printf("core file size %ld\n", a.rlim_max);
				break;
			case 'C':
				a.rlim_cur = atol(buff[j].v[0]);
				a.rlim_max = atol(buff[j].v[0]);
				setrlimit(RLIMIT_CORE, &a);
				printf("core file size changed %ld\n", a.rlim_max);
				break;
			case 'v':
				for (char** env = envp; *env != 0; env++)
				{
					char* thisEnv = *env;
					printf("%s\n", thisEnv);
				}
				break;
			case 'V':
				if (setenv(buff[j].v[0], buff[j].v[1], 2) == 0)
				{
					printf("setenv: set %s\n", buff[j].v[0]);
					printf("setenv: set %s\n", buff[j].v[1]);
					printf("%s\n", getenv(buff[j].v[0]));
				}
				else
				{
					printf("setenv: Cannot set '%s'\n", buff[j].v[0]);
				}
				break;
			}
			j--;
		}
	}
	return 0;
}
