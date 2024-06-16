//
// Created by davi on 10/06/2024.
//

#include "rubronegra.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar uma árvore rubro-negra
rubronegra *criaArvoreRB() {
    rubronegra *arv = (rubronegra *)malloc(sizeof(rubronegra));
    arv->sentinela = (noRB *)malloc(sizeof(noRB));
    arv->sentinela->cor = P;
    arv->sentinela->chave = -1000;
    arv->sentinela->esq = arv->sentinela->dir = arv->sentinela->pai = arv->sentinela;
    arv->raiz = arv->sentinela;
    arv->numElementos = 0;
    arv->rotacoesInsercaoRB = 0;
    arv->rotacoesRemocaoRB = 0;
    return arv;
}

// Função para criar um nó rubro-negra
noRB *criaNoRB(int chave) {
    noRB *novoNo = (noRB *)malloc(sizeof(noRB));
    novoNo->chave = chave;
    novoNo->esq = novoNo->dir = novoNo->pai = NULL;
    novoNo->cor = V; // Novo nó sempre é inserido como vermelho
    return novoNo;
}

// Função para inserir um nó na árvore rubro-negra
int insereNoRB(rubronegra *arv, int valor) {
    noRB *z = criaNoRB(valor);
    noRB *y = arv->sentinela;
    noRB *x = arv->raiz;

    while (x != arv->sentinela) {
        y = x;
        if (z->chave < x->chave) {
            x = x->esq;
        } else {
            x = x->dir;
        }
    }

    z->pai = y;
    if (y == arv->sentinela) {
        arv->raiz = z;
    } else if (z->chave < y->chave) {
        y->esq = z;
    } else {
        y->dir = z;
    }

    z->esq = z->dir = arv->sentinela;
    z->cor = V;
    corrigeInsercao(arv, z);
    arv->numElementos++;
    return 1;
}

// Função para corrigir a inserção na árvore rubro-negra
void corrigeInsercao(rubronegra *arv, noRB *z) {
    while (z->pai->cor == V) {
        if (z->pai == z->pai->pai->esq) {
            noRB *tio = z->pai->pai->dir;
            if (tio->cor == V) {
                z->pai->cor = P;
                tio->cor = P;
                z->pai->pai->cor = V;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoEsqRB(arv, z, 0);
                }
                z->pai->cor = P;
                z->pai->pai->cor = V;
                rotacaoDirRB(arv, z->pai->pai, 0);
            }
        } else {
            noRB *tio = z->pai->pai->esq;
            if (tio->cor == V) {
                z->pai->cor = P;
                tio->cor = P;
                z->pai->pai->cor = V;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaoDirRB(arv, z, 0);
                }
                z->pai->cor = P;
                z->pai->pai->cor = V;
                rotacaoEsqRB(arv, z->pai->pai, 0);
            }
        }
    }
    arv->raiz->cor = P;
}


noRB *predecessor(noRB *x, noRB *sentinela) {
    x = x->esq;
    while (x->dir != sentinela) {
        x = x->dir;
    }
    return x;
}


int removeNoRB(rubronegra *arv, int valor) {
    noRB *z = arv->raiz;
    while (z != arv->sentinela && z->chave != valor) {
        if (valor < z->chave) {
            z = z->esq;
        } else {
            z = z->dir;
        }
    }
    if (z == arv->sentinela) {
        return 0; // Elemento não encontrado
    }

    noRB *y = z;
    noRB *x;
    char y_original_cor = y->cor;
    if (z->esq == arv->sentinela) {
        x = z->dir;
        if (z->pai == arv->sentinela) {
            arv->raiz = x;
        } else if (z == z->pai->esq) {
            z->pai->esq = x;
        } else {
            z->pai->dir = x;
        }
        x->pai = z->pai;

    } else if (z->dir == arv->sentinela) {
        x = z->esq;
        if (z->pai == arv->sentinela) {
            arv->raiz = x;
        } else if (z == z->pai->esq) {
            z->pai->esq = x;
        } else {
            z->pai->dir = x;
        }
        x->pai = z->pai;

    } else {
        y = predecessor(z, arv->sentinela);
        y_original_cor = y->cor;
        x = y->esq;
        if (y->pai == z) {
            if (x != arv->sentinela) {
                x->pai = y;
            }
        } else {
            if (y->pai != arv->sentinela) {
                if (y == y->pai->esq) {
                    y->pai->esq = x;
                } else {
                    y->pai->dir = x;
                }
            }
            if (x != arv->sentinela) {
                x->pai = y->pai;
            }
            y->esq = z->esq;
            if (y->esq != arv->sentinela) {
                y->esq->pai = y;
            }
        }
        if (z->pai == arv->sentinela) {
            arv->raiz = y;
        } else if (z == z->pai->esq) {
            z->pai->esq = y;
        } else {
            z->pai->dir = y;
        }
        y->pai = z->pai;
        y->dir = z->dir;
        if (y->dir != arv->sentinela) {
            y->dir->pai = y;
        }
        y->cor = z->cor;
    }
    if (y_original_cor == P) {
        corrigeRemocao(arv, x);
    }
    free(z);
    arv->numElementos--;
    return 1;
}


void corrigeRemocao(rubronegra *arv, noRB *x) {
    while (x != arv->raiz && x->cor == P) {
        if (x == x->pai->esq) {
            noRB *w = x->pai->dir;
            if (w->cor == V) {
                w->cor = P;
                x->pai->cor = V;
                rotacaoEsqRB(arv, x->pai, 1);
                w = x->pai->dir;
            }
            if (w->esq->cor == P && w->dir->cor == P) {
                w->cor = V;
                x = x->pai;
            } else {
                if (w->dir->cor == P) {
                    w->esq->cor = P;
                    w->cor = V;
                    rotacaoDirRB(arv, w, 1);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = P;
                w->dir->cor = P;
                rotacaoEsqRB(arv, x->pai, 1);
                x = arv->raiz;
            }
        } else {
            noRB *w = x->pai->esq;
            if (w->cor == V) {
                w->cor = P;
                x->pai->cor = V;
                rotacaoDirRB(arv, x->pai, 1);
                w = x->pai->esq;
            }
            if (w->dir->cor == P && w->esq->cor == P) {
                w->cor = V;
                x = x->pai;
            } else {
                if (w->esq->cor == P) {
                    w->dir->cor = P;
                    w->cor = V;
                    rotacaoEsqRB(arv, w, 1);
                    w = x->pai->esq;
                }
                w->cor = x->pai->cor;
                x->pai->cor = P;
                w->esq->cor = P;
                rotacaoDirRB(arv, x->pai, 1);
                x = arv->raiz;
            }
        }
    }
    x->cor = P;
}


void rotacaoEsqRB(rubronegra *arv, noRB *x, int tipo) {
    noRB *y = x->dir;
    x->dir = y->esq;
    if (y->esq != arv->sentinela)
        y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == arv->sentinela)
        arv->raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;

    if (tipo == 0) // rotação de inserção
        arv->rotacoesInsercaoRB++;
    else // rotação de remoção
        arv->rotacoesRemocaoRB++;
}


void rotacaoDirRB(rubronegra *arv, noRB *x, int tipo) {
    noRB *y = x->esq;
    x->esq = y->dir;
    if (y->dir != arv->sentinela)
        y->dir->pai = x;
    y->pai = x->pai;
    if (x->pai == arv->sentinela)
        arv->raiz = y;
    else if (x == x->pai->dir)
        x->pai->dir = y;
    else
        x->pai->esq = y;
    y->dir = x;
    x->pai = y;

    if (tipo == 0) // rotação de inserção
        arv->rotacoesInsercaoRB++;
    else // rotação de remoção
        arv->rotacoesRemocaoRB++;
}


void imprimeOrdemRB(noRB *raiz, noRB *sentinela) {
    if (raiz != sentinela) {
        imprimeOrdemRB(raiz->esq, sentinela);
        printf("%d - %d - %c\n", raiz->chave, raiz->pai ? raiz->pai->chave : -1, raiz->cor);
        imprimeOrdemRB(raiz->dir, sentinela);
    }
}


void imprimePreOrdemRB(noRB *raiz, noRB *sentinela) {
    if (raiz != sentinela) {
        printf("%d - %d - %c\n", raiz->chave, raiz->pai ? raiz->pai->chave : -1, raiz->cor);
        imprimePreOrdemRB(raiz->esq, sentinela);
        imprimePreOrdemRB(raiz->dir, sentinela);
    }
}


noRB *getRaizRB(rubronegra *arv) {
    return arv->raiz;
}


int getNumElementosRB(rubronegra *arv) {
    return arv->numElementos;
}


int processaCargaRB(rubronegra *arv, char *nomeArquivo, int tipo) {
    int retorno = 0, valor, numElementos = 0;
    FILE *arq = fopen(nomeArquivo, "r");
    if (!arq) {
        return -2;
    }
    if (tipo == 1) {
        while (fscanf(arq, "%d", &valor) == 1) {
            retorno += insereNoRB(arv, valor);
            numElementos++;
        }
        fclose(arq);
        if (retorno == numElementos) {
            return 1;
        } else {
            return 0;
        }
    }

    while (fscanf(arq, "%d", &valor) == 1) {
        retorno += removeNoRB(arv, valor);
        numElementos++;
    }
    fclose(arq);
    if (retorno == numElementos) {
        return 1;
    } else {
        return 0;
    }
}


noRB *buscaRB(rubronegra *arv, int chave) {
    if (arv->raiz == arv->sentinela) {
        printf("A arvore esta vazia.");
        return NULL; // árvore vazia
    }

    noRB *encontra = arv->raiz;
    while (encontra != arv->sentinela && encontra->chave != chave) {
        if (chave < encontra->chave) {
            encontra = encontra->esq;
        } else {
            encontra = encontra->dir;
        }
    }
    if (encontra == arv->sentinela) {
        return NULL; // elemento não encontrado
    } else {
        return encontra;
    }
}
