#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ulimit.h>
#include <sys/resource.h>

int main(int argc, char** argv){

    char c;
    extern char* optarg;

    while ((c = getopt(argc, argv, "ispuU:cC:dvV:")) != -1) {
        switch (c){
            case 'i':
                {
                    uid_t uid = getuid();
                    uid_t euid = geteuid();
                    gid_t gid = getgid();
                    gid_t egid = getegid();

                    printf("UID: %d eUID: %d GID: %d eGID: %d\n", uid, euid, gid, egid);
                }
                break;

            case 's':
                setpgid(0, 0);
                break;


            case 'p':
                {
                    pid_t pid = getpid();
                    pid_t ppid = getppid();
                    pid_t pgid = getpgid(0);

                    printf("PID: %d pPID: %d pGID: %d\n", pid, ppid, pgid);
                }
                break;

            case 'u':
                {
                    long value = ulimit(UL_GETFSIZE);

                    printf("Soft file size limit: %d blocks\n", value);
                }
                break;

            case 'U':
                {
                    long value = atol(optarg);

                    // set errno = 0
                    // if ulimit == -1 check errno
                    ulimit(UL_SETFSIZE, value);
                }
                break;

            case 'c':
                {
                    struct rlimit rlp;
                    getrlimit(RLIMIT_CORE, &rlp);

                    printf("Max core file size: %d bytes\n", rlp.rlim_cur);
                }
                break;

            case 'C':
                {
                    struct rlimit rlp;
                    getrlimit(RLIMIT_CORE, &rlp);

                    rlp.rlim_cur = atoll(optarg);

                    setrlimit(RLIMIT_CORE, &rlp);
                }
                break;

            case 'd':
                {
                    long path_size = pathconf(".", _PC_PATH_MAX);
                    char* buf = malloc(path_size);

                    getcwd(buf, path_size);

                    //char* buf = getenv("PWD");

                    printf("%s\n", buf);
                }
                break;

            case 'v':
                {
                    extern char** environ;

                    int i = 0;

                    while (environ[i] != NULL){
                        printf("%s\n", environ[i]);
                        i++;
                    }
                }
                break;

            case 'V':
                putenv(optarg);
                break;
            
            default:
                break;
        }
    }

    return 0;
}
