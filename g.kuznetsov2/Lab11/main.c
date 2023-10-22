#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdarg.h>

int execvpe(char *file, char *const argv[], char **envp){
    extern char **environ;
    if(envp != NULL) environ = envp;
    return execvp(file, argv);
}


int main(int argc, char *argv[]) {\
//    extern char **environ;
//    printf("\n%d %s\n", argc, argv[0]);
    if(argc < 2){
        perror("You must at least enter program name to exec\n");
        exit(1);
    }
    printf("Enter number of environment params you want to set:\n");
    int n = 0;
    scanf("%d", &n);
    if(n < 0){
        perror("Incorrect number of params");
        exit(1);
    }
    char **new_env = calloc(n + 1, sizeof(char*));
    if(n > 0){
        printf("Enter environment params you want to set new process (param=val separates by \\n):\n");
        new_env = (char **) calloc(n + 1, sizeof(char*));;
        for(int i = 0; i < n; i++){
            new_env[i] = (char*) calloc(100, sizeof(char));
            scanf("%s", new_env);
        }
    }
//    char *const new_env[] = {"USER=ElevenLabUser", NULL};
    new_env[n] = NULL;
    execvpe(argv[1], argv + 1, new_env);

    perror("Something went wrong\n");
    return 1;
}