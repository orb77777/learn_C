#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* next;
    int number;
} Node; 

Node* list_create()
{
    Node* list = (Node*)malloc(sizeof(Node));
    list->next = NULL;
    list->number = -1;
    return list;
}

Node* find_last_element(Node* list)
{
    if(!list->next)
    {
        return list;
    }

   return find_last_element(list->next);
}

void list_add(Node* list, int element)
{
    Node* last = find_last_element(list);
    Node* new = (Node*) malloc(sizeof(Node));

    last->next = new;
    new->next = NULL;
    new->number = element;

}

void print_list(Node* list)
{
    if(!list->next)
    {
        printf("%d \n", list->number);
        return;
    }

    printf("%d ", list->number);
    print_list(list->next);
}

int list_search(Node* list, const int element)
{
    int index = -1;

    while(element != list->number  && list->next)
    {
        index++;
        list = list->next;
    }

    return index;
}

void list_delete(Node* list, const int element)
{
    while(list->next)
    {
        if(list->next->number == element)
        {
            list->next = list->next->next;
            break;
        }

        list = list->next;
    }

}

int main()
{
    Node* list = list_create();

    list_add(list, 5);
    list_add(list, 10);
    list_add(list, 10);

    print_list(list);

    int index = list_search(list, 10);
    printf("%d \n", index);

    list_delete(list, 5);
    print_list(list);

    free(list);


    return 0;
}
