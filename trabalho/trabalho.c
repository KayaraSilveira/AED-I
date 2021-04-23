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

    int i;
    int j;
    int count;
    int escolha;
    char nomeAux[30];
    Nodo *pAux, *pAuxii, *pAuxiii;
    unsigned int nCount; 
    Nodo *pFirst;
    Nodo *pLast;
    Nodo *pFirstFila;
    Nodo *pLastFila;
    unsigned int nCountFila;

}Variavel;  //variaveis e sentinela


void *incluir (Variavel *pBuffer);
void *apagar (Variavel *pBuffer);
void buscar (Variavel *pBuffer);
void sair (Variavel *pBuffer);
void menuOrdenar (Variavel *pBuffer);
void alfabetica (Variavel *pBuffer);
void alfabeticaDecrescente (Variavel *pBuffer);
void idade (Variavel *pBuffer);
void idadeDecrescente (Variavel *pBuffer);
void listarFilaOrdenada (Variavel *pBuffer);
void PUSHAlfabetica (Variavel *pBuffer);
void PUSHlfabeticaDecrescente (Variavel *pBuffer);
void PUSHIdade (Variavel *pBuffer);
void PUSHIdadeDecrescente (Variavel *pBuffer);



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
                menuOrdenar(pBuffer);
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
        pNovo->pPrevious = pBuffer->pLast; 
        pBuffer->pLast->pNext = pNovo;  
    }

    pBuffer->pLast = pNovo;
    pBuffer->nCount += 1;
    printf("Nome incluido\n");

}

void *apagar (Variavel *pBuffer) { 

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
                    pBuffer->pAuxiii = pBuffer->pAux->pNext; 
                    pBuffer->pAuxiii->pPrevious = NULL;
                }
                else {
                    if(pBuffer->pAux == pBuffer->pLast) {
                        pBuffer->pLast = pBuffer->pAux->pPrevious;
                        pBuffer->pAuxii = pBuffer->pAux->pPrevious; 
                        pBuffer->pAuxii->pNext = NULL;
                    }
                    else {
                        pBuffer->pAuxii = pBuffer->pAux->pPrevious; 
                        pBuffer->pAuxii->pNext = pBuffer->pAux->pNext; 
                        pBuffer->pAuxiii = pBuffer->pAux->pNext; 
                        pBuffer->pAuxiii->pPrevious = pBuffer->pAux->pPrevious; 
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

void sair (Variavel *pBuffer) {

    pBuffer->pAux = pBuffer->pFirst;

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i += 1) {
        
        pBuffer->pAuxii = pBuffer->pAux;
        pBuffer->pAux = pBuffer->pAux->pNext;
        free(pBuffer->pAuxii);

    }
    free(pBuffer);
    exit(1);
}

void menuOrdenar (Variavel *pBuffer) {

    printf("Voce deseja ordenar por:\n 1)Ordem alfabetica\n 2)Ordem alfabetica decrescente\n 3)Idade crescente\n 4)Idade decrescente\n");
    scanf("%d", &pBuffer->escolha);

    switch(pBuffer->escolha){
            case 1: 
                alfabetica(pBuffer);
                break;
           case 2:
                alfabeticaDecrescente(pBuffer);
                break;
            case 3:
                idade(pBuffer);
                break;
            case 4:
                idadeDecrescente(pBuffer);
                break;  
        }
}

void alfabetica (Variavel *pBuffer) {

    pBuffer->pLastFila = NULL;
    pBuffer->pFirstFila = NULL;
    pBuffer->nCountFila = 0;
    pBuffer->pAux = pBuffer->pFirst; //auxiliar eh o primeiro elemento do aux

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i = pBuffer->i + 1) { //percorre toda LISTA
        PUSHAlfabetica(pBuffer);
        pBuffer->nCountFila += 1; //incrementa o contador de pessoas na FILA
        pBuffer->pAux = pBuffer->pAux->pNext; //passa pro proximo elemento da LISTA a ser colocado na FILA
    }
    listarFilaOrdenada(pBuffer);
   
}

void alfabeticaDecrescente (Variavel *pBuffer) {
    
    pBuffer->pLastFila = NULL;
    pBuffer->pFirstFila = NULL;
    pBuffer->nCountFila = 0;
    pBuffer->pAux = pBuffer->pFirst; 

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i = pBuffer->i + 1) { 
        PUSHAlfabeticaDecrescente(pBuffer);
        pBuffer->nCountFila += 1;
        pBuffer->pAux = pBuffer->pAux->pNext;
    }
    listarFilaOrdenada(pBuffer);

}

void idade (Variavel *pBuffer) {
    
    pBuffer->pLastFila = NULL;
    pBuffer->pFirstFila = NULL;
    pBuffer->nCountFila = 0;
    pBuffer->pAux = pBuffer->pFirst; 

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i = pBuffer->i + 1) { 
        PUSHIdade(pBuffer);
        pBuffer->nCountFila += 1;
        pBuffer->pAux = pBuffer->pAux->pNext;
    }
    listarFilaOrdenada(pBuffer);

}

void idadeDecrescente (Variavel *pBuffer){

    pBuffer->pLastFila = NULL;
    pBuffer->pFirstFila = NULL;
    pBuffer->nCountFila = 0;
    pBuffer->pAux = pBuffer->pFirst; 

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCount; pBuffer->i = pBuffer->i + 1) { 
        PUSHIdadeDecrescente(pBuffer);
        pBuffer->nCountFila += 1;
        pBuffer->pAux = pBuffer->pAux->pNext;
    }
    listarFilaOrdenada(pBuffer);

}

void listarFilaOrdenada (Variavel *pBuffer){

    pBuffer->pAux = pBuffer->pFirstFila;

    for(pBuffer->i = 0; pBuffer->i < pBuffer->nCountFila; pBuffer->i = pBuffer->i + 1) {
        pBuffer->pAuxii = pBuffer->pAux;
        pBuffer->pAux = pBuffer->pAux->pNext;
        printf("Nome: %s ", pBuffer->pAuxii->info.nome);
        printf("Idade: %d ", pBuffer->pAuxii->info.idade);
        printf("Telefone: %s\n", pBuffer->pAuxii->info.telefone);
        free(pBuffer->pAuxii);
    }
}

void PUSHAlfabetica (Variavel *pBuffer) {
        
    Nodo *pNovo;
    pNovo = malloc(sizeof(Nodo)); 
        
    strcpy(pNovo->info.nome, pBuffer->pAux->info.nome); //copia o elemento da LISTA a ser colocado na FILA para um pNovo
    pNovo->info.idade = pBuffer->pAux->info.idade;
    strcpy(pNovo->info.telefone, pBuffer->pAux->info.telefone);
    
    if(pBuffer->i == 0) { //testa se é a primeira pessoa da FILA
        pBuffer->pFirstFila = pNovo;
        pBuffer->pLastFila = pNovo;
        pBuffer->pFirstFila->pPrevious = NULL;
        pBuffer->pFirstFila->pNext = NULL;

    }
    else {
        pBuffer->j = pBuffer->nCountFila; 
        pBuffer->pAuxii = pBuffer->pLastFila; //segundo auxiliar que vai sempre receber o anterior ao que vai ser comparado

        if(strcmp(pNovo->info.nome, pBuffer->pAuxii->info.nome) >= 0) { //teste se ja está no local certo
            pBuffer->pAuxii->pNext = pNovo;
            pNovo->pPrevious = pBuffer->pAuxii;
            pBuffer->pLastFila = pNovo;
            pNovo->pNext = NULL;
        }

        else {
            while((pBuffer->j > 0) && (strcmp(pNovo->info.nome, pBuffer->pAuxii->info.nome) < 0)) { //loop que percorre toda FILA
                if((pBuffer->j == 1) && (pBuffer->j == pBuffer->nCountFila)){ //testa se so tem um elemento na FILA e ele vai trocar de lugar com o a ser inserido
                    pBuffer->pAuxii->pPrevious = pNovo;
                    pNovo->pNext = pBuffer->pAuxii;
                    pBuffer->pAuxii->pNext = NULL;
                    pNovo->pPrevious = NULL;
                    pBuffer->pFirstFila = pNovo;
                    pBuffer->pLastFila = pBuffer->pAuxii;    
                }

                else {
                    if(pBuffer->j == pBuffer->nCountFila){ //teste se o a ser inserido vai trocar de lugar com o ultimo da fila
                        pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                        pBuffer->pAuxiii->pNext = pNovo;
                        pNovo->pPrevious = pBuffer->pAuxiii;
                        pNovo->pNext = pBuffer->pAuxii;
                        pBuffer->pAuxii->pPrevious = pNovo;
                        pBuffer->pAuxii->pNext = NULL;
                        pBuffer->pLastFila = pBuffer->pAuxii;  
                    }

                    else {
                        if(pBuffer->j == 1){ //testa se o a ser inserido vai trocar de lugar com o primeiro da fila
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                            pNovo->pPrevious = NULL;
                            pBuffer->pFirstFila = pNovo;
                        }   

                        else { //todos os demais casos
                            pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                            pBuffer->pAuxiii->pNext = pNovo; 
                            pNovo->pPrevious = pBuffer->pAuxiii;    
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                        }
                    }
                }
                pBuffer->pAuxii = pNovo->pPrevious; //segundo auxiliar vai receber o anterior
                pBuffer->j = pBuffer->j - 1; 
            }
        }
    }
}

void PUSHAlfabeticaDecrescente (Variavel *pBuffer) {
    Nodo *pNovo;
    pNovo = malloc(sizeof(Nodo)); 
        
    strcpy(pNovo->info.nome, pBuffer->pAux->info.nome);
    pNovo->info.idade = pBuffer->pAux->info.idade;
    strcpy(pNovo->info.telefone, pBuffer->pAux->info.telefone);
    
    if(pBuffer->i == 0) {
        pBuffer->pFirstFila = pNovo;
        pBuffer->pLastFila = pNovo;
        pBuffer->pFirstFila->pPrevious = NULL;
        pBuffer->pFirstFila->pNext = NULL;

    }
    else {
        pBuffer->j = pBuffer->nCountFila;
        pBuffer->pAuxii = pBuffer->pLastFila;

        if(strcmp(pNovo->info.nome, pBuffer->pAuxii->info.nome) < 0) {
            pBuffer->pAuxii->pNext = pNovo;
            pNovo->pPrevious = pBuffer->pAuxii;
            pBuffer->pLastFila = pNovo;
            pNovo->pNext = NULL;
        }

        else {
            while((pBuffer->j > 0) && (strcmp(pNovo->info.nome, pBuffer->pAuxii->info.nome) >= 0)) {
                if((pBuffer->j == 1) && (pBuffer->j == pBuffer->nCountFila)){
                    pBuffer->pAuxii->pPrevious = pNovo;
                    pNovo->pNext = pBuffer->pAuxii;
                    pBuffer->pAuxii->pNext = NULL;
                    pNovo->pPrevious = NULL;
                    pBuffer->pFirstFila = pNovo;
                    pBuffer->pLastFila = pBuffer->pAuxii;    
                }

                else {
                    if(pBuffer->j == pBuffer->nCountFila){
                        pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                        pBuffer->pAuxiii->pNext = pNovo;
                        pNovo->pPrevious = pBuffer->pAuxiii;
                        pNovo->pNext = pBuffer->pAuxii;
                        pBuffer->pAuxii->pPrevious = pNovo;
                        pBuffer->pAuxii->pNext = NULL;
                        pBuffer->pLastFila = pBuffer->pAuxii;  
                    }

                    else {
                        if(pBuffer->j == 1){
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                            pNovo->pPrevious = NULL;
                            pBuffer->pFirstFila = pNovo;
                        }   

                        else {
                            pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                            pBuffer->pAuxiii->pNext = pNovo; 
                            pNovo->pPrevious = pBuffer->pAuxiii;    
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                        }
                    }
                }
                pBuffer->pAuxii = pNovo->pPrevious;
                pBuffer->j = pBuffer->j - 1;
            }
        }
    }   
}

void PUSHIdade (Variavel *pBuffer) {

    Nodo *pNovo;
    pNovo = malloc(sizeof(Nodo)); 
        
    strcpy(pNovo->info.nome, pBuffer->pAux->info.nome);
    pNovo->info.idade = pBuffer->pAux->info.idade;
    strcpy(pNovo->info.telefone, pBuffer->pAux->info.telefone);
    
    if(pBuffer->i == 0) {
        pBuffer->pFirstFila = pNovo;
        pBuffer->pLastFila = pNovo;
        pBuffer->pFirstFila->pPrevious = NULL;
        pBuffer->pFirstFila->pNext = NULL;

    }
    else {
        pBuffer->j = pBuffer->nCountFila;
        pBuffer->pAuxii = pBuffer->pLastFila;

        if(pNovo->info.idade >= pBuffer->pAuxii->info.idade) {
            pBuffer->pAuxii->pNext = pNovo;
            pNovo->pPrevious = pBuffer->pAuxii;
            pBuffer->pLastFila = pNovo;
            pNovo->pNext = NULL;
        }

        else {
            while((pBuffer->j > 0) && (pNovo->info.idade < pBuffer->pAuxii->info.idade)) {
                if((pBuffer->j == 1) && (pBuffer->j == pBuffer->nCountFila)){
                    pBuffer->pAuxii->pPrevious = pNovo;
                    pNovo->pNext = pBuffer->pAuxii;
                    pBuffer->pAuxii->pNext = NULL;
                    pNovo->pPrevious = NULL;
                    pBuffer->pFirstFila = pNovo;
                    pBuffer->pLastFila = pBuffer->pAuxii;    
                }

                else {
                    if(pBuffer->j == pBuffer->nCountFila){
                        pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                        pBuffer->pAuxiii->pNext = pNovo;
                        pNovo->pPrevious = pBuffer->pAuxiii;
                        pNovo->pNext = pBuffer->pAuxii;
                        pBuffer->pAuxii->pPrevious = pNovo;
                        pBuffer->pAuxii->pNext = NULL;
                        pBuffer->pLastFila = pBuffer->pAuxii;  
                    }

                    else {
                        if(pBuffer->j == 1){
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                            pNovo->pPrevious = NULL;
                            pBuffer->pFirstFila = pNovo;
                        }   

                        else {
                            pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                            pBuffer->pAuxiii->pNext = pNovo; 
                            pNovo->pPrevious = pBuffer->pAuxiii;    
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                        }
                    }
                }
                pBuffer->pAuxii = pNovo->pPrevious;
                pBuffer->j = pBuffer->j - 1;
            }
        }
    }
}

void PUSHIdadeDecrescente (Variavel *pBuffer) {
    Nodo *pNovo;
    pNovo = malloc(sizeof(Nodo)); 
        
    strcpy(pNovo->info.nome, pBuffer->pAux->info.nome);
    pNovo->info.idade = pBuffer->pAux->info.idade;
    strcpy(pNovo->info.telefone, pBuffer->pAux->info.telefone);
    
    if(pBuffer->i == 0) {
        pBuffer->pFirstFila = pNovo;
        pBuffer->pLastFila = pNovo;
        pBuffer->pFirstFila->pPrevious = NULL;
        pBuffer->pFirstFila->pNext = NULL;

    }
    else {
        pBuffer->j = pBuffer->nCountFila;
        pBuffer->pAuxii = pBuffer->pLastFila;

        if(pNovo->info.idade <= pBuffer->pAuxii->info.idade) {
            pBuffer->pAuxii->pNext = pNovo;
            pNovo->pPrevious = pBuffer->pAuxii;
            pBuffer->pLastFila = pNovo;
            pNovo->pNext = NULL;
        }

        else {
            while((pBuffer->j > 0) && (pNovo->info.idade > pBuffer->pAuxii->info.idade)) {
                if((pBuffer->j == 1) && (pBuffer->j == pBuffer->nCountFila)){
                    pBuffer->pAuxii->pPrevious = pNovo;
                    pNovo->pNext = pBuffer->pAuxii;
                    pBuffer->pAuxii->pNext = NULL;
                    pNovo->pPrevious = NULL;
                    pBuffer->pFirstFila = pNovo;
                    pBuffer->pLastFila = pBuffer->pAuxii;    
                }

                else {
                    if(pBuffer->j == pBuffer->nCountFila){
                        pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                        pBuffer->pAuxiii->pNext = pNovo;
                        pNovo->pPrevious = pBuffer->pAuxiii;
                        pNovo->pNext = pBuffer->pAuxii;
                        pBuffer->pAuxii->pPrevious = pNovo;
                        pBuffer->pAuxii->pNext = NULL;
                        pBuffer->pLastFila = pBuffer->pAuxii;  
                    }

                    else {
                        if(pBuffer->j == 1){
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                            pNovo->pPrevious = NULL;
                            pBuffer->pFirstFila = pNovo;
                        }   

                        else {
                            pBuffer->pAuxiii = pBuffer->pAuxii->pPrevious;
                            pBuffer->pAuxiii->pNext = pNovo; 
                            pNovo->pPrevious = pBuffer->pAuxiii;    
                            pBuffer->pAuxiii = pNovo->pNext;
                            pBuffer->pAuxiii->pPrevious = pBuffer->pAuxii;
                            pBuffer->pAuxii->pNext = pBuffer->pAuxiii;
                            pBuffer->pAuxii->pPrevious = pNovo;
                            pNovo->pNext = pBuffer->pAuxii;
                        }
                    }
                }
                pBuffer->pAuxii = pNovo->pPrevious;
                pBuffer->j = pBuffer->j - 1;
            }
        }
    }
}

