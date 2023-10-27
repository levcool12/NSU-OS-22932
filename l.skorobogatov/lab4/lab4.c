#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char * string;
	struct node * next;
} node;

int main()
{
	char string[12355];
	node * head = NULL;
	node * str;
	int string_len;
	while (1)
	{
		fgets(string, 10000, stdin);
		if ((int)string[0] == 46)
		{
			while (head != NULL)
			{
				printf("%s", head->string);
				head = head->next;
			}
			exit(0);
		}
		else
		{
			string_len = (int)strlen(string);
			string_len++;
			if (head == NULL)
			{
				head = (node *)malloc(sizeof(node));
				head->next = NULL;
				head->string = (char*)malloc(sizeof(char)*string_len);
				strcpy(head->string, string);
				str = head;
			}
			else
			{
				str->next = (node *)malloc(sizeof(node));
				str = str->next;
				str->string = (char*)malloc(sizeof(char)*string_len);
				strcpy(str->string, string);
				str->next = NULL;
			}
		}
	}
	return 0;
}
