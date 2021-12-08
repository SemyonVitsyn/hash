#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hashnode
{
        int key;
        char data[50];
        struct hashnode *node;
};

int form_hash(int phone_number);
void find(int key, int hash, struct hashnode **table);
void add(int key, int hash, char *name, struct hashnode **table);
void delete(int key, int hash, struct hashnode **table);
void destroy_hash(struct hashnode **table);





int form_hash(int phone_number)
{
        return phone_number % 100; 
}

void add(int key, int hash, char *name, struct hashnode **table)
{
        struct hashnode *current = table[hash];
        if (table[hash] == NULL)
        {
                table[hash] = (struct hashnode*)calloc(1, sizeof(struct hashnode));
                table[hash]->key = key;
                strcpy(table[hash]->data, name);
                table[hash]->node = NULL;
        }
        else
        {
                while (current->node != NULL && current->node->key != key)
                        current = current->node;
                if (current->node == NULL)
                {
                        struct hashnode *add = (struct hashnode*)calloc(1, sizeof(struct hashnode));
                        add->key = key;
                        strcpy(add->data, name);
                        add->node = NULL;
                        current->node = add;
                }
                else
                        printf("Contact already exist\n");

        }
}

void find(int key, int hash, struct hashnode **table)
{
        struct hashnode *current = table[hash];
        while (current != NULL && current->key != key)
                current = current->node;
        if (current == NULL)
                printf("Contact does not exist\n");
        else
                printf("%s\n", current->data);
}

void delete(int key, int hash, struct hashnode **table)
{
        struct hashnode *sw, *current = table[hash];
        if (current == NULL)
        {
                printf("Contact does not exist\n");
                return;
        }
        if (current->key == key)
        {
                free(current);
                table[hash] = current->node;
                return;
        }
        while (current->node->key != key && current->node->node != NULL)
                current = current->node;
        if (current->node->node == NULL && current->node->key != key)
                printf("Contact does not exist\n");
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
        for (i = 0; i < 100; i++)
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
        int i, choice, hash, key, size = 100;
        char name[50];
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
                                printf("Phone number = ");
                                scanf("%d", &key);
                                hash = form_hash(key);
                                find(key, hash, table);
                                break;
                        }
                        case 2:
                        {
                                printf("Phone number = ");
                                scanf("%d", &key);
                                hash = form_hash(key);
                                printf("Name = ");
                                scanf("%s", name);
                                add(key, hash, name, table);
                                break;
                        }
                        case 3:
                        {
                                printf("Phone number = ");
                                scanf("%d", &key);
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

