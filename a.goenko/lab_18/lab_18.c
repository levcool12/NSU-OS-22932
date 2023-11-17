#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    struct stat path_stat;
    for(int i = 1; i<argc; i++){
        stat(argv[i], &path_stat);
        if(S_ISREG(path_stat.st_mode))
            printf("-");
        else if(S_ISDIR(path_stat.st_mode))
            printf("d");
        else
            printf("?");
        mode_t perm = path_stat.st_mode;
        printf("%c",(perm & S_IRUSR) ? 'r' : '-');
        printf("%c",(perm & S_IWUSR) ? 'w' : '-');
        printf("%c",(perm & S_IXUSR) ? 'x' : '-');
        printf("%c",(perm & S_IRGRP) ? 'r' : '-');
        printf("%c",(perm & S_IWGRP) ? 'w' : '-');
        printf("%c",(perm & S_IXGRP) ? 'x' : '-');
        printf("%c",(perm & S_IROTH) ? 'r' : '-');
        printf("%c",(perm & S_IWOTH) ? 'w' : '-');
        printf("%c ",(perm & S_IXOTH) ? 'x' : '-');
        struct passwd *pw = getpwuid(path_stat.st_uid);
        struct group * gr = getgrgid(path_stat.st_gid);
        printf("%s %s ", pw->pw_name, gr->gr_name);
        if (S_ISREG(perm))
            printf("%ld ", path_stat.st_size);
        char date[36];
        strftime(date, 36, "%d.%m.%Y %H:%M:%S", localtime(&path_stat.st_mtime));
        printf("%s ", date);
        char *filename = strrchr(argv[i], '/');
        if (filename == NULL)
            filename = argv[i];
        else
            filename++;
        printf("%s\n", filename);
    }
}