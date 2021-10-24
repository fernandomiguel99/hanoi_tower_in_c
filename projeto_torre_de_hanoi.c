// Projeto: Pilha Dinâmica - Torre de Hanoi
// Aluno: Fernando Miguel D'Andrea Lima RA:11.118.771-2
// link do vídeo: https://youtu.be/z5uH9tE_iiQ

#include <stdio.h>      //inclui as bibliotecas utilizadas
#include <stdlib.h>
#include <string.h>

struct Node             //define a estrutura do Noh
{
    int data;
    struct Node *next_node;
};

struct List             //define a estrutura da lista
{
    struct Node *start;
    struct Node *end;
    int size;
};

void initialize(struct List *list)    //funcao que inicializa a lista com o valor inicial e final igual a vazio e com um tamanho de lista igual a zero
{
    list->start = NULL;
    list->end = NULL;
    list->size = 0;
}

void push(struct List *list, int value)                     //funcao que envia um valor para o topo de uma lista
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

void pop(struct List *list)             //funcao que retira o valor do topo de uma lista
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

void display(struct List *list1, struct List *list2, struct List *list3)       //funcao que mostra graficamente as 3 listas como se fossem os pinos das torres de hanoi
{
    struct Node *aux1 = list1->start;          //cria nós auxiliares que recebem os valores das listas para representar graficamente
    struct Node *aux2 = list2->start;
    struct Node *aux3 = list3->start;
    printf("\n|\t|\t|\n");
    while(aux1 != NULL || aux2 != NULL || aux3 != NULL)     //logica de repeticao que verifica o topo de cada um dos pinos para verificar como será o display grafico da estrutra de dados
    {
        if(aux1 != NULL && aux2 == NULL && aux3 != NULL)  //logica que se repete para todas as opcoes possiveis, verifica quais das colunas possui um valor e as printa, caso nao tenha valor é colocado um "|" para simbolizar um pino vazio
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
    puts("=================");          //base dos pinos da torre de hanoi
    puts("origem auxiliar destino\n");
    free(aux1);         //libera as 3 variaveis utilizadas para a representacao grafica
    free(aux2);
    free(aux3);
}

int main()  //inicia o main do programa
{
    struct List origin, aux, target;    //cria as 3 listas: origem, auxiliar e destino
    int n_disk;                         //variavel que armazena o numero de discos na torre inicial
    int total_mov=(2^n_disk-1);         //variavel que calcula o numero de movimentos validos minimos para resolver o problema

    initialize(&origin);        //utilizando a funcao initialize inicia as 3 listas
    initialize(&aux);
    initialize(&target);
    puts("Digite a quantidade de discos do pino inicial:");  //o programa pede ao usuario a quantidade de pinos a ser utilizado
    scanf(" %d", &n_disk);                                   //o programa recebe a quantidade de discos

    while(n_disk>0)                 //loop que passa os valores dos discos para o pino inicial
    {
        push(&origin, n_disk);
        n_disk = n_disk - 1;
    }
    
    puts("\n");
    display(&origin, &aux, &target);   //display representativo dos 3 pinos no estado inicial

    for(int i = 1; i <= total_mov; i++)  //metodo iterativo de resolucao do problema
    {
        if(i%3 == 1)   //verifica se o movimento é valido para o pino original para o destino
        {
            if(origin.size == 0)  //verifica se o tamanho do pino original é igual a zero, se sim recebe o valor do pino destino
            {
                push(&origin,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
            else if(target.size == 0)  //verifica se o tamanho do pino destino é igual a zero, se sim recebe o valor do pino original
            {
                push(&target,origin.start->data);
                pop(&origin);
                display(&origin, &aux, &target);
            }
            else if(origin.start->data < target.start->data)  //verifica se o valor do topo do pino original é menor que o valor do topo do pino destino, se sim o pino destino recebe o valor do pino original
            {
                push(&target,origin.start->data);
                pop(&origin);
                display(&origin, &aux, &target);
            }
            else  //caso nenhuma outra opcao seja valida, o pino origem recebe o valor do topo do pino destino
            {
                push(&origin,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
        }
        if(i%3 == 2)   //verifica se o movimento é valido para o pino original para o auxiliar
        {
            if(origin.size == 0)  //verifica se o tamanho do pino original é igual a zero, se sim recebe o valor do pino auxiliar
            {
                push(&origin,aux.start->data);
                pop(&aux);
                display(&origin, &aux, &target);
            }
            else if(aux.size == 0)  //verifica se o tamanho do pino auxiliar é igual a zero, se sim recebe o valor do pino original
            {
                push(&aux,origin.start->data);
                pop(&origin);
                display(&origin, &aux ,&target);
            }
            else if(origin.start->data < aux.start->data)  //verifica se o valor do topo do pino original é menor que o valor do topo do pino auxiliar, se sim o pino auxiliar recebe o valor do pino original
            {
                push(&aux,origin.start->data);
                pop(&origin);
                display(&origin, &aux, &target);
            }
            else  //caso nenhuma outra opcao seja valida, o pino origem recebe o valor do topo do pino auxiliar
            {
                push(&origin,aux.start->data);
                pop(&aux);
                display(&origin, &aux, &target);
            }
        }
        if(i%3 == 0)   //verifica se o movimento é valido para o pino auxiliar para o destino
        {
            if(aux.size == 0)  //verifica se o tamanho do pino auxiliar é igual a zero, se sim recebe o valor do pino destino
            {
                push(&aux,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
            else if(target.size == 0)  //verifica se o tamanho do pino destino é igual a zero, se sim recebe o valor do pino auxiliar
            {
                push(&target,aux.start->data);
                pop(&aux);
                display(&origin, &aux ,&target);
            }
            else if(aux.start->data < target.start->data)  //verifica se o valor do topo do pino auxiliar é menor que o valor do topo do pino auxiliar, se sim o pino destino recebe o valor do pino auxiliar
            {
                push(&target,aux.start->data);
                pop(&aux);
                display(&origin, &aux, &target);
            }
            else  //caso nenhuma outra opcao seja valida, o pino auxiliar recebe o valor do topo do pino destino
            {
                push(&aux,target.start->data);
                pop(&target);
                display(&origin, &aux, &target);
            }
        }
    }
    return 0;
}
