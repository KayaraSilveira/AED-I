#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    int idade;
    int telefone;
}Pessoa; 
Pessoa p[10];

void *incluir (void *pBuffer);
void *apagar (void *pBuffer);
void buscar (void *pBuffer);
void listar (void *pBuffer);
void sair (void *pBuffer);

int main () {
    //primeira posição: int de escolha
    //segunda posição: int de tamanho incrementado no incluir decrementado no apagar
    //terceira posição: i usado dentro do for
    //quarta posição: j usado dentro de um segundo for
    //quinta posição: count para verificar se o nome foi encontrado
    //sexta posição: char auxiliar para ler nomes a serem buscados ou apagados
    void *pBuffer = NULL;
    pBuffer = malloc(5 * sizeof(int) + 30 * sizeof(char));
    *(int *)(pBuffer + (1) * sizeof(int)) = 0;
    if(!pBuffer) {
        printf("Memoria insuficiente\n");
        exit(1);
    }
    do{
       
        printf("O que voce deseja fazer?\n 1)Incluir\n 2)Apagar\n 3)Buscar\n 4)Listar\n 5)Sair\n");
        scanf("%d",&*(int *)pBuffer);

        switch(*(int *)pBuffer){
            case 1: 
                pBuffer = incluir(pBuffer);
                break;
           case 2:
                printf("digite o nome que voce deseja apagar:");
                scanf("%s", (char *)pBuffer + (5) * sizeof(int));
                pBuffer = apagar(pBuffer);
                break;
            case 3:
                printf("digite o nome que voce deseja buscar:");
                scanf("%s", (char *)pBuffer + (5) * sizeof(int));
                buscar(pBuffer);
                break;
            case 4:
                listar(pBuffer);
                break;
            case 5:
                sair(pBuffer);
                break;
        }
    }  while(*(int *)pBuffer != 5); 
    return 0;

}
void *incluir (void *pBuffer) {

    printf("Digite o nome a ser adicionado: ");
    scanf("%s", p[*(char *)(pBuffer + (1) * sizeof(int))].nome);

    printf("Digite a idade: ");
    scanf("%d", &p[*(int *)(pBuffer + (1) * sizeof(int))].idade);  

    printf("Digite o telefone: ");
    scanf("%d", &p[*(int *)(pBuffer + (1) * sizeof(int))].telefone);

    *(int *)(pBuffer + (1) * sizeof(int)) = *(int *)(pBuffer + (1) * sizeof(int)) + 1;

    return pBuffer;
}

void *apagar (void *pBuffer) {
   *(int *)(pBuffer + (4) * sizeof(int)) = 0;
    for(*(int *)(pBuffer + (2) * sizeof(int)) = 0; *(int *)(pBuffer + (2) * sizeof(int)) < *(int *)(pBuffer + (1) * sizeof(int)); *(int *)(pBuffer + (2) * sizeof(int)) += 1) {
        if(strcmp(p[*(int *)(pBuffer + (2) * sizeof(int))].nome, (char *)(pBuffer + (5) * sizeof(int))) == 0) {
            for(*(int *)(pBuffer + (3) * sizeof(int)) = *(int *)(pBuffer + (2) * sizeof(int)); *(int *)(pBuffer + (3) * sizeof(int)) < (*(int *)(pBuffer + (1) * sizeof(int)) - 1); *(int *)(pBuffer + (3) * sizeof(int)) += 1) {
               strcpy(p[*(int *)(pBuffer + (3) * sizeof(int) )].nome, p[((*(int *)(pBuffer + (3) * sizeof(int))) + 1)].nome);
                p[*(int *)(pBuffer + (3) * sizeof(int))].idade = p[((*(int *)(pBuffer + (3) * sizeof(int))) + 1)].idade;
                p[*(int *)(pBuffer + (3) * sizeof(int) )].telefone = p[((*(int *)(pBuffer + (3) * sizeof(int))) + 1)].telefone;
            }
            *(int *)(pBuffer + (4) * sizeof(int)) += 1;
        }   
    }
    if(*(int *)(pBuffer + (4) * sizeof(int)) == 0) {
        printf("O nome nao foi encontrado\n");
    }
    else {
        *(int *)(pBuffer + (1) * sizeof(int)) -= 1;
    }
    
    return pBuffer;
}
void buscar (void *pBuffer) {

    *(int *)(pBuffer + (4) * sizeof(int)) = 0;
    if(*(int *)(pBuffer + (1) * sizeof(int)) != 0) { 
        for(*(int *)(pBuffer + (2) * sizeof(int)) = 0; *(int *)(pBuffer + (2) * sizeof(int)) < *(int *)(pBuffer + (1) * sizeof(int)); *(int *)(pBuffer + (2) * sizeof(int)) += 1) {
            if(strcmp(p[*(int *)(pBuffer + (2) * sizeof(int))].nome, (char *)(pBuffer + (5) * sizeof(int))) == 0) {
                printf("Nome: %s ", p[*(char *)(pBuffer + (2) * sizeof(int))].nome);
                printf("Idade: %d ", p[*(int *)(pBuffer + (2) * sizeof(int))].idade);
                printf("Telefone: %d\n", p[*(int *)(pBuffer + (2) * sizeof(int))].telefone);
                *(int *)(pBuffer + (4) * sizeof(int)) += 1;
                } 
            }
        
        if(*(int *)(pBuffer + (4) * sizeof(int)) == 0) {
            printf("O nome nao foi encontrado\n");
        }
    }
    else {
        printf("A lista esta vazia\n");
        }

}
void listar (void *pBuffer) {
    
    if(*(int *)(pBuffer + (1) * sizeof(int)) != 0) {
        for(*(int *)(pBuffer + (2) * sizeof(int)) = 0; (*(int *)(pBuffer + (2) * sizeof(int))) < (*(int *)(pBuffer + (1) * sizeof(int))); (*(int *)(pBuffer + (2) * sizeof(int)))++)  {
             printf("Nome: %s ", p[*(char *)(pBuffer + (2) * sizeof(int))].nome);
             printf("Idade: %d ", p[*(int *)(pBuffer + (2) * sizeof(int))].idade);
             printf("Telefone: %d\n", p[*(int *)(pBuffer + (2) * sizeof(int))].telefone);
        }
    }
    else {
        printf("A lista esta vazia\n");
    }

}
void sair (void *pBuffer) {
    free(pBuffer);
    exit(1);

}
