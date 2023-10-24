#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

typedef struct Str {
    int indent;
    int len;
} Str;

typedef struct Arr {
    Str* arr;
    int capacity;
    int size;
} Arr;

Arr array;
int descriptor;
char* data;
struct stat st;

void read_file(){
    descriptor = open("test.txt", O_RDONLY);
    if(descriptor == -1){
        perror("File is not open");
        exit(1);
    }
    if(fstat(descriptor, &st) == -1){
        perror("fstat");
        exit(1);
    }
    data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, descriptor, 0);
    if(data == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
}

void push(Arr* array, int indent, int len) {
    if (array->size >= array->capacity) {
        array->capacity *= 2;
        array->arr = (Str*)realloc(array->arr, sizeof(Str) * array->capacity);
    }
    array->arr[array->size].indent = indent;
    array->arr[array->size].len = len;
    array->size++;
}

void building_table(Arr* array) {
    read_file();
    int indent = 0;
    int len = 0;
    for(int i = 0; i < st.st_size; i++) {
        if (data[i] != '\n') {
            len++;
        }
        else {
            len++;
            push(array, indent, len);
            indent += len;
            len = 0;
        }
    }
}

void alarm_f(int al){
    printf("Timed out!\n");
    for(int i = 1; i <= array.size; i++){
       char* str = malloc(sizeof(char) * array.arr[i - 1].len);
       strncpy(str, &data[array.arr[i - 1].indent], array.arr[i - 1].len);
       printf("%s", str);
       free(str);
    }
    exit(EXIT_SUCCESS);
}

int main() {
    array.capacity = 4;
    array.size = 0;
    array.arr = (Str*)malloc(sizeof(Str) * array.capacity);
    int number;
    building_table(&array);
    signal(SIGALRM, alarm_f);
    alarm(5);
    while (true) {
        printf("Enter the line number\n");
        scanf("%d", &number);
        if(number > array.size){
            printf("This line is not in the file!\n");
            continue;
        }
        if (number == 0) {
            break;
        }
        char* str = malloc(sizeof(char) * array.arr[number - 1].len);
        strncpy(str, &data[array.arr[number - 1].indent], array.arr[number - 1].len);
        printf("%s", str);
        free(str);
        alarm(0);
    }
    free(array.arr);
    close(descriptor);
    return 0;
}