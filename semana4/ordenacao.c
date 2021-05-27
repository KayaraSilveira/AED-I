#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

void mergeSort (int *data, int inicio, int fim);
void merge(int *data, int inicio, int meio, int fim);
void quickSort (int *data, int left, int right);
void selectSort (int *data, int n);
void insertionSort (int *data, int size);
void printa(int *data, int size); 
void verifica (int *data, int size);
int *copia(int *pVetor, int size);
float time_diff(struct timeval *start, struct timeval *end);


int main () {

    srand(time(NULL));
    int selection, size, number, i; 
    struct timeval begin, end;

    printf("Digite o tamanho do vetor: \n");
    scanf("%d", &size);
    int *pVetor, *pVetorOrdenado;
    pVetor = malloc(size * sizeof(int));

    for(i = 0; i < size; i++) {
        number = rand()%10000;
        pVetor[i] = number;
    }

    do{
       
        printf("Escolha o algoritmo de ordenacao:\n 1)Insertion Sort\n 2)Selection Sort\n 3)Quick Sort\n 4)Merge Sort\n 5)Sair\n");
        scanf("%d", &selection);

        
        switch(selection){
            case 1: 
                pVetorOrdenado = copia(pVetor, size);
                gettimeofday(&begin, NULL);
                insertionSort(pVetorOrdenado, size);
                gettimeofday (&end, NULL);
                printa(pVetorOrdenado, size);
                verifica(pVetorOrdenado, size);
                printf("tempo de execucao:: %0.8f sec\n", time_diff(&begin, &end));
                free(pVetorOrdenado);
                break;

           case 2:
                pVetorOrdenado = copia(pVetor, size);
                gettimeofday(&begin, NULL);
                selectSort(pVetorOrdenado, size);
                gettimeofday (&end, NULL);
                printa(pVetorOrdenado, size);
                verifica(pVetorOrdenado, size);
                printf("tempo de execucao:: %0.8f sec\n", time_diff(&begin, &end));
                free(pVetorOrdenado);
                break;

            case 3:
                pVetorOrdenado = copia(pVetor, size);
                gettimeofday(&begin, NULL);
                quickSort(pVetorOrdenado, 0, size - 1);
                gettimeofday (&end, NULL);
                printa(pVetorOrdenado, size);
                verifica(pVetorOrdenado, size);
                printf("tempo de execucao:: %0.8f sec\n", time_diff(&begin, &end));
                free(pVetorOrdenado);
                break;

            case 4:
                pVetorOrdenado = copia(pVetor, size);
                gettimeofday(&begin, NULL);
                mergeSort(pVetorOrdenado, 0, size - 1);
                gettimeofday (&end, NULL);
                printa(pVetorOrdenado, size);
                verifica(pVetorOrdenado, size);
                printf("tempo de execucao:: %0.8f sec\n", time_diff(&begin, &end));
                free(pVetorOrdenado);
                break;

            case 5:
                free(pVetor);
                break;
        }
    }  while(selection != 5); 

    return 0;
}
void insertionSort (int *data, int size) {

    for(int i = 0; i < size; i++) {
        int j = i;
        int x = data[i];
        while ((j > 0) && (data[j-1] > x)) {
            data[j] = data[j-1];
            j--;
        }
    data[j] = x;
    }   
}

void selectSort (int *data, int n) {

    int min, tmp, i, j, min_id;

    for( i = 0; i < (n - 1); i++) {
        min = data[i];
        for( j = (i + 1); j < n; j++) {
            if(data[j] < min) {
                min = data[j];
                min_id = j;
            }
        }
        tmp = data[i];
        data[i] = data[min_id];
        data[min_id] = tmp;
        min_id = i + 1;
        
    }
}

void quickSort (int *data, int left, int right) {

    int mid, tmp, i, j;
    i = left;
    j = right;
    mid = data[(left + right)/2];

    do {

        while(data[i] < mid) {
            i++;
        }
        while(mid < data[j]) {
            j--;
        }

        if( i <= j) {
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);

    if(left < j) 
        quickSort(data, left, j);
    
    if(i < right) 
        quickSort(data, i, right);
    
}  

void mergeSort (int *data, int inicio, int fim) {

    int meio;
    if(inicio < fim) {
        meio = floor((inicio+fim)/2);
        mergeSort(data, inicio, meio);
        mergeSort(data, meio + 1, fim);
        merge(data, inicio, meio, fim);
    }
}

void merge(int *data, int inicio, int meio, int fim) {

    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;

    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = malloc(tamanho * sizeof(int));

    if(temp != NULL) {
        for(i = 0; i < tamanho; i++) {
            if(!fim1 && !fim2) {

                if(data[p1] < data[p2])                     
                    temp[i] = data[p1++];
                else 
                    temp[i] = data[p2++];
                
                if(p1 > meio)
                    fim1 = 1;
                if(p2 > fim)
                    fim2 = 1;
            }
            else {
                if(!fim1)
                    temp[i] = data[p1++];
                else 
                    temp[i] = data[p2++];
            }
        }
        for(j = 0, k = inicio; j < tamanho; j++, k++) {
            data[k] = temp[j];
        }
    }
    free(temp);
}

void printa(int *data, int size) {

    int i;

    for(i = 0; i < size; i++)
        printf("Vetor[%d] = %d\n", i, data[i]);

}

void verifica (int *data, int size) {

    int count = 0;
    for(int i = 0; i < (size - 1); i++) {
        if(data[i] > data[i + 1])
            count++;
    }
    if(count == 0) 
        printf("O resultado esta correto\n");
    else 
        printf("O resultado esta incorreto\n");

}

int *copia(int *pVetor, int size) {

    int i, *pVetorOrdenado;
    pVetorOrdenado = malloc(size * sizeof(int));

    for(i = 0; i < size; i++) {
        pVetorOrdenado[i] = pVetor[i];
    }

    return pVetorOrdenado;
}

float time_diff(struct timeval *start, struct timeval *end) {

    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

