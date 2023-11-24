#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#define st_mtime st_mtim.tv_sec

char fileStatus(struct stat* st) {
	if (S_ISREG(st->st_mode)) return '-';
	else if (S_ISDIR(st->st_mode)) return 'd';
	else return '?';
}

void accessRights(struct stat* st) {
	char data[9];
	memset(data, '-', 9);

	//owner's rights
	if (st->st_mode& S_IRUSR) data[0] = 'r';
	if (st->st_mode& S_IWUSR) data[1] = 'w';
	if (st->st_mode& S_IXUSR) data[2] = 'x';

	//group rights
	if (st->st_mode& S_IRGRP) data[3] = 'r';
	if (st->st_mode& S_IWGRP) data[4] = 'w';
	if (st->st_mode& S_IXGRP) data[5] = 'x';

	//all others (outside the group)
	if (st->st_mode& S_IROTH) data[6] = 'r';
	if (st->st_mode& S_IWOTH) data[7] = 'w';
	if (st->st_mode& S_IXOTH) data[8] = 'x';

	for (int i = 0; i < 9; i++) {
		printf("%c", data[i]);
	}
}

void getTime(struct stat* st) {

	printf(" %c%c%c", ctime(&(st->st_mtime))[4], ctime(&(st->st_mtime))[5], ctime(&(st->st_mtime))[6]);
	printf(" %c%c", ctime(&(st->st_mtime))[8], ctime(&(st->st_mtime))[9]);
	printf(" %c%c:%c%c", ctime(&(st->st_mtime))[11], ctime(&(st->st_mtime))[12], ctime(&(st->st_mtime))[14], ctime(&(st->st_mtime))[15]);
	printf(" %c%c%c%c", ctime(&(st->st_mtime))[20], ctime(&(st->st_mtime))[21], ctime(&(st->st_mtime))[22], ctime(&(st->st_mtime))[23]);

}

void listing(char* argv) {
	struct stat st;
	stat(argv, &st);

	struct passwd* pwd = getpwuid(st.st_uid);
	struct group* grp = getgrgid(st.st_gid);


	//File status bits
	char s = fileStatus(&st);
	printf("%c", s);

	//access rights
	accessRights(&st);

	//Name of the owner
	pwd ? printf("%15s", pwd->pw_name) : printf(" %u", pwd->pw_uid);

	//File group name
	grp ? printf("%15s", grp->gr_name) : printf(" %g", grp->gr_gid);

	//file size
	s == '-' ? printf(" %lld", (long long int)st.st_size) : printf("");
	//File modification date
	getTime(&st);

	//file name
	s == '-' ? printf("%10s\n", basename(argv)) : printf(" .\n");
		
}


int main(int argc, char* argv[]) {

	if (argc <= 1) {
		printf("too few arguments\n");
		exit(0);
	}

	for (int i = 1; i < argc; i++) {
		listing(argv[i]);
	}
	printf("\n");
}