#define _CRT_SECURE_NO_WARNINGS
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("Real user id: %d\n", getuid());
	printf("Effective user id: %d\n", geteuid());

	FILE* fp1;
	fp1 = fopen("tst.txt", "r");
	if (fp1 == NULL) {
		perror("Could not open the file");
	}
	else {
		fclose(fp1);
	}

	setuid(getuid());

	printf("Real user id: %d\n", getuid());
	printf("Effective user id: %d\n", geteuid());

	FILE* fp2;
	fp2 = fopen("tst.txt", "r");

	if (fp2 == NULL) {
		perror("Could not open the file");
	}
	else {
		fclose(fp2);
	}
}