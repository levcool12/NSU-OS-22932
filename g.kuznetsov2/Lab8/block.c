#include <stdio.h>
#include <unistd.h>

int main(){
    int fd = open("a.txt", 'r');
    if(fd == -1){
        printf("Can't open file\n");
        return 0;
    }
//    fseek(fd, 0L, SEEK_END);
//    int sz = ftell(fd);
//    fseek(fd, 0L, SEEK_SET);
    lockf(fd, F_LOCK, 6);
    char buf[100];
    while(1) {
        read(fd, buf, 100);
        printf("%s\n", buf);
    }
    return 0;
}
