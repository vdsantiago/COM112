#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "com112_sort.h"
#include "com112_file.h"

void relatorio(double time, int comparison, int movement, int flag)
{
    if (flag == 0)
    {
        printf("Método Bubble Sort:\n");
    }
    else if(flag == 1){
        printf("Método Selection Sort:\n");
    }
    else if(flag == 2){
        printf("Método Insertion Sort:\n");
    }
    else{
        printf("Método Merge Sort:\n");
    }
    
    printf("    Tempo de execução: %fs\n", time);
    printf("    Número de comparações: %d\n",comparison);
    printf("    Número de movimentações: %d\n", movement);
    printf("\n");
}

void copyArray(int *Array, int *copiedArray, int length)
{
    int i;

    for(i = 0; i < length; i++)
    {
        copiedArray[i] = Array[i];
    }
}

void report(int length, int* dataArray, clock_t t)
{
        int Array[length], copiedArray[length], i, secondFlag = 0;

        readFile(Array, length);

        for(i = 0; i < 4; i++)
        {
            if(i == 0)
            {
                copyArray(Array, copiedArray, length);
                t = clock();
                bubble_sort(copiedArray, length, dataArray);
                t = clock() - t;
            }
            else if(i == 1)
            {
                copyArray(Array, copiedArray, length);
                t = clock();
                selection_sort(copiedArray, length, dataArray);
                t = clock() - t;
            }
            else if(i == 2)
            {
                copyArray(Array, copiedArray, length);
                t = clock();
                insertion_sort(copiedArray, length, dataArray);
                t = clock() - t;
            }
            else
            {
                copyArray(Array, copiedArray, length);
                t = clock();
                merge_sort(copiedArray, 0, length - 1, dataArray);
                t = clock() - t;
                secondFlag = 1;
            }
            double time = ((double)t)/CLOCKS_PER_SEC;
            relatorio(time, dataArray[0], dataArray[1], i); // i aqui está se comportando como flag
            writeReport(length, dataArray[0], dataArray[1], i, secondFlag, time); // i aqui está se comportando como flag
        }
        writeFile(length, copiedArray, 1);
}

int menu()
{
    int opc;

    printf("Selecione o método de ordenação que deseja utilizar:\n");
    printf("Digite (1) para Bubble Sort\n");
    printf("Digite (2) para Selection Sort\n");
    printf("Digite (3) para Insertion Sort\n");
    printf("Digite (4) para Merge Sort\n");
    printf("Digite (5) para gerar relatório\n");
    printf("Digite (6) para sair\n");

    scanf("%d", &opc);

    return opc;
}

void generateArray(int *array, int n)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        array[i] = rand() % 50;
    }
}


int main()
{
    int n, opc, flag;
    double* time;

    printf("Entre com o tamanho do vetor que você deseja criar\n");
    scanf("%d", &n);

    int vet[n], aux[n];
    int dataArray[2];

    dataArray[0] = 0;
    dataArray[1] = 0;

    generateArray(aux, n);

    writeFile(n, vet, 0);
    opc = menu(n, vet);

    clock_t t;

    volta:
    copyArray(aux, vet, n);

    switch (opc)
    {
        case 1:
            flag = 0;
            t = clock();
            bubble_sort(vet, n, dataArray);
            t = clock() - t;
            break;
                
        case 2:
            flag = 1;
            t = clock();
            selection_sort(vet, n, dataArray);
            t = clock() - t;
            break;
                
        case 3:
            flag = 2;
            t = clock();
            insertion_sort(vet, n, dataArray);
            t = clock() - t;
            break;

        case 4:
            flag = 3;
            t = clock();
            merge_sort(vet, 0, n - 1, dataArray);
            t = clock() - t;
            break;

        case 5:
            report(n, dataArray, t);   
    }

    if(opc <= 4){
        double time = ((double)t)/CLOCKS_PER_SEC;
        writeFile(n, vet, 1);
        writeReport(n, dataArray[0], dataArray[1], flag, 2, time);
        relatorio(time, dataArray[0], dataArray[1], flag);

        opc = menu(n, vet);
        goto volta;
    }
    else if(opc == 5){
        printf("\n");
        printf("Ordenação realizada com SUCESSO!\n\n");
        opc = menu(n, vet);
        goto volta;
    }
    else{
        return 0;
    }
    return 0;
}