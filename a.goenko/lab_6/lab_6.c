#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

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
    descriptor = open("test.txt", O_RDONLY);
    if(descriptor == -1){
        perror("File is not open");
        exit(1);
    }
    char c;
    int indent = 0;
    int len = 0;
    while (read(descriptor, &c, 1) != 0) {
        if (c != '\n') {
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
    for(int i = 1; i <= array.size; i++)
    {
        lseek(descriptor, array.arr[i - 1].indent, SEEK_SET);
        char* str = malloc(sizeof(char) * array.arr[i - 1].len);
        read(descriptor, str, array.arr[i - 1].len);
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
        lseek(descriptor, array.arr[number - 1].indent, SEEK_SET);
        char* str = malloc(sizeof(char) * array.arr[number - 1].len);
        read(descriptor, str, array.arr[number - 1].len);
        printf("%s", str);
        free(str);
        alarm(0);
    }
    free(array.arr);
    close(descriptor);
    return 0;
}