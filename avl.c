//
// Created by davi on 26/05/2024.
//

#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

avl *criaArvoreAVL() {
    avl *arv = (avl*) malloc(sizeof(avl));
    if(!arv) {
        printf("Erro ao alocar memória para a criação da árvore.");
        return NULL;
    }

    arv -> sentinela = (noAVL*) malloc(sizeof(noAVL));
    if(!arv->sentinela) {
        printf("Erro ao alocar memória para a criação do nó sentinela");
        return NULL;
    }

    arv -> sentinela -> chave = -1000;
    arv -> sentinela -> Fdir = NULL;
    arv -> sentinela -> Fesq = NULL;
    arv -> sentinela -> pai = NULL;
    arv -> sentinela -> fb = 0;
    arv -> numElementos = 0;
    arv->rotacoesInsercaoAVL = 0;
    arv->rotacoesRemocaoAVL = 0;
    return arv;
}


int insereNoAVL(avl *arv, int valor) {
    noAVL *novoNo = (noAVL*)malloc(sizeof(noAVL)), *aux;
    if (!novoNo) {
        return 0;
    }
    novoNo->Fdir = novoNo->Fesq = NULL;
    novoNo->chave = valor;
    arv->numElementos++;
    novoNo->fb = 0;

    if(!arv->sentinela->Fdir)
    {
        arv->sentinela->Fdir = novoNo;
        novoNo->pai = arv->sentinela;
        return 1;
    }
    aux = arv->sentinela->Fdir;
    while(aux)
    {
        novoNo->pai = aux;
        if(aux->chave > valor)
        {
            aux = aux->Fesq;
        } else {
            aux = aux->Fdir;
        }
    }
    if(novoNo->pai->chave > valor)
    {
        novoNo->pai->Fesq = novoNo;
    } else {
        novoNo->pai->Fdir = novoNo;
    }

    atualizaFB_insercao(arv, novoNo);
    return 1;
}

int removeNoAVL(avl *arv, int valor) {
    if(!arv->sentinela->Fdir) {
        return 0;
    }

    noAVL *aux = arv->sentinela->Fdir, *sucessor;
    while(aux && aux->chave != valor) {
        if(aux->chave > valor) {
            aux = aux->Fesq;
        } else {
            aux = aux->Fdir;
        }
    }

    if(!aux) {
        return -1;
    }
    arv->numElementos--;
    if(!aux->Fdir && !aux->Fesq) {
        if(aux->pai->chave > valor) {
            aux->pai->Fesq = NULL;
        } else {
            aux->pai->Fdir = NULL;
        }
        atualizaFB_remocao(arv, aux->pai, valor);
        free(aux);
        return 1;
    }
    if(!aux->Fdir) {
        if(aux->pai->chave > valor) {
            aux->pai->Fesq = aux->Fesq;
        } else {
            aux->pai->Fdir = aux->Fesq;
        }
        aux->Fesq->pai = aux->pai;
        atualizaFB_remocao(arv, aux->pai, valor);
        free(aux);
        return 1;
    }
    if(!aux->Fesq) {
        if(aux->pai->chave > valor) {
            aux->pai->Fesq = aux->Fdir;
        } else {
            aux->pai->Fdir = aux->Fdir;
        }
        aux->Fdir->pai = aux->pai;
        atualizaFB_remocao(arv, aux->pai, valor);
        free(aux);
        return 1;
    }

    sucessor = aux->Fdir;
    while(sucessor->Fesq) {
        sucessor = sucessor->Fesq;
    }
    aux->chave = sucessor->chave;
    if(sucessor->pai == aux) {
        aux->Fdir = sucessor->Fdir;
        if(sucessor->Fdir) {
            sucessor->Fdir->pai = aux;
        }
    } else {
        sucessor->pai->Fesq = sucessor->Fdir;
        if(sucessor->Fdir) {
            sucessor->Fdir->pai = sucessor->pai;
        }
    }

    atualizaFB_remocao(arv, sucessor->pai, sucessor->chave);
    free(sucessor);
    return 1;
}


void imprimeOrdemAVL(noAVL *raiz) {
    if(raiz) {
        imprimeOrdemAVL(raiz->Fesq);
        printf("%d - %d\n",raiz->chave, raiz->pai->chave);
        imprimeOrdemAVL(raiz->Fdir);
    }
}


void imprimePreOrdemAVL(noAVL *raiz) {
    if(raiz) {
        printf("%d - %d - %d\n",raiz->chave, raiz->pai->chave, raiz->fb);
        imprimePreOrdemAVL(raiz->Fesq);
        imprimePreOrdemAVL(raiz->Fdir);
    }
}


noAVL *getRaizAVL(avl *arv) {
    return arv->sentinela->Fdir;
}


int getNumElementosAVL(avl *arv) {
    return arv->numElementos;
}


int processaCargaAVL(avl *arv, char *nomeArquivo, int tipo) {
    int retorno = 0, valor, numElementos = 0;
    FILE *arq = fopen(nomeArquivo, "r");

    if(!arq) {
        return -2;
    }
    if(tipo == 1) {
        while (!feof(arq)) {
            if(fscanf(arq, "%d", &valor) == 1) {
                retorno += insereNoAVL(arv, valor);
                numElementos++;
            }
        }
        if(retorno == numElementos) {
            return 1;
        } else {
            return 0;
        }
    }
    // tipo 2
    while(!feof(arq)) {
        if(fscanf (arq, "%d", &valor) == 1) {
            retorno += removeNoAVL(arv, valor);
            numElementos++;
        }
    }
    if(retorno == numElementos) {
        return 1;
    } else {
        return 0;
    }
}

void atualizaFB_insercao(avl *arv, noAVL *novoNo) {
    noAVL *aux = novoNo;

    do {
        if (aux->chave < aux->pai->chave) {
            aux->pai->fb--;
        } else {
            aux->pai->fb++;
        }
        aux = aux->pai;
    } while (aux->pai != arv->sentinela && aux->fb != 2 && aux->fb != -2 && aux->fb != 0);

    if (aux->fb == 2 || aux->fb == -2) {
        balanceamento(arv, aux, 0);
    }
}


void atualizaFB_remocao(avl *arv, noAVL *pai, int chaveRemovida) {
    noAVL *aux = pai;

    if (aux == arv->sentinela) {
        return;
    }
    if (pai->chave > chaveRemovida) {
        pai->fb++;
    } else {
        pai->fb--;
    }
    while (aux->fb == 0 && aux != arv->sentinela->Fdir) {
        aux = aux->pai;
        if (aux->chave > chaveRemovida) {
            aux->fb++;
        } else {
            aux->fb--;
        }
    }
    if (aux->fb == 2 || aux->fb == -2) {
        balanceamento(arv, aux, 1);
        if ((aux->pai != arv->sentinela) && (aux->pai->fb == 0)) {
            atualizaFB_remocao(arv, aux->pai->pai, chaveRemovida);
        }
    }
}


void balanceamento(avl *arv, noAVL *noDesbal, int tipo) {
    noAVL *filho;
    int fbNeto, fbFilho;

    if (noDesbal->fb == 2) {
        filho = noDesbal->Fdir;
        if (filho->fb == -1) {
            fbNeto = filho->Fesq->fb;
            rotacaoDirAVL(arv, filho, tipo);
            rotacaoEsqAVL(arv, noDesbal, tipo);
            if (fbNeto == 0) {
                filho->fb = 0;
                noDesbal->fb = 0;
            } else if (fbNeto == 1) {
                filho->fb = 0;
                noDesbal->fb = -1;
            } else {
                filho->fb = 1;
                noDesbal->fb = 0;
            }
        } else {
            fbFilho = filho->fb;
            rotacaoEsqAVL(arv, noDesbal, tipo);
            if (fbFilho == 0) {
                noDesbal->fb = 1;
                filho->fb = -1;
            }
        }
    } else {
        filho = noDesbal->Fesq;
        if (filho->fb == 1) {
            fbNeto = filho->Fdir->fb;
            rotacaoEsqAVL(arv, filho, tipo);
            rotacaoDirAVL(arv, noDesbal, tipo);
            if (fbNeto == 0) {
                filho->fb = 0;
                noDesbal->fb = 0;
            } else if (fbNeto == 1) {
                filho->fb = -1;
                noDesbal->fb = 0;
            } else {
                filho->fb = 0;
                noDesbal->fb = 1;
            }
        } else {
            fbFilho = filho->fb;
            rotacaoDirAVL(arv, noDesbal, tipo);
            if (fbFilho == 0) {
                noDesbal->fb = -1;
                filho->fb = 1;
            }
        }
    }
}


void rotacaoDirAVL(avl *arv, noAVL *noDesbal, int tipo) {
    noAVL *filho = noDesbal->Fesq;
    noDesbal->Fesq = filho->Fdir;

    if (filho->Fdir) {
        filho->Fdir->pai = noDesbal;
    }

    filho->pai = noDesbal->pai;
    if (noDesbal->pai->fb == -1000) { // se o pai é sentinela
        noDesbal->pai->Fdir = filho;
    } else if (noDesbal == noDesbal->pai->Fesq) { // se o desbalanceado for filho esquerdo
        noDesbal->pai->Fesq = filho;
    } else { // se o desbalanceado for filho direito
        noDesbal->pai->Fdir = filho;
    }

    filho->Fdir = noDesbal;
    noDesbal->pai = filho;

    // Atualização dos fatores de balanceamento
    filho->fb = 0;
    noDesbal->fb = 0;

    // Incrementar contador de rotações
    if (tipo == 0) { // Inserção
        arv->rotacoesInsercaoAVL++;
    } else { // Remoção
        arv->rotacoesRemocaoAVL++;
    }
}


void rotacaoEsqAVL(avl *arv, noAVL *noDesbal, int tipo) {
    noAVL *filho = noDesbal->Fdir;
    noDesbal->Fdir = filho->Fesq;

    if (filho->Fesq) {
        filho->Fesq->pai = noDesbal;
    }

    filho->pai = noDesbal->pai;
    if (noDesbal->pai->fb == -1000) { // se o pai é sentinela
        noDesbal->pai->Fdir = filho;
    } else if (noDesbal == noDesbal->pai->Fesq) { // se o desbalanceado for filho esquerdo
        noDesbal->pai->Fesq = filho;
    } else { // se o desbalanceado for filho direito
        noDesbal->pai->Fdir = filho;
    }

    filho->Fesq = noDesbal;
    noDesbal->pai = filho;

    filho->fb = 0;
    noDesbal->fb = 0;

    if (tipo == 0) { // rotação de inserção
        arv->rotacoesInsercaoAVL++;
    } else { // rotação de remoção
        arv->rotacoesRemocaoAVL++;
    }
}


noAVL *buscaAVL(avl *arv, int chave) {
    if (!arv->sentinela->Fdir) {
        return NULL; // árvore vazia
    }

    noAVL *encontra = arv->sentinela->Fdir;
    while (encontra != arv->sentinela && encontra->chave != chave) {
        if (chave < encontra->chave) {
            encontra = encontra->Fesq;
        } else {
            encontra = encontra->Fdir;
        }
    }

    if (encontra == arv->sentinela->Fdir) {
        return NULL; // elemento não encontrado
    }
    return encontra;
}
