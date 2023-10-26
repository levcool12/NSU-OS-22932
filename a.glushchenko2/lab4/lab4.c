#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(char*** head, char* data, int* size) {
    char** newHead = (char**)malloc((*size + 1) * sizeof(char*));
    for (int i = 0; i < *size; i++) {
        newHead[i] = (*head)[i];
    }
    newHead[*size] = data;
    *head = newHead;
    (*size)++;
}

void printList(char** head, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s", head[i]);
    }
}

int main() {
    char** head = NULL;
    int size = 0;
    char input[256];
    fgets(input, sizeof(input), stdin);
    while (strcmp(input, ".\n") != 0) {
        char* data = (char*)malloc(strlen(input) + 1);
        strcpy(data, input);
        insert(&head, data, &size);
        fgets(input, sizeof(input), stdin);
    }
    printList(head, size);
    for (int i = 0; i < size; i++) {
        free(head[i]);
    }
    free(head);
    return 0;
}