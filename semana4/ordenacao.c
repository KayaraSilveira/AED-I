#include <stdio.h> 

int *Merge_sort (int *data);
int *Merge(int *left, int *right);
void Quicksort (int data[], int left, int right);
void Selectsort (int data[], int n);
void Insertionsort (int data[], int size);
void Printa(int data[], int size); 
void verifica (int data[], int size);

int main () {

    srand(time(NULL));
    int size, number, i, selection; 

    printf("Digite o tamanho do vetor: \n");
    scanf("%d", &size);
    int vet[size];

    for(i = 0; i < size; i++) {
        number = rand()%10000;
        vet[i] = number;
    }

    do{
       
        printf("Escolha o algoritmo de ordenacao:\n 1)Insertion Sort\n 2)Selection Sort\n 3)Quick Sort\n 4)Merge Sort\n 5)Sair\n");
        scanf("%d", &selection);

        
        switch(selection){
            case 1: 
                Insertionsort(vet, size);
                Printa(vet, size);
                verifica(vet, size);
                break;
           case 2:
                Selectsort(vet, size);
                Printa(vet, size);
                verifica(vet, size);
                break;
            case 3:
                Quicksort(vet, 0, size);
                Printa(vet, size);
                verifica(vet, size);
                break;
            case 4:
                
                break;
            case 5:
                
                break;
        }
    }  while(selection != 5); 

    return 0;
}
void Insertionsort (int data[], int size) {

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

void Selectsort (int data[], int n) {

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

void Quicksort (int data[], int left, int right) {

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
        Quicksort(data, left, j);
    
    if(i < right) 
        Quicksort(data, i, right);
    

}  

void Printa(int data[], int size) {

    int i;

    for(i = 0; i < size; i++)
        printf("Vetor[%d] = %d\n", i, data[i]);

}

void verifica (int data[], int size) {

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