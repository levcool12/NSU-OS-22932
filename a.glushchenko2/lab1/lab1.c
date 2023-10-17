#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ulimit.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    char options[] = "fdgipuvcU:C:V:";  /* valid options */
    int c;
    char* f_ptr, * g_ptr;
    char* dir = (char*)malloc(sizeof(char) * 128);
    char** env;
    extern char** environ;
    struct rlimit rl;
    int a = 5;
    
    if (argc < 2) {
        printf("Too few arguments\n");
        exit(0);
    }
    printf("argc equals %d\n", argc);
    while ((c = getopt(argc, argv, options)) != EOF) {
        switch (c) {

            case'i':
                printf("Real user id: %d\n", getuid());
                printf("Effective user id: %d\n", geteuid());
                printf("Real group id: %d\n", getgid());
                printf("Effective group id: %d\n", getegid());
                break;

            case 's':
                setpgid(0, 0);
                break;

            case 'p':
                printf("Process id: %d\n", getpid());
                printf("Parent process id: %d\n", getppid());
                printf("Group process id: %d\n", getpgid(0));
                break;

            case 'd':
                getcwd(dir, 128);
                printf("Current working directory: %s\n", dir);
                break;

            case 'u':
                printf("Ulimit value: %d\n", ulimit(UL_GETFSIZE));
                break;

            case 'c':
                getrlimit(RLIMIT_CORE, &rl);
                printf("Max size of core file: %d\n", rl.rlim_max);
                break;

            case 'v':
                printf("%s\n", *environ);
                break;

            case 'U':
                if (ulimit(UL_SETFSIZE, atoi(optarg)) != -1) {
                    ulimit(UL_SETFSIZE, atoi(optarg));
                    printf("New value of ulimit: %d\n", atoi(optarg));
                }
                else {
                    printf("Incorrect value of ulimit\n");
                }
                break;

            case 'C':
                rl.rlim_cur = atoi(optarg);
                setrlimit(RLIMIT_CORE, &rl) == 0;
                printf("New core size limit: %d\n", rl.rlim_cur);
                break;

            case 'V':
                if (putenv(optarg) != -1) {
                    printf("New value instaled\n");
                }
                else {
                    printf("Incorrect value\n");
                }
                break;

            case '?':
                printf("invalid option is %c\n", optopt);
                break;
            }
        }
        
    }