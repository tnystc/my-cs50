#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int number;
    struct node *next;

}
node;

node* create(int number);
bool find(node* head, int number);
node* insert(node* head, int number);
void destroy(node* head);

int main(int argc, char *argv[])
{
    int x = 6;

    node* list = create(x);
    if (list == NULL)
    {
        return 1;
    }
    node* tmp = insert(list, 4);
    if (tmp == NULL)
    {
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        return 1;
    }
    list = tmp;
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    int searchNumber = 6;
    bool found = find(list, searchNumber);
    if (found)
    {
        printf("succes\n");
    }

    destroy(list);
}

node* create(int number)
{
    node* n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }
    n->number = number;
    n->next = NULL;
    return n;
}

bool find(node* head, int number)
{
    node* trvptr = head;
    while(trvptr->number != number)
    {
        trvptr = head->next;
        if (trvptr->next == NULL)
        {
            if (trvptr->number == number)
            {
                return true;
            }
            return false;
        }
    }
    return true;
}

node* insert(node* head, int number)
{
    node* new = malloc(sizeof(node));
    if (new == NULL)
    {
        return NULL;
    }
    new->number = number;
    new->next = head;
    return new;
}

void destroy(node* head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        destroy(head->next);
        free(head);
    }
}