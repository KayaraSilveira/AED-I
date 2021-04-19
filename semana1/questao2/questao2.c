#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


char *adicionar (char *lista);
char *remover (char *lista);
void listar (char *lista);
void sair (char *lista);


int main () {

    char *ListaNomes = NULL;
    int escolha;

        do{
       
        printf("O que voce deseja fazer?\n 1)Adicionar\n 2)Remover\n 3)Listar\n 4)Sair\n");
        scanf("%d",&escolha);
        getchar();
        
        switch(escolha){
            case 1: 
                ListaNomes = adicionar(ListaNomes);
                break;
           case 2:
                ListaNomes = remover(ListaNomes);
                break;
            case 3:
                listar(ListaNomes);
                break;
            case 4:
                sair(ListaNomes);
                break;
        }
    }  while(escolha != 4); 
    return 0;
}


char *adicionar (char *lista)  {

    int tam_lista = 0, tam_nome = 0, tam;
    char *nome = NULL; 
    nome = (char*)malloc(sizeof(char)*50);

    
    if (!nome) {
        printf("Memoria insuficiente");
        exit(1);
    }

    printf("Digite o nome a ser adicionado: "); 
    scanf("%[^\n]s", nome);
    strcat(nome, ";");
    tam_nome = strlen(nome);

    if(!lista) { //se a lista ainda nao existe
        tam = tam_nome + 1;
        lista = (char*)malloc(tam * sizeof(char)); //aloca um espaço pra lista
        strcpy(lista, nome); //copia o nome a ser adicionado a lista
    }
     else { //se ela ja existe
        tam_lista = strlen(lista); 
        tam = tam_lista + tam_nome + 1;
        lista = (char*)realloc(lista, tam * sizeof(char)); //realoca a string original 
        strcat(lista, nome); //concatena com os nomes que foram adicionados anteriormente
    }
    if(!lista) {
        printf("Memoria insuficiente");
        exit(1);
        }
    
    free(nome);
    
    return lista;
}


char *remover (char *lista) {

    if(!lista){
        printf("Primeiro adicione um nome a lista\n");
        return lista;
    }
    int tam_nome, tam_lista = 0, tam_lista_aux, i, j, count = 0;
    char *nome = NULL, *aux_nome = NULL, *lista_aux = NULL;

    aux_nome = (char *)malloc(sizeof(char) * 50); //aloca espaço pro auxiliar que vai guardar o nome
    nome = (char *)malloc(sizeof(char) * 50); //aloca o nome a ser removido

    printf("Digite o nome a ser removido: "); 
    scanf ( "%s", nome); 
    getchar(); 

    tam_lista = strlen(lista);

    for(i = 0; i < tam_lista; i++) { //percorre a lista
        j = 0;
        
        while(lista[i] != ';') { //copia nome por nome pro nome auxiliar
            aux_nome[j] = lista[i];
            j++;
            i++;
        }

        aux_nome[j] = '\0';
        tam_nome = strlen(aux_nome) + 2;
       
        if(strcmp(aux_nome, nome) != 0) {  //se o nome copiado é diferente do nome a ser removido
            if (lista_aux == NULL) {  //se a lista auxiliar ainda nao existe
                lista_aux = (char*)malloc(tam_nome * sizeof(char)); //aloca a lista auxiliar
                strcpy(lista_aux, aux_nome); //copia o nome que nao vai ser removido pra essa lista
                strcat (lista_aux, ";");
                strcat (lista_aux, "\0");
            }
            else { //se a lista auxiliar ja existe
                lista_aux = (char*)realloc(lista_aux, (tam_lista_aux + tam_nome) * sizeof(char)); //realoca a lista auxiliar pro novo tamanho
                strcat (lista_aux, aux_nome); //concatena outro nome que nao vai ser removido a lista
                strcat (lista_aux, ";");
                strcat (lista_aux, "\0");
            }
            
            if(lista_aux == NULL) { 
                printf("Memoria insuficiente");
                exit(1);
             }
            tam_lista_aux = strlen(lista_aux);
        }
        else {
            count++; //conta se algum nome foi removido
        }
    }

        if(count == 0) { //se nenhum nome foi removido o programa avisa que nao foi encontrado
            printf("O nome nao foi encontrado\n");
            free(lista_aux);
            free(nome);
            free(aux_nome);
        }
        else { //se removeu algum nome
            lista = (char*)realloc(lista, (tam_lista) * sizeof(char)); //realoca a lista original pro novo tamanho
            if(!lista_aux) { //se a lista auxliar ficou vazia significa que todos nomes foram retirados portanto retorna nulo
                free(lista_aux);
                free(nome);
                free(aux_nome);
                free(lista);
                return NULL;

            }
            else { //se ainda ha nomes na lista
                strcpy(lista, lista_aux); //copia a lista nova gerada pela função pra lista original
                free(lista_aux); 
                free(nome);
                free(aux_nome);
            }
        }

    return lista;
}


void listar (char *lista) {
    if (lista) {
        while (*lista) {
            if (*lista != ';') {
                printf("%c", *lista++);
            } else {
                lista++;
                printf("\n");
            }
        }
    } else {
        printf("A lista esta vazia\n");
    }
        
}

void sair (char *lista) {
    free(lista);
    exit(1);
}