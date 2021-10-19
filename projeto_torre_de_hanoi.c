// Projeto: Pilha Dinâmica - Torre de Hanoi
// Aluno: Fernando Miguel D'Andrea Lima RA:11.118.771-2
// link do vídeo: https://youtu.be/z5uH9tE_iiQ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *next_node;
};

struct List
{
    struct Node *start;
    struct Node *end;
    int size;
};

void initialize(struct List *list)
{
    list->start = NULL;
    list->end = NULL;
    list->size = 0;
}

void push(struct List *list, int value)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next_node = NULL;
    if(list->size == 0)
    {
        list->start = new_node;
    }
    else
    {
        new_node->next_node = list->start;
        list->start = new_node;
    }
    list->size++;
}

void pop(struct List *list)
{
    if(list->size == 0)
        puts("Lista vazia");
    else
    {
        struct Node *aux = list->start;
        list->start = aux->next_node;
        free(aux);
        list->size--;
    }
}

void display(struct List *list1, struct List *list2, struct List *list3)
{
    struct Node *aux1 = list1->start;
    struct Node *aux2 = list2->start;
    struct Node *aux3 = list3->start;
    printf("\n|\t|\t|\n");
    while(aux1 != NULL || aux2 != NULL || aux3 != NULL)
    {
        if(aux1 != NULL && aux2 == NULL && aux3 != NULL)
        {
            printf("%d\t|\t%d\n", aux1->data, aux3->data);
            aux1 = aux1->next_node;
            aux3 = aux3->next_node;        
        }
        else if(aux1 != NULL && aux2 != NULL && aux3 == NULL)
        {
            printf("%d\t%d\t|\n", aux1->data, aux2->data);
            aux1 = aux1->next_node;
            aux2 = aux2->next_node;
        }
        else if(aux1 != NULL && aux2 == NULL && aux3 == NULL)
        {
            printf("%d\t|\t|\n", aux1->data);
            aux1 = aux1->next_node;
        }
        else if(aux1 == NULL && aux2 != NULL && aux3 != NULL)
        {
            printf("|\t%d\t%d\n", aux2->data, aux3->data);
            aux2 = aux2->next_node;
            aux3 = aux3->next_node;
        }
        else if(aux1 == NULL && aux2 != NULL && aux3 == NULL)
        {
            printf("|\t%d\t|\n", aux2->data);
            aux2 = aux2->next_node;
        }
        else if(aux1 == NULL && aux2 == NULL && aux3 != NULL)
        {
            printf("|\t|\t%d\n", aux3->data);
            aux3 = aux3->next_node;
        }
        else
        {
            printf("%d\t%d\t%d\n", aux1->data, aux2->data, aux3->data);
            aux1 = aux1->next_node;
            aux2 = aux2->next_node;
            aux3 = aux3->next_node;
        }
    }
    puts("\n===================\n");
    free(aux1);
    free(aux2);
    free(aux3);
}

int main()
{
    struct List origin, aux, target;    
    int n_disk;
    int total_mov=(2^n_disk-1);

    initialize(&origin);
    initialize(&aux);
    initialize(&target);
    puts("Digite a quantidade de discos do pino inicial:");
    scanf(" %d", &n_disk);

    while(n_disk>0)
    {
        push(&origin, n_disk);
        n_disk = n_disk - 1;
    }
    
    puts("\n");
    display(&origin, &aux, &target);

    for(int i = 1; i <= total_mov; i++)
    {
        if(i%3 == 1)
        {
            if(origin.size == 0)
            {
                push(&origin,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
            else if(target.size == 0)
            {
                push(&target,origin.start->data);
                pop(&origin);
                display(&origin, &aux, &target);
            }
            else if(origin.start->data < target.start->data)
            {
                push(&target,origin.start->data);
                pop(&origin);
                display(&origin, &aux, &target);
            }
            else
            {
                push(&origin,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
        }
        if(i%3 == 2)
        {
            if(origin.size == 0)
            {
                push(&origin,aux.start->data);
                pop(&aux);
                display(&origin, &aux, &target);
            }
            else if(aux.size == 0)
            {
                push(&aux,origin.start->data);
                pop(&origin);
                display(&origin, &aux ,&target);
            }
            else if(origin.start->data < aux.start->data)
            {
                push(&aux,origin.start->data);
                pop(&origin);
                display(&origin, &aux, &target);
            }
            else
            {
                push(&origin,aux.start->data);
                pop(&aux);
                display(&origin, &aux, &target);
            }
        }
        if(i%3 == 0)
        {
            if(aux.size == 0)
            {
                push(&aux,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
            else if(aux.size == 0)
            {
                push(&target,aux.start->data);
                pop(&aux);
                display(&origin, &aux ,&target);
            }
            else if(aux.start->data < target.start->data)
            {
                push(&target,aux.start->data);
                pop(&aux);
                display(&origin, &aux, &target);
            }
            else
            {
                push(&aux,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
        }
    }
    return 0;
}
