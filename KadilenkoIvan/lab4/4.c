#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_elem_ {
    char* str;
    struct List_elem_* next;
}List_elem;

List_elem* create_List_elem(char* str) {    List_elem* new_List_elem = malloc(sizeof(List_elem));
    new_List_elem->str = malloc(strlen(str) + 1);
    strcpy(new_List_elem->str, str);
    new_List_elem->next = NULL;
    return new_List_elem;
}

void append_List_elem(List_elem** curr_elem, char* str) {
    List_elem* new_List_elem = create_List_elem(str);
    (*curr_elem)->next = new_List_elem;
}

void print_List(List_elem* head) {
    List_elem* current = head->next;
    while (current != NULL) {
        printf("%s", current->str);
        current = current->next;
    }
}

void free_List(List_elem* head) {
    List_elem* current = head->next->next;
    while (current != NULL) {
        List_elem* next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
}

int main() {
    List_elem* head = malloc(sizeof(List_elem));
    List_elem* curr = head;
    char input[1000];
    printf("Input:\n");
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (input[0] == '.') {
            break;
        }
        append_List_elem(&curr, input);
        curr = curr->next;
    }

    printf("Strings:\n");
    print_List(head);
    free_List(head);
    return 0;
}