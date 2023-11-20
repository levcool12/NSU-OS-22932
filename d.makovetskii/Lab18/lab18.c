// 18. Листинг каталога
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void print_permissions(mode_t mode) {  // Три группы символов, соответствующие правам доступа для хозяина, группы и всех остальных
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void print_file_info(const char* filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return;
    }

    print_permissions(file_stat.st_mode);
    // Количество связей файла
    printf("   %ld", (long)file_stat.st_nlink);

    struct passwd* owner = getpwuid(file_stat.st_uid);
    // Имена собственника и группы файла
    if (owner != NULL)
        printf(" %s", owner->pw_name);
    else
        printf(" %d", file_stat.st_uid);

    struct group* group = getgrgid(file_stat.st_gid);
    if (group != NULL)
        printf(" %s", group->gr_name);
    else
        printf(" %d", file_stat.st_gid);
    // Если файл является обычным файлом, его размер. Иначе оставьте это поле пустым.
    if (S_ISREG(file_stat.st_mode))
        printf(" %ld", (long)file_stat.st_size);
    else
        printf("   ");
    // Дату модификации файла
    struct tm* modified_time = localtime(&file_stat.st_mtime);
    char time_buffer[80];
    strftime(time_buffer, sizeof(time_buffer), "%b %d %H:%M", modified_time);
    printf(" %s", time_buffer);
    // Имя файла
    printf(" %s\n", filename);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Invalid input: no file.");
        return 1;
    }

    for (int i = 1; i < argc; i++)
        print_file_info(argv[i]);

    return 0;
}