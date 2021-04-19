#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct {

    int i, j, escolha;
    unsigned int nCount; 
    Nodo *pFirst;
    Nodo *pLast;

}Variavel;  //variaveis e sentinela

typedef struct {

    Pessoa info;
    struct Nodo *pPrevious;
    struct Nodo *pNext;

}Nodo;  //nó

typedef struct {

    char nome[30];
    int idade;
    char telefone[15];

}Pessoa; //info

void *incluir (Variavel *pBuffer);
void *apagar (Variavel *pBuffer);
void buscar (Variavel *pBuffer);
void listar (Variavel *pBuffer);
void sair (Variavel *pBuffer);

int main () {

    Variavel *pBuffer = NULL;
    pBuffer = malloc(sizeof(Variavel));
    pBuffer->pFirst = NULL;
    pBuffer->pLast = NULL;

    do{
       
        printf("O que voce deseja fazer?\n 1)Incluir\n 2)Apagar\n 3)Buscar\n 4)Listar\n 5)Sair\n");
        scanf("%d", &pBuffer->escolha);

        
        switch(pBuffer->escolha){
            case 1: 
                pBuffer = incluir(pBuffer);
                break;
           case 2:
                pBuffer = apagar(pBuffer);
                break;
            case 3:
                buscar(pBuffer);
                break;
            case 4:
                listar(pBuffer);
                break;
            case 5:
                sair(pBuffer);
                break;
        }
    }  while(pBuffer->escolha != 5); 

    return 0;
}

void *incluir (Variavel *pBuffer) {
    Nodo *pNovo;
    pNovo = (Nodo *) malloc(sizeof(Nodo));
    pNovo->pNext = NULL;
    
    printf("Digite o nome a ser adicionado: ");
    scanf("%s", pNovo->info->nome);

    printf("Digite a idade: ");
    scanf("%d", pNovo->info->idade);

    printf("Digite o telefone: ");
    scanf("%s", pNovo->info->telefone);


    if (!pBuffer->pFirst) {
        pBuffer->pFirst = pNovo;
        pBuffer->pLast = pNovo;
        pBuffer->pFirst->pPrevious = NULL;
    }
    else { 
        pNovo->pPrevious = pBuffer->pLast; //anterior do pNovo vai ser o antigo ultimo
        pBuffer->pLast->pNext = pNovo; //antigo ultimo next recebe o endereço do novo ultimo
        pBuffer->pLast = pNovo;  
    }

}