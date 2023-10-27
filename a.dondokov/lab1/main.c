#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

extern char ** environ;

int main(int argc, char *argv[]) {
    char options[] = "ispuU:cC:dvV:"; 
    int c;
    struct rlimit rlp;
    while ((c = getopt(argc, argv, options)) != EOF) {
        switch (c) {
            case 'i': { printf(" uid: %d\n euid: %d\n gid: %d\n egid: %d\n", getuid(), geteuid(), getgid(), getegid()); break; }
            
            case 's': { 
                if (setpgid(0, 0) == -1) {perror("error\n"); } 
                else { setpgid(0, 0);printf("The process becomes the leader of the group \n"); }
                break; }

            case 'p': { printf(" pid: %d\n ppid: %d\n pgrp: %d\n", getpid(), getppid(), getpgrp());  break; }

            case 'u': { 
                if (getrlimit(RLIMIT_FSIZE, &rlp) == -1) {perror("error\n"); }  
                else { printf("ulimit value: %llu\n", rlp.rlim_cur); } 
                break; }

            case 'U': { 
                long new_ulimit = strtol(optarg, NULL, 10);
                if (new_ulimit == 0) { perror("error\n"); break; }
                if (getrlimit(RLIMIT_FSIZE, &rlp) == -1) { perror("error\n"); break; }
                rlp.rlim_cur = new_ulimit;
                if (setrlimit(RLIMIT_FSIZE, &rlp) == -1) { perror("error\n"); } 
                else { printf("the ulimit value changes\n"); }
                break; }

            case 'c': {
                if (getrlimit(RLIMIT_CORE, &rlp) == -1) { perror("error\n"); } 
                else { printf("core size: %llu\n", rlp.rlim_cur); }
                break; }

            case 'C': { 
                long long new_rlim = strtoll(optarg, NULL, 10);
                if (new_rlim == 0) { perror("error\n"); break; }
                if (getrlimit(RLIMIT_CORE, &rlp) == -1) { perror("error\n"); break; }
                rlp.rlim_cur = new_rlim;
                if (setrlimit(RLIMIT_CORE, &rlp) == -1) { perror("error\n"); } 
                else { printf("core size changes\n"); }
                break; }

            case 'd': { 
                char *p = getenv("PWD");
                if (p == NULL) { perror("error\n"); } 
                else { printf("current directory: %s\n", p); }
                break; }

            case 'v': { 
                char **ptr = environ;
                for (; *ptr != NULL; ptr++) {
                    printf("%s\n", *ptr);
                }
                break; }

            case 'V': {
                if (putenv(optarg) == -1) {
                    printf("error\n");
                }
                break; }

            default:
                printf("Error\n");
        }
    }

    return 0;
}