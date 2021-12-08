#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>



struct hashnode
{
	char key[50];
	char data[10][50];
	struct hashnode *node;
};

int form_hash(char *key);
void find(char *key, int hash, struct hashnode **table);
void add(char *key, int hash, char *translation, struct hashnode **table);
void delete(char *key, int hash, struct hashnode **table);
void destroy_hash(struct hashnode **table);





int form_hash(char *key)
{
	int hash = 0, i = 0;
	while (key[i] != '\0' && i < 50)
	{
		hash += key[i];
		i++;
	}
	return hash % 1000;
}

void add(char *key, int hash, char *translation, struct hashnode **table)
{
	struct hashnode *current = table[hash];
	int i = 0;
	if (table[hash] == NULL)
	{
		table[hash] = (struct hashnode*)calloc(1, sizeof(struct hashnode));
		strcpy(table[hash]->key, key);
		strcpy(table[hash]->data[0], translation);
		strcpy(table[hash]->data[1], "***");
		table[hash]->node = NULL;
	}
	else
	{
	//	while (current->node != NULL && strcmp(current->node->key, key))
		while (current->node != NULL && strcmp(current->key, key))
			current = current->node;
		if (current->node == NULL && strcmp(current->key, key))
		{
			struct hashnode *add = (struct hashnode*)calloc(1, sizeof(struct hashnode));
			strcpy(add->key, key);
                	strcpy(add->data[0], translation);
			strcpy(add->data[1], "***");
               	 	add->node = NULL;
			current->node = add;
		}
		else
		{
	//		while (strcmp(current->
			while (strcmp(current->data[i], "***") && strcmp(current->data[i], translation))
				i++;
			if (!strcmp(current->data[i], "***"))
			{
                     	  	strcpy(current->data[i], translation);
                       		strcpy(current->data[i+1], "***");
			}
			else
                        	printf("Translation already exist\n");
		}
	}
}

void find(char *key, int hash, struct hashnode **table)
{
	int i = 0;
	struct hashnode *current = table[hash];
	while (current != NULL && strcmp(current->key, key))
		current = current->node;
	if (current == NULL)
		printf("Translation does not exist\n");
	else
	{
		while (strcmp(current->data[i], "***") && i < 10)
		{
                	printf("%s\n", current->data[i]);
			i++;
		}
	}
}

void delete(char* key, int hash, struct hashnode **table)
{
	struct hashnode *sw, *current = table[hash];
	if (current == NULL)
	{
		printf("Translation does not exist\n");
		return;
	}
	if (!strcmp(current->key, key))
	{
		free(current);
		table[hash] = current->node;
		return;
	}
	while (strcmp(current->node->key, key) && current->node->node != NULL)
        	current = current->node;
	if (current->node->node == NULL && strcmp(current->node->key, key))
                printf("Translation does not exist\n");
	else 
	{
                if (current->node->node == NULL)
		{
	       		free(current->node);
			current->node = NULL;	
		}
		else
		{
			sw = current->node->node;
			free(current->node);
			current->node = sw;
		}
	}
}	

void destroy_hash(struct hashnode **table)
{
	int i;
	for (i = 0; i < 1000; i++)
	{
		while (table[i] != NULL)
		{
			free(table[i]);
			table[i] = table[i]->node;
		}
		table[i] = NULL;
	}
}





int main()
{
	setlocale(LC_ALL, "Rus");
	int i, choice, hash, size = 1000;
	char key[50], translation[50];
	struct hashnode *table[size];
	for (i = 0; i < size; i++)
	{
		table[i] = NULL;
	}	
	printf("1. Find\n2. Add\n3. Delete\n4. Exit\n");
	while (1)
	{
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
			{
				printf("Word = ");
				scanf("%s", key);
				hash = form_hash(key);
				find(key, hash, table);
				break;
			}
			case 2:
			{
				printf("Word = ");
				scanf("%s", key);
				hash = form_hash(key);      
				printf("Translation = ");
				scanf("%s", translation);
				add(key, hash, translation, table);
				break;
			}
			case 3:
			{
				printf("Word = ");
                      		scanf("%s", key);
                       	        hash = form_hash(key);
				delete(key, hash, table);
				break;
			}
			case 4:
			{
				destroy_hash(table);
				return 0;
				break;
			}
			default:
			{
				printf("Wrong input\n");
				break;
			}
		}
		printf("--------------------------------------------------------\n");
	}
	return 0;
}
