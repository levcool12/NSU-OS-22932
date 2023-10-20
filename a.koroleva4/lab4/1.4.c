#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100


typedef struct Node
{
    char* str;
    struct Node* next;
} Node;


void insertNode(Node** head, char* str)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->str = (char*)malloc((strlen(str) + 1) * sizeof(char));
    strcpy(newNode->str, str);
    newNode->next = NULL;

    if (*head == NULL) *head = newNode;
    else
    {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void printList(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {
        printf("%s\n", temp->str);
        temp = temp->next;
    }
}

int main()
{
    Node* head = NULL;
    char str[MAX_STRING_LENGTH];


    while (1)
    {
        fgets(str, MAX_STRING_LENGTH, stdin);
        str[strcspn(str, "\n")] = '\0';
        if (strcmp(str, ".") == 0) break; 
        insertNode(&head, str);
    }

    printList(head);

    Node* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->str);
        free(temp);
    }

    return 0;
}