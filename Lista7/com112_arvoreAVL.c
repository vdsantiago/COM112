#include <stdio.h>
#include <stdlib.h>
#include "com112_arvoreAVL.h"

struct NO
{
    int info;
    int altura;
    struct NO *dir;
    struct NO *esq;
};

AVL* cria_AVL()
{
    AVL* raiz = (AVL*) malloc(sizeof(AVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no)
{
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

int libera_AVL(AVL* raiz)
{
    if(raiz == NULL)
        return 1;
    libera_NO(*raiz);
    free(raiz);

    return 1;
}

int altura_NO(struct NO* no)
{
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no)
{
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_AVL(AVL *raiz)
{
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_AVL(AVL *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_AVL(&((*raiz)->esq));
    int alt_dir = totalNO_AVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_AVL(AVL *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_AVL(&((*raiz)->esq));
    int alt_dir = altura_AVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
    {
        return (alt_esq + 1);
    }
    else
    {
        return(alt_dir + 1);
    }
}

void preOrdem_AVL(AVL *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        printf("No %d: %d\n",(*raiz)->info,altura_NO(*raiz));
        preOrdem_AVL(&((*raiz)->esq));
        preOrdem_AVL(&((*raiz)->dir));
    }
}

void emOrdem_AVL(AVL *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        emOrdem_AVL(&((*raiz)->esq));
        printf("No %d: Altura(%d) FatorBalanceamento(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_AVL(&((*raiz)->dir));
    }
}

void posOrdem_AVL(AVL *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        posOrdem_AVL(&((*raiz)->esq));
        posOrdem_AVL(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

int consulta_AVL(AVL *raiz, int valor)
{
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info)
        {
            return 1;
        }
        if(valor > atual->info)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->esq;
        }
    }
    return 0;
}

void RotacaoLL(AVL *A)
{
    printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(AVL *A)
{
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(AVL *A)
{
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(AVL *A)
{
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_AVL(AVL *raiz, int valor)
{
    int r;
    if(*raiz == NULL)
    {
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
        {
            return 0;
        }
        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info)
    {
        if((r = insere_AVL(&(atual->esq), valor)) == 1)
        {
            if(fatorBalanceamento_NO(atual) >= 2)
            {
                if(valor < (*raiz)->esq->info )
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }
    else
    {
        if(valor > atual->info)
        {
            if((r = insere_AVL(&(atual->dir), valor)) == 1)
            {
                if(fatorBalanceamento_NO(atual) >= 2)
                {
                    if((*raiz)->dir->info < valor)
                    {
                        RotacaoRR(raiz);
                    }
                    else
                    {
                        RotacaoRL(raiz);
                    }
                }
            }
        }

        else
        {
            printf("Valor duplicado\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return r;
}

struct NO* procuraMenor(struct NO* atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_AVL(AVL *raiz, int valor)
{
	if(*raiz == NULL)
    {
	    printf("Valor inexistente\n");
	    return 0;
	}

    int r;
	if(valor < (*raiz)->info)
    {
	    if((r = remove_AVL(&(*raiz)->esq,valor)) == 1)
        {
            if(fatorBalanceamento_NO(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                {
                    RotacaoRR(raiz);
                }
                else
                {
                    RotacaoRL(raiz);
                }
            }
	    }
	}

	if((*raiz)->info < valor)
    {
	    if((r = remove_AVL(&(*raiz)->dir, valor)) == 1)
        {
            if(fatorBalanceamento_NO(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoLR(raiz);
                }
            }
	    }
	}

	if((*raiz)->info == valor)
    {
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL))
        {
			struct NO *vNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(vNode);
		}

        else 
        {
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_AVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2)
            {
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                {
					RotacaoLL(raiz);
                }
				else
                {
					RotacaoLR(raiz);
                }
			}
		}

		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return r;
}