#include <unistd.h>
#include <stdio.h>

uid_t do_work() {
    uid_t ruid = getuid();
    uid_t euid = geteuid();
    printf("Real User ID: %d\n", ruid);
    printf("Effective User ID: %d\n", euid);
    FILE* file = fopen("test.txt", "r");
    if (file == NULL)
        perror("");
    else
        fclose(file);
    return ruid;
}

int main() {
    uid_t ruid = do_work();
    setuid(ruid);
    setgid(getgid());
    do_work();
    return 0;
}
