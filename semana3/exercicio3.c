#include <stdio.h> 
#include <stdlib.h>

typedef struct {

    int numero;

} Registro;

typedef struct {

    Registro reg;
    struct Nodo *pEsq, *pDir;

} Nodo;

int FB(Nodo* pRaiz);
int Altura(Nodo* pRaiz);
void RSE (Nodo** ppRaiz);
void RSD (Nodo** ppRaiz);
int BalancaEsquerda (Nodo** ppRaiz);
int BalancaDireita (Nodo** ppRaiz);
int Balanceamento (Nodo** ppRaiz);
int Insere (Nodo** ppRaiz, int x);
int EhArvoreAvl (Nodo* pRaiz);
int Imprime (Nodo *pRaiz);
int FreeArvore (Nodo *pRaiz);
int Remove (Nodo** ppRaiz, int x);
Nodo* procuraMenor (Nodo* pAtual);
void SegundoCenario ();


int main () {

    int quantidade, i, x, escolha, escolha2;
    Nodo *pRaiz = NULL;
    
    srand(time(0));

    do {

        printf("Qual cenario voce deseja? \n1)Primeiro cenario \n2)Segundo cenario \n3)Nenhum(sair)\n");
        scanf("%d", &escolha);

        if(escolha == 1) {

            printf("------------Primeiro cenario------------\n");
            printf("Quantos nodos voce quer na arvore?\n");
            scanf("%d", &quantidade);

            for(i = 0; i < quantidade; i++) {
            x = rand()%1000;
            printf("numero inserido: %d\n", x);
            Insere (&pRaiz, x);
            }

            printf("Esta foi a arvore formada:\n");
            Imprime(pRaiz);

            if(EhArvoreAvl(pRaiz))
                printf("Gerou uma arvore AVL\n");
            else
                printf("A arvore gerada nao eh AVL\n");

            do {
                printf("Deseja apagar algum nodo? \n1)sim \n2)nao \n");
                scanf("%d", &escolha2);

                if(escolha2 == 1) {
                    printf("Digite o valor do nodo a ser apagado:\n");
                    scanf("%d", &x);
                    if(Remove(&pRaiz, x)) {
                        printf("Nodo apagado\n");
                        Imprime(pRaiz);
                        if(EhArvoreAvl(pRaiz))
                            printf("A arvore continua AVL\n");
                        else 
                            printf("A arvore nao eh mais AVL\n");
                    }
                    else {
                        printf("O nodo nao foi apagado\n");
                        Imprime(pRaiz);
                    }
                }

            }while(escolha2 == 1);
          
            FreeArvore(pRaiz);
        }

        if(escolha == 2) {
            printf("------------Segundo cenario------------\n");
            SegundoCenario();
        }
    
    }while (escolha != 3);
    return 0;
}

int FB(Nodo* pRaiz) {


    if (pRaiz == NULL) 
        return 0;
    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);

}

int Altura (Nodo* pRaiz) {


    int iEsq, iDir;

    if(pRaiz == NULL)
        return 0;

    iEsq = Altura (pRaiz->pEsq);
    iDir = Altura (pRaiz->pDir);

    if (iEsq > iDir)
        return iEsq + 1;
    else 
        return iDir + 1;

}

void RSE (Nodo** ppRaiz) {

    Nodo *pAux;

    pAux = (*ppRaiz) ->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;

}

void RSD (Nodo** ppRaiz) {

    Nodo *pAux;

    pAux = (*ppRaiz) ->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;

}

int BalancaEsquerda (Nodo** ppRaiz) {

    int fbe = FB ((*ppRaiz)->pEsq);
    if (fbe >= 0) {
        RSD(ppRaiz);
        return 1;
    }
    else if (fbe < 0) {
        RSE(&((*ppRaiz)->pEsq));
        RSD((ppRaiz));
        return 1;
    }
    return 0;
}

int BalancaDireita (Nodo** ppRaiz) {

    int fbd = FB ((*ppRaiz)->pDir);
    if (fbd <= 0) {
        RSE(ppRaiz);
        return 1;
    }
    else if (fbd > 0) {
        RSD(&((*ppRaiz)->pDir));
        RSE((ppRaiz));
        return 1;
    }
    return 0;
}

int Balanceamento (Nodo** ppRaiz) {

    int fb = FB(*ppRaiz);
    if(fb > 1) 
        return BalancaEsquerda(ppRaiz);
    
    else if (fb < -1) 
        return BalancaDireita(ppRaiz);
    
    else 
        return 0;

}

int Insere (Nodo** ppRaiz, int x) {

    if (*ppRaiz == NULL) {
        *ppRaiz = (Nodo *)malloc(sizeof(Nodo));
        (*ppRaiz)->reg.numero = x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;
    }
    else if ((*ppRaiz)->reg.numero > x){
        if (Insere(&(*ppRaiz)->pEsq, x)) {
            if (Balanceamento (ppRaiz))
                return 0;
            else 
                return 1;
        }
    }
    else if ((*ppRaiz)->reg.numero < x) {
        if (Insere(&(*ppRaiz)->pDir, x)) {
            if (Balanceamento(ppRaiz))
                return 0;
            else 
                return 1;
        }
        else 
            return 0;
    }
    else 
        return 0;
}
int Remove (Nodo** ppRaiz, int x) {


    if(*ppRaiz == NULL) {
        printf("Numero nao econtrado\n");
        return 0;
    }

    int retorno; 

    if ((*ppRaiz)->reg.numero > x) {
        if ((retorno = Remove(&(*ppRaiz)->pEsq, x)) == 1 ) {
            Balanceamento(ppRaiz);
        }
    }

    if((*ppRaiz)->reg.numero < x) {
        if((retorno = Remove(&(*ppRaiz)->pDir, x)) == 1 ) {
            Balanceamento(ppRaiz);
        }
    }
    
    if ((*ppRaiz)->reg.numero == x) {
        if(((*ppRaiz)->pEsq == NULL ) || ((*ppRaiz)->pDir == NULL)) {
            Nodo *removido = (*ppRaiz);

            if((*ppRaiz)->pEsq != NULL)
                *ppRaiz = (*ppRaiz)->pEsq;
            else 
                *ppRaiz = (*ppRaiz)->pDir;

            free(removido);
        }

        else {
            Nodo *temp = procuraMenor ((*ppRaiz)->pEsq);
            (*ppRaiz)->reg.numero = temp->reg.numero;
            Remove(&(*ppRaiz)->pDir, (*ppRaiz)->reg.numero);
            Balanceamento(ppRaiz);
        }
        return 1;
    }
    return retorno;
   
}

Nodo* procuraMenor (Nodo* pAtual) {
    Nodo *nodo1 = pAtual;
    Nodo *nodo2 = pAtual->pEsq;
    while (nodo2 != NULL) {
        nodo1 = nodo2;
        nodo2 = nodo2->pEsq;
    }
    return nodo1;
}

int EhArvoreAvl (Nodo* pRaiz) {
    int fb;

    if (pRaiz == NULL)
        return 1;
    
    if(!EhArvoreAvl(pRaiz->pEsq))
        return 0;
    if (!EhArvoreAvl(pRaiz->pDir))
        return 0;

    fb = FB (pRaiz);
    if ((fb > 1)  || (fb < -1))
        return 0;
    else 
        return 1;
}

int Imprime (Nodo *pRaiz) {

    if(pRaiz != NULL) {

        printf("%d(", pRaiz->reg.numero);
        Imprime(pRaiz->pEsq);
        Imprime(pRaiz->pDir);
        printf(")");
    }
}

int FreeArvore (Nodo *pRaiz) {

    if(pRaiz != NULL) {
        
        FreeArvore(pRaiz->pEsq);
        FreeArvore(pRaiz->pDir);
        free(pRaiz);
      
    }
}

void SegundoCenario () {

    Nodo *pRaiz = NULL;

    printf("\n.....Testes de insercao.....\n");

    printf("\ncaso 1a: inserindo 15 na primeira arvore\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    printf("primeira arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Insere(&pRaiz, 15);
    printf("arvore apos a insercao do 15: "); 
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("caso 2a: inserindo 15 na segunda arvore\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 9);
    printf("segunda arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Insere(&pRaiz, 15);
    printf("arvore apos a insercao do 15: ");
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("caso 3a: inserindo 15 na terceira arvore\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 21);
    Insere(&pRaiz, 30);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 11);
    printf("terceira arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Insere(&pRaiz, 15);
    printf("arvore apos a insercao do 15: ");
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("caso 1b: inserindo 8 na primeira arvore\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    printf("primeira arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Insere(&pRaiz, 8);
    printf("arvore apos a insercao do 8: "); 
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("caso 2b: inserindo 8 na segunda arvore\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 9);
    printf("segunda arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Insere(&pRaiz, 8);
    printf("arvore apos a insercao do 8: ");
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("caso 3b: inserindo 8 na terceira arvore\n");
    Insere(&pRaiz, 20);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 26);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 21);
    Insere(&pRaiz, 30);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 11);
    printf("terceira arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Insere(&pRaiz, 8);
    printf("arvore apos a insercao do 8: ");
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("\n.....Testes de exclusao.....\n");

    printf("\ncaso 1: exluindo o 1 na primeira arvore\n");
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 1);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 5);
    printf("primeira arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Remove(&pRaiz, 1);
    printf("arvore apos a exclusao do 1: "); 
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("caso 2: exlcuindo o 1 na segunda arvore\n");
    Insere(&pRaiz, 6);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 1);
    Insere(&pRaiz, 8);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 11);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 5);
    Insere(&pRaiz, 12);
    Insere(&pRaiz, 10);
    Insere(&pRaiz, 13);
    printf("segunda arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Remove(&pRaiz, 1);
    printf("arvore apos a exclusao do 1: ");
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);
    pRaiz = NULL;
    printf("\n");

    printf("caso 3: exlcuindo o 1 na terceira arvore\n");
    Insere(&pRaiz, 5);
    Insere(&pRaiz, 2);
    Insere(&pRaiz, 8);
    Insere(&pRaiz, 1);
    Insere(&pRaiz, 3);
    Insere(&pRaiz, 7);
    Insere(&pRaiz, 10);
    Insere(&pRaiz, 4);
    Insere(&pRaiz, 6);
    Insere(&pRaiz, 11);
    Insere(&pRaiz, 9);
    Insere(&pRaiz, 12);
    printf("terceira arvore: ");
    Imprime(pRaiz);
    printf("\n");
    Remove(&pRaiz, 1);
    printf("arvore apos a exclusao do 1: ");
    Imprime(pRaiz);
    printf("\n");
    FreeArvore(pRaiz);

}