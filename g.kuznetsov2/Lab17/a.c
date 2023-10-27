#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#define BUF_SIZE 100

typedef struct TerminalString{
    char *str;
    unsigned int cols;
    unsigned int size;
    unsigned int length;
} TS;

struct termios default_settings;

void recoverDefaultSetting(){
    tcsetattr(STDIN_FILENO, TCSANOW, &default_settings);
}

void TS_init(TS *ts){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    ts->cols = w.ws_col;
    if(ts->cols == 0) ts->cols = 20;
//    free(&w);
    ts->str = (char*) calloc(ts->cols, sizeof(char));
    ts->size = ts->cols;
    ts->length = 0;
}

void TS_append(TS *ts, char ch){
    if(ts->length + 1 == ts->size){
        ts->str = (char*) realloc(ts->str, sizeof(char) * ts->size + ts->cols);
        ts->size += ts->cols;
        TS_append(ts, '\n');
    }
    write(STDOUT_FILENO, &ch, sizeof(char));
    ts->str[ts->length++] = ch;
}

int main() {
    printf("Type text\n");
    TS ts;
    TS_init(&ts);
//    setbuf(stdout, NULL);
    struct termios terminal_settings;
    tcgetattr(STDIN_FILENO, &terminal_settings);
    default_settings = terminal_settings;
    terminal_settings.c_lflag &= ~(ICANON | ECHO);
    terminal_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW,  &terminal_settings);

    char ch;
    while (1){
        if(read(fileno(stdin), &ch, sizeof(char) == -1)){
            if(errno == EINTR){
//                perror("Something went wrong in reading, trying again\n");
                continue;
            } if(errno == EAGAIN){
                //perror("Something went wrong in reading, trying again\n");
                continue;
            }
            perror("Can't open the file :(\n");
            exit(1);
        }
        if(ch == '\000') continue;
        TS_append(&ts, ch);
    }
//
//    char *buf = (char*) calloc(BUF_SIZE, sizeof(char));
//    int pointer = 0;

//    scanf("%c", &ch);
//    while(ch){
//        buf[pointer] = ch;
//        pointer++;
//        printf("%s", buf);
//        scanf("%c", &ch);
//    }
//
//    terminal_settings.c_lflag |= ICANON | ECHO;
//    tcsetattr(STDIN_FILENO, TCSANOW,  &terminal_settings);

    recoverDefaultSetting();
    printf("End\n");
    return 0;
}
