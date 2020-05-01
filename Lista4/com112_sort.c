#include <stdio.h>
#include <stdlib.h>
#include "com112_sort.h"

void bubble_sort (int *v, int *r, int n) 
{
    int i, k, j, aux, c, t;

    for (k = 1; k < n; k++) 
    {
        for (j = 0; j < n - 1; j++) 
        {
            if (v[j] > v[j + 1]) 
            {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
                t++;
            }
            c++;
        }
    }

    printf("Vetor ordenado:\n");
    printf("[");
    for (i = 0; i < n; i++)
    {
        printf(" %d", v[i]);
    }
    printf(" ]\n\n");
    r[0] = c;
    r[1] = t;
}

void selection_sort(int *v, int *r, int n) 
{ 
    int i, j, menor, aux, c, t; 
    for (i = 0; i < n - 1; i++)
    {
        menor = i;
        for(j = i + 1; j < n; j++)
        {
            if(v[j] < v[menor])
            {
                menor = j;
            }
            c++;
        }

        if(i != menor)
        {
            aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
            t++;
        }
        
    }

    r[0] = c;
    r[1] = t;
}

void insertion_sort(int *v, int *r, int n) 
{ 
    int i, k, j, aux, c, t; 

    for (k = 1; k < n; k++)
    { 
        aux = v[k];
        c++;

        for (j = k; (j > 0) && (aux < v[j - 1]); j--)
        {
            v[j] = v[j - 1];
            v[j] = aux;
            t++;
        }
    } 

    printf("Vetor ordenado:\n");
    printf("[");
    for (i = 0; i < n; i++)
    {
        printf(" %d", v[i]);
    }

    printf(" ]\n\n");

    r[0] = c;
    r[1] = t;
}
