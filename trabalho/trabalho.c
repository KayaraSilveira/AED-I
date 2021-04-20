#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct {

    char nome[30];
    int idade;
    char telefone[15];

}Pessoa; //info

typedef struct {

    Pessoa info;
    struct Nodo *pPrevious;
    struct Nodo *pNext;

}Nodo;  //nó

typedef struct {

    int i, j, escolha;
    char nomeAux[30];
    Nodo *pAux, *pAuxii;
    unsigned int nCount; 
    Nodo *pFirst;
    Nodo *pLast;

}Variavel;  //variaveis e sentinela



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
    pBuffer->nCount = 0;

    do{
       
        printf("O que voce deseja fazer?\n 1)Incluir\n 2)Apagar\n 3)Buscar\n 4)Listar\n 5)Sair\n");
        scanf("%d", &pBuffer->escolha);

        
        switch(pBuffer->escolha){
            case 1: 
                incluir(pBuffer);
                break;
           case 2:
                apagar(pBuffer);
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
    scanf("%s", pNovo->info.nome);

    printf("Digite a idade: ");
    scanf("%d", &pNovo->info.idade);

    printf("Digite o telefone: ");
    scanf("%s", pNovo->info.telefone);
  
    if (!pBuffer->pFirst) {
        pBuffer->pFirst = pNovo;
        pBuffer->pFirst->pPrevious = NULL;
    }
    else { 
        pNovo->pPrevious = pBuffer->pLast; //anterior do pNovo vai ser o antigo ultimo
        pBuffer->pLast->pNext = pNovo; //antigo ultimo next recebe o endereço do novo ultimo 
    }

    pBuffer->pLast = pNovo;
    pBuffer->nCount += 1;

}

void *apagar (Variavel *pBuffer) {

}

void buscar (Variavel *pBuffer) {

}

void listar (Variavel *pBuffer) {

    pBuffer->pAux = pBuffer->pFirst;

    if(pBuffer->nCount != 0) {
        for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i += 1) {
            printf("Nome: %s ", pBuffer->pAux->info.nome);
            printf("Idade: %d ", pBuffer->pAux->info.idade);
            printf("Telefone: %s\n", pBuffer->pAux->info.telefone);
            pBuffer->pAux = pBuffer->pAux->pNext;

        }
    }
    else 
        printf("A lista esta vazia\n");

}

void sair (Variavel *pBuffer) {

    pBuffer->pAux = pBuffer->pFirst;

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i += 1) {
        
        pBuffer->pAuxii = pBuffer->pAux;
        pBuffer->pAux = pBuffer->pAux->pNext;
        free(pBuffer->pAuxii);

    }

    free(pBuffer);

}
