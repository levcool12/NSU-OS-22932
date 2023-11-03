#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node_s {
    char *str;
    struct Node_s *next;
} Node;
Node *head, *tail; 

void push(char *str) {
    unsigned long len = strlen(str) + 1;
    char *copyPtr = calloc(len, sizeof(char));
    strcpy(copyPtr, str);

    tail->str = copyPtr;
    tail->next = calloc(1, sizeof(Node));

    tail = tail->next;
}

void printList() {
    Node *ptr = head;
    while (ptr != NULL) {
        if (ptr->str) {
            printf("%s\n", ptr->str);
        }
        ptr = ptr->next;
    }
}

int main() {
    char inputBuf[256] = {0};
    head = malloc(sizeof(Node));
    head->str = NULL;
    head->next = NULL;
    tail = head;

    while (fgets(inputBuf, 256, stdin) != NULL) {
        if (inputBuf[0] == '.') {
            printList();
            return 0;
        }

        char *lineEnd = strchr(inputBuf, '\n');
        if (lineEnd == NULL) {
            size_t newBufCnt = 0;
            size_t newBufCap = 256;
            char *newBuf = malloc(256);

            memcpy(newBuf, inputBuf, 256);
            newBufCnt += 256 - 1;

            while (fgets(inputBuf, 256, stdin) != NULL) {
                newBufCap += 256;
                newBuf = realloc(newBuf, newBufCap);

                memcpy(newBuf + newBufCnt, inputBuf, 256);
                newBufCnt += 256 - 1;

                lineEnd = strchr(newBuf, '\n');
                if (lineEnd) {
                    *lineEnd = '\0';
                    push(newBuf);
                    free(newBuf);
                    break;
                }
            }
        } else {
            *lineEnd = '\0';
            push(inputBuf);
        }
    }

    return 0;
}
