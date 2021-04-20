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

    int i, count, escolha;
    char nomeAux[30];
    Nodo *pAux, *pAuxii, *pAuxiii;
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
    pNovo = malloc(sizeof(Nodo));
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
    printf("Nome incluido\n");

}

void *apagar (Variavel *pBuffer) { //apaga só o primeiro, nao sei se deveria ser assim ou apagar por nome

   /* if(pBuffer->nCount != 0) {
        pBuffer->pAux = pBuffer->pFirst;
        pBuffer->pFirst = pBuffer->pFirst->pNext;
        free(pBuffer->pAux);
        printf("Nome apagado\n");
        pBuffer->nCount -= 1;
    }
    else 
        printf("A lista esta vazia\n");
        */
    printf("Digite o nome que voce deseja apagar: ");
    scanf("%s", pBuffer->nomeAux);

    pBuffer->pAux = pBuffer->pFirst;
    pBuffer->count = 0;

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i += 1) {
        if(strcmp(pBuffer->pAux->info.nome, pBuffer->nomeAux) == 0) { 
            
            pBuffer->count += 1; 

            if(pBuffer->nCount == 1){
                pBuffer->pFirst = NULL;
                pBuffer->pLast = NULL;
            }
            else {
                if(pBuffer->pAux == pBuffer->pFirst) {
                    pBuffer->pFirst = pBuffer->pAux->pNext;
                    pBuffer->pAuxiii = pBuffer->pAux->pNext; //guarda o proximo no auxiii
                    pBuffer->pAuxiii->pPrevious = NULL;
                }
                else {
                    if(pBuffer->pAux == pBuffer->pLast) {
                        pBuffer->pLast = pBuffer->pAux->pPrevious;
                        pBuffer->pAuxii = pBuffer->pAux->pPrevious; //guarda o anterior no auxii
                        pBuffer->pAuxii->pNext = NULL;
                    }
                    else {
                        pBuffer->pAuxii = pBuffer->pAux->pPrevious; //guarda o anterior no auxii
                        pBuffer->pAuxii->pNext = pBuffer->pAux->pNext; //aponta o proximo do auxii pro proximo após o apagado
                        pBuffer->pAuxiii = pBuffer->pAux->pNext; //guarda o proximo no auxiii
                        pBuffer->pAuxiii->pPrevious = pBuffer->pAux->pPrevious; //aponta o anterior do auxiii pro anterior antes do apagado
                    }
                } 
            }
            free(pBuffer->pAux);
            pBuffer->nCount -= 1;
            printf("Nome apagado\n");
            pBuffer->i = pBuffer->nCount;
            }
        else 
            pBuffer->pAux = pBuffer->pAux->pNext;   
    }

    if(pBuffer->count == 0)
        printf("O nome nao foi encontrado\n");

}

void buscar (Variavel *pBuffer) {

    pBuffer->pAux = pBuffer->pFirst;
    pBuffer->count = 0;

    printf("Digite o nome que voce procura: ");
    scanf("%s", pBuffer->nomeAux);

     for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i += 1) {
        if(strcmp(pBuffer->pAux->info.nome, pBuffer->nomeAux) == 0) {
            printf("Nome: %s ", pBuffer->pAux->info.nome);
            printf("Idade: %d ", pBuffer->pAux->info.idade);
            printf("Telefone: %s\n", pBuffer->pAux->info.telefone);
            pBuffer->count += 1;
        }
        pBuffer->pAux = pBuffer->pAux->pNext;
     }
    
    if(pBuffer->count == 0)
        printf("O nome nao foi encontrado\n");

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


