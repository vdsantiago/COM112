#include <stdio.h>
#include "com112_arvoreAVL.h"

int menu()
{
    int op;

    printf("\nMenu de opções\n");
    printf("1- Criar árvore\n");
    printf("2- Liberar árvore\n");
    printf("3- Inserir elemento\n");
    printf("4- Remover elemento\n");
    printf("5- Consultar elemento\n");
    printf("6- Imprimir percurso pré-ordem\n");
    printf("7- Imprimir percurso em-ordem\n");
    printf("8- Imprimir percurso pós-ordem\n");
    printf("9- Altura da árvore\n");
    printf("10- Total de elementos\n");
    printf("11- Sair\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &op);

    return op;
}

int main() 
{
  AVL *raiz;
  int op, pos, valor, a;

    do
    {
        op = menu();
        switch(op){

        case 1: 
            raiz = cria_AVL();

            if(raiz != NULL)
            {
            printf("\n Árvore criada com sucesso");
            }
            else
            {
            printf("\n Árvore não foi criada");
            }
            break;


        case 2: 
            a = libera_AVL(raiz);

            if(a){
            printf("\n Árvore liberada");
            }else{
            printf("\n Árvore não foi liberada");
            }
            break;

        case 3:
            printf("\n Digite o valor a ser inserido: ");
            scanf("%d", &valor);      

            a = insere_AVL(raiz, valor);

            if(a == 1)
            {
            printf("\n Inserção realizada");
            }
            else
            {
            printf("\n Inserção não realizada");
            }
            break;

        case 4:
            printf("\n Digite o valor a ser removido: ");
            scanf("%d", &valor); 

            a = remove_AVL(raiz, valor);

            if(a == 1)
            {
            printf("\n Remoção realizada");
            }
            else
            {
            printf("\n Remoção não realizada");
            }
            break;

        case 5:
            printf("\n Digite o valor a ser buscado: ");
            scanf("%d", &valor); 

            a = consulta_AVL(raiz, valor);

            if(a == 1)
            {
            printf("\n Busca realizada");
            }
            else
            {
            printf("\n Valor não encontrado");
            }
            break;

        case 6:    
            preOrdem_AVL(raiz);
            break;

        case 7:
            emOrdem_AVL(raiz);
            break;

        case 8:    
            posOrdem_AVL(raiz);    
            break;

        case 9:
            printf("%d\n", altura_AVL(raiz));
            break;

        case 10:
            printf("%d\n", totalNO_AVL(raiz));
            break;
                
        case 11:
            libera_AVL(raiz);
            printf("\nFinalizando...\n");
            break;

        default: 
            printf("\nOpção inválida!\n");
            break;
        }

    }
    while(op != 11);

  return 0;
}