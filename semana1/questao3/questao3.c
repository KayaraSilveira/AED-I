#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


void *incluir (void *pBuffer);
void *apagar (void *pBuffer);
void buscar (void *pBuffer);
void listar (void *pBuffer);
void sair (void *pBuffer);

int main () {
    void *pBuffer = NULL;

    int escolha;

        do{
       
        printf("O que voce deseja fazer?\n 1)Incluir\n 2)Apagar\n 3)Buscar\n 4)Listar\n 5)Sair\n");
        scanf("%d",&escolha);

        
        switch(escolha){
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
    }  while(escolha != 5); 
    return 0;

}

void *incluir (void *pBuffer) {
    if (!pBuffer) {
        pBuffer = malloc(sizeof(int));
        *(int *)pBuffer = 0;

    }
    pBuffer = (char*)realloc(pBuffer, ( (1 * sizeof(int)) + (( 25 * sizeof(char)) * ((*(int*)(pBuffer)) + 1)) ) );
    printf("Digite o nome a ser adicionado: ");
    scanf("%s", (char *)pBuffer + sizeof(int) + (25 * sizeof(char)) * (*(int*)(pBuffer)));
    getchar();
    
    printf("Digite a idade: ");
    scanf("%s", (char *)pBuffer + sizeof(int) + 10 * sizeof(char) + (25 * sizeof(char)) * (*(int*)(pBuffer)));  
    getchar();

    printf("Digite o telefone (apenas numeros com o DDD): ");
    scanf("%s", (char *)pBuffer + sizeof(int) + 13 * sizeof(char) + (25 * sizeof(char)) * (*(int*)(pBuffer)));
    getchar();

    
    if(!pBuffer) {
        printf("Memoria insuficiente");
        exit(1);
        }
    *(int *)pBuffer = *(int *)pBuffer + 1;
    return pBuffer;
}


void *apagar (void *pBuffer) {
    char nome[10], *novo_pBuffer = NULL;
    int count = 0;

    printf("Digite o nome que voce quer apagar: ");
    scanf("%s", nome);
    getchar();

    for(int i = 0; i < *(int *)pBuffer; i++) { //percorre a quantidade de pessoas
        if(strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 25 ) * i), nome) != 0) { //compara o nome lido com o nome da pessoa i
            if (novo_pBuffer == NULL) {    //se o novo_pBuffer nao existe ele aloca um 
                novo_pBuffer = (char*)malloc( (1 * sizeof(int)) + 25 * sizeof(char) ); //vai alocar pra 1 inteiro e 25 char
                *(int *)novo_pBuffer = 1; //diz que a quantidade de pessoas é 1
                strcpy((char *)novo_pBuffer + sizeof(int), (char *)(pBuffer + sizeof(int) + (25 * sizeof(char) * i))); //copia o conteudo do pBuffer na pessoa i pra primeira pessoa do novo_pBuffer 
                strcpy((char *)novo_pBuffer + sizeof(int) + 10 * sizeof(char), (char *)(pBuffer + sizeof(int) + 10 * sizeof(char) + (25 * sizeof(char) * i)));
                strcpy((char *)novo_pBuffer + sizeof(int) + 13 * sizeof(char) , (char *)(pBuffer + sizeof(int) + 13 * sizeof(char) + (25 * sizeof(char) * i)));
             } else { //se ja existe
                novo_pBuffer = (char*)realloc(novo_pBuffer, ( (1 * sizeof(int)) + (( 25 * sizeof(char)) * ((*(int*)(novo_pBuffer)) + 1)) ) ); //realoca pro tamanho de 1 int + a quantidade de pessoas existentes + 1 char
                strcpy((char *)novo_pBuffer + sizeof(int) + (sizeof(char) * 25 * (*(int *)novo_pBuffer)), (char *)(pBuffer + sizeof(int) + (25 * sizeof(char) * i))); //copia o conteudo do p_Buffer na pessoa i para a pessoa da quantidade de pessoas do novo_pBuffer
                strcpy((char *)novo_pBuffer + sizeof(int) + 10 * sizeof(char) + (sizeof(char) * 25 * (*(int *)novo_pBuffer)), (char *)(pBuffer + sizeof(int) + 10 * sizeof(char) + (25 * sizeof(char) * i)));
                strcpy((char *)novo_pBuffer + sizeof(int) + 13 * sizeof(char) + (sizeof(char) * 25 * (*(int *)novo_pBuffer)), (char *)(pBuffer + sizeof(int) + 13 * sizeof(char) + (25 * sizeof(char) * i)));
                *(int *)novo_pBuffer = *(int *)novo_pBuffer + 1; //incrementa +1 a quantidade de pessoas
             }

        }
        else { 
            count++; //conta se alguma pessoa nao foi copiada ou seja foi removida
            }
        }

        if(count == 0) {  //se ninguem foi removido
            printf("O nome nao foi encontrado\n"); //nao encontrou o nome
            free(novo_pBuffer);
        }
        else {
            if (!novo_pBuffer) 
                *(int *)pBuffer = *(int *)pBuffer - 1;
            else
                *(int *)pBuffer = *(int *)novo_pBuffer;
            
            if(*(int *)pBuffer == 0) {  //verifica se a lista ficou vazia
                free(novo_pBuffer);
                free(pBuffer);
                return NULL;
            }

            else {
                pBuffer = realloc(pBuffer,(1 * sizeof(int)) + (( 25 * sizeof(char)) * ((*(int*)(pBuffer))))); //realoca o pBuffer pro tamanho de um inteiro + 25 vezes a quantidade de pessoas char
                for(int i = 0; i < *(int *)pBuffer; i++) {
                    strcpy((char *)pBuffer + sizeof(int) + (25 * sizeof(char)) * i, (char *)novo_pBuffer + sizeof(int) + (25 * sizeof(char)) * i );
                    strcpy((char *)pBuffer + sizeof(int) + 10 * sizeof(char) + (25 * sizeof(char)) * i, (char *)novo_pBuffer + sizeof(int) + 10 * sizeof(char) + (25 * sizeof(char)) * i );
                    strcpy((char *)pBuffer + sizeof(int) + 13 * sizeof(char) + (25 * sizeof(char)) * i, (char *)novo_pBuffer + sizeof(int) + 13 * sizeof(char) + (25 * sizeof(char)) * i );
                }
            free(novo_pBuffer);
            }
        }
    if(!pBuffer) {
        printf("Memoria insuficiente");
        exit(1);
        }
    return pBuffer;
}



void buscar (void *pBuffer) {
    char nome[10], count = 0;

    printf("Digite o nome que voce procura: ");
    scanf("%s", nome);
    getchar();

    for(int i = 0; i < *(int *)pBuffer; i++) { 
        if(strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 25 ) * i), nome) == 0) {
            count++;
            printf("Nome: %s ", (char *)pBuffer + sizeof(int) + ((sizeof(char) * 25 ) * i));
            printf("Idade: %s ", (char *)pBuffer + sizeof(int) + 10 * sizeof(char) + ((sizeof(char) * 25 ) * i));
            printf("Telefone: %s\n", (char *)pBuffer + sizeof(int) + 13 * sizeof(char) + ((sizeof(char) * 25 ) * i));
            }  
        }
    if(count == 0) {
        printf("Nome nao encontrado\n");
    }
}


void listar (void *pBuffer) {

    if (pBuffer != NULL) {
       for(int i = 0; i < *(int*)(pBuffer); i++){
            printf("Nome: %s ", (char *)pBuffer + sizeof(int) + ((sizeof(char) * 25 ) * i));
            printf("Idade: %s ", (char *)pBuffer + sizeof(int) + 10 * sizeof(char) + ((sizeof(char) * 25 ) * i));
            printf("Telefone: %s\n", (char *)pBuffer + sizeof(int) + 13 * sizeof(char) + ((sizeof(char) * 25 ) * i));

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