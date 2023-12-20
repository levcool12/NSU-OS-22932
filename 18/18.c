#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <libgen.h>
#include <string.h>

int main(int argc, char *argv[]) {

    for(int i = 1; argv[i]; i++) {

        char *filename = argv[i];

        struct stat buf;    //helper variable to contain files meta data
        errno = 0;
        if(stat(filename, &buf) == -1) { //get meta data about queried file
            perror("stat");
            exit(EXIT_FAILURE);
        }

        //check file type
        if(S_ISREG(buf.st_mode)) {  //if regular file
            printf("-");
        }
        else if(S_ISDIR(buf.st_mode)) { //if directory
            printf("d");
        }
        else {  //if sth else
            printf("?");
        }

        //print rights
        {
            const char rights[] = {'r', 'w', 'x'};
            const mode_t rdefs[] = {
                S_IRUSR, S_IWUSR, S_IXUSR,
                S_IRGRP, S_IWGRP, S_IXGRP,
                S_IROTH, S_IWOTH, S_IXOTH
                };
            
            for(int i = 0; i < 9; i++) {
                if((buf.st_mode & rdefs[i]) == rdefs[i]) {
                    printf("%c", rights[i % 3]);
                }
                else {
                    printf("-");
                }
            }
        }

        printf("%4lu", buf.st_nlink);   //prints count of links

        //prints owner user name
        {
            struct passwd *filepwd = getpwuid(buf.st_uid);
            printf(" %s", filepwd->pw_name);
        }

        //prints owner group name
        {
            struct group *filegrp = getgrgid(buf.st_gid);
            printf(" %s", filegrp->gr_name);
        }

        //prints file size if file is regular
        if(S_ISREG(buf.st_mode)) {
            printf("%8ld", buf.st_size);
        }
        else { 
            printf("%8c", ' ');
        }

        char *timestring = ctime(&buf.st_mtime);
        timestring[strlen(timestring) - 1] = 0;
        printf(" %s", timestring);

        printf(" %s", basename(filename));

        puts("");

    }

    return 0;

}
