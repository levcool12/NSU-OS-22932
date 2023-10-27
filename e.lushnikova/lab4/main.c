#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char* string;
    struct Node* next;
};

void insert(struct Node** head, char* string) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->string = (char*)malloc((strlen(string) + 1) * sizeof(char));
    strcpy(newNode->string, string);
    newNode->next = *head;
    *head = newNode;
}

void display(struct Node* head) {
    while (head != NULL) {
        printf("%s\n", head->string);
        head = head->next;
    }
}

int main() {
    struct Node* head = NULL;
    char input[100];
    do {
        printf("Enter the string: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        if (strcmp(input, ".") == 0) {
            break;
        }

        insert(&head, input);
    } while (1);
    display(head);
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;

        free(temp->string);
        free(temp);
    }
    return 0;
}