#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char* str;
    struct Node* next;
} Node;

void push(Node* last, char* arr) {
    Node* new = malloc(sizeof(Node));
    new->str = malloc(sizeof(char) * (strlen(arr) + 1));
    strcpy(new->str, arr);
    new->next = NULL;
    last->next = new;
}

int main() {
    Node* head = malloc(sizeof(Node));
    Node* last = malloc(sizeof(Node));
    head->next = NULL;
    bool flag = 0;
    char* arr;
    while (true) {
        arr = malloc(sizeof(char) * 100);
        fgets(arr, 100, stdin);
        if (flag == 1) {
            push(last, arr);
            last = last->next;
        }
        else {
            push(head, arr);
            flag = 1;
            last = head->next;
        }
        free(arr);
        if (last->str[0] == '.')
            break;
    }
    head = head->next;
    while (head->next) {
        printf("%s", head->str);
        head = head->next;
    }
    printf("%s", head->str);
}