typedef struct NO* AVL;

AVL* cria_AVL();
int libera_AVL(AVL *raiz);
int insere_AVL(AVL *raiz, int data);
int remove_AVL(AVL *raiz, int valor);
int estaVazia_AVL(AVL *raiz);
int altura_AVL(AVL *raiz);
int totalNO_AVL(AVL *raiz);
int consulta_AVL(AVL *raiz, int valor);
void preOrdem_AVL(AVL *raiz);
void emOrdem_AVL(AVL *raiz);
void posOrdem_AVL(AVL *raiz);