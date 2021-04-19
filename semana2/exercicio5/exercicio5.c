#include <stdio.h> 
#include <stdlib.h>

typedef struct {
    char nome[30];
    int idade;
    int altura;
}Pessoa; 


Pessoa *adicionar (Pessoa *p, int tam);
void sair (Pessoa *p, int tam);

int main () {

Pessoa *p = NULL;
int escolha, tam = 0;

do{
        printf("O que voce deseja fazer?\n 1)Adicionar\n 2)Sair\n");
        scanf("%d",&escolha);
        
        switch(escolha){
            case 1: 
               p = adicionar(p, tam);
               tam++;
                break;
            case 2:
                sair(p, tam);
                break;
        }
    }  while(escolha != 2); 

    return 0;
}

Pessoa *adicionar (Pessoa *p, int tam) {
    if(!p) {
        p = (Pessoa*)malloc(sizeof(Pessoa));
    }
    else {
        p = (Pessoa*)realloc(p, (tam + 1) * sizeof(Pessoa));
    }

    printf("Digite o nome a ser adiconado: ");
    scanf("%s", p[tam].nome);
    printf("Digite a idade: ");
    scanf("%d", &p[tam].idade); 
    printf("Digite a altura: ");
    scanf("%d", &p[tam].altura);

    return p;
}

void sair (Pessoa *p, int tam) {

if (p != NULL) {
       for(int i = 0; i < tam; i++){
            printf("Nome: %s ", p[i].nome );
            printf("Idade: %d ", p[i].idade);
            printf("Altura: %d\n", p[i].altura);
       }
    } 
    else {
        printf("A lista esta vazia\n");
    }
    free(p);
    exit(1);

}