#include <sys/ioctl.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
//#include <conio.h>
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
//    char tmp = '|';
//    if(ch == '\n') write(STDOUT_FILENO, &tmp, sizeof(char));
    if(!isprint(ch) && ch != '\n') return;
    if(ts->length + 1 == ts->size){
        ts->str = (char*) realloc(ts->str, sizeof(char) * ts->size + ts->cols);
        ts->size += ts->cols;
        TS_append(ts, ch);
    }
    write(STDOUT_FILENO, &ch, sizeof(char));
//    printf(":%c|%d:", ch, ts->length);
    ts->str[ts->length++] = ch;
}

void TS_erase(TS *ts){
    if(ts->length == 0) return;
    ts->length--;
    write(STDOUT_FILENO, "\b \b", sizeof(char) * 3);
}

void TS_kill(TS *ts){
    if(ts->length == 0) return;
    while(ts->length > 0 && ts->str[ts->length] != '\n'){
        ts->length--;
        write(STDOUT_FILENO, "\b \b", sizeof(char) * 3);
    }
}

void type_kill(){
    char c = 21; // ASCII value of CTRL-U (VKILL)
    ioctl(STDIN_FILENO, TIOCSTI, &c);
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
        if(read(fileno(stdin), &ch, sizeof(char)) == -1){
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
//        printf("%d ", ts.length);
//        int intChar = getchar();
//        printf("%d", intChar);
//        if(intChar == EOF) break;
//        if(ch == '\000') continue;
//        printf("%c", ch);
//        if(ts.length == 16){
//            type_kill();
//            ts.length++;
//        }
        else if(terminal_settings.c_cc[VERASE] == ch) TS_erase(&ts);
        else if(terminal_settings.c_cc[VKILL] == ch) TS_kill(&ts);
        else if('\n' == ch)
            TS_append(&ts, '\n');
        else if(isprint(ch)){
            TS_append(&ts, ch);
        } else{
            write(STDOUT_FILENO, "\a", sizeof(char));
        }
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
