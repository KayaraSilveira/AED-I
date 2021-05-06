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

int main () {

    int quantidade, i, random;
    Nodo *pRaiz = NULL;

    printf("Quantos nos voce quer na arvore?\n");
    scanf("%d", &quantidade);
    
    srand(time(0));

    for(i = 0; i < quantidade; i++) {
        random = rand()%1000;
        printf("numero inserido: %d\n", random);
        Insere (&pRaiz, random);
    }

    if(EhArvoreAvl(pRaiz))
        printf("Gerou uma arvore AVL\n");
    else
        printf("A arvore gerada nao eh AVL\n");
    
    Imprime(pRaiz);
    FreeArvore(pRaiz);

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
    if (fbe > 0) {
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
    if (fbd < 0) {
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