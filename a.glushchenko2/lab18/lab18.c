#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char* argv[]) {
    struct stat fileStat;
    struct passwd* pwd;
    struct group* grp;

    if (argc < 2) {
        fprintf(stderr, "Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (lstat(argv[i], &fileStat) < 0) {
            perror(argv[i]);
            continue;
        }

        printf("%c", S_ISDIR(fileStat.st_mode) ? 'd' : (S_ISREG(fileStat.st_mode) ? '-' : '?'));

        printf("%c", (fileStat.st_mode & S_IRUSR) ? 'r' : '-');
        printf("%c", (fileStat.st_mode & S_IWUSR) ? 'w' : '-');
        printf("%c", (fileStat.st_mode & S_IXUSR) ? 'x' : '-');

        printf("%c", (fileStat.st_mode & S_IRGRP) ? 'r' : '-');
        printf("%c", (fileStat.st_mode & S_IWGRP) ? 'w' : '-');
        printf("%c", (fileStat.st_mode & S_IXGRP) ? 'x' : '-');

        printf("%c", (fileStat.st_mode & S_IROTH) ? 'r' : '-');
        printf("%c", (fileStat.st_mode & S_IWOTH) ? 'w' : '-');
        printf("%c", (fileStat.st_mode & S_IXOTH) ? 'x' : '-');

        printf("  %ld", (long)fileStat.st_nlink);

        if ((pwd = getpwuid(fileStat.st_uid)) != NULL) {
            printf("  %s", pwd->pw_name);
        }
        else {
            printf("  %d", fileStat.st_uid);
        }

        if ((grp = getgrgid(fileStat.st_gid)) != NULL) {
            printf("  %s", grp->gr_name);
        }
        else {
            printf("  %d", fileStat.st_gid);
        }

        if (S_ISREG(fileStat.st_mode)) {
            printf("  %lld", (long long)fileStat.st_size);
        }
        else {
            printf("  %10s", "");
        }

        struct tm* tm_info;
        tm_info = localtime(&fileStat.st_mtime);
        char buffer[20];
        strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", tm_info);
        printf("  %s  ", buffer);

        printf("%s\n", argv[i]);
    }
    return 0;
}