#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    printf("Real user ID %d\n", getuid());
	printf("Effective user ID %d\n", geteuid());

    FILE *file = fopen("test.txt", "r");
    if (file == NULL)
        perror("Could not open the file");
    else
        fclose (file);

    int flg_set = setuid(getuid());

    printf("Real user ID %d\n", getuid());
    printf("Effective user ID %d\n", geteuid());

    FILE *file2 = fopen("test.txt", "r");
    if (file2 == NULL)
        perror("Could not open the file");
    else
        fclose (file2);
}