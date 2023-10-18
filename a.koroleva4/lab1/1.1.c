#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <ulimit.h>
#include <sys/resource.h>

extern char** environ;

int main(int argc, char* argv[]) {
    int opt;
    char buffer[1024];
    if (argc < 2)
    {
        printf("No arguments\n");
        exit(0);
    }
    while ((opt = getopt(argc, argv, "ispuU:cC:dvV:")) != -1) {
        switch (opt) {
        case 'i': {
            printf("Real userId: %d\n", getuid());
            printf("Effect userId: %d\n", geteuid());
            printf("Real groupId: %d\n", getgid());
            printf("Effect groupId: %d\n", getegid());
            break; }
        case 's': {
            setpgid(0, 0);
            break; }
        case 'p': {
            printf("Curr procId: %d\n", getpid());
            printf("Parent procId: %d\n", getppid());
            printf("Group procId: %d\n", getpgid(0));
            break; }
        case 'u': {
            printf("Ulimit: %ld\n", ulimit(UL_GETFSIZE));
            break; }
        case 'U': {
            if (ulimit(UL_SETFSIZE, atol(optarg)) == -1)
                printf("Error\n");
            break; }
        case 'c': {
            struct rlimit rl;
            getrlimit(RLIMIT_CORE, &rl);
            printf("Core size = %ld\n", rl.rlim_cur);
            break; }
        case 'C': {
            struct rlimit rl;
            rlim_t new_size;
            sscanf(optarg, "%llu", &new_size);
            rl.rlim_cur = new_size;
            rl.rlim_max = RLIM_INFINITY;
            if (setrlimit(RLIMIT_CORE, &rl) == -1) {
                perror("Error");
                }
            else {
                printf("New core size = %ld\n", atol(optarg));
                }
            break;
        }
        case 'd': {
            getcwd(buffer, sizeof(buffer));
            printf("Curr dir: %s\n", buffer);
            break; }
        case 'v': {
            char** env = environ;
            for (env; *env != NULL; env++) {
                printf("%s\n", *env);
            }
            break; }
        case 'V':{
            char* arg = optarg;  
            if (putenv(arg) != 0) {
                perror("Error");
            }

            break;
        }
        default:
            printf("Error\n");
        }
    }

    return 0;
}