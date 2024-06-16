#include <stdio.h>
#include <time.h>
#include "avl.h"
#include "rubronegra.h"
#include <stdlib.h>

int main() {
    avl *arv_avl = criaArvoreAVL();
    rubronegra *arv_rubronegra = criaArvoreRB();
    char nomeArquivo[30];
    clock_t inicio, fim;
    double tempo;
    int listaChaves[1000], i;
    noAVL *resultadoBuscaAVL;
    noRB *resultadoBuscaRB;

    // Para entrar com arquivo na rubro-negra:
    //printf("Digite a entrada: ");
    //scanf("%s", nomeArquivo);
    //processaCargaRB(arv_rubronegra, nomeArquivo, 1);

    printf("Arvore Rubro-Negra:\n");
    inicio = clock(); // tempo inicial da inserção na rubro-negra
    for (i = 1; i < 10001; i++) {
        insereNoRB(arv_rubronegra, i);
    }
    fim = clock(); // tempo final da inserção na rubro-negra

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo total gasto na rubro-negra para inserir 10.000 elementos: %f segundos\n", tempo);
    printf("Rotacoes para inserir 10000 elementos na rubro-negra: %d\n", arv_rubronegra->rotacoesInsercaoRB);

    // Caso queira imprimir em pre-ordem ou em ordem após a inserção na rubro-negra:
    //imprimePreOrdemRB(getRaizRB(arv_rubronegra), arv_rubronegra->sentinela);
    //printf("\n");
    //imprimeOrdemRB(getRaizRB(arv_rubronegra), arv_rubronegra->sentinela);

    for (i = 0; i < 1000; i++) {
        listaChaves[i] = rand() % 10000 + 1;  // Gera 1000 números aleatórios entre 1 e 10000
    }

    inicio = clock(); // tempo inicial de busca de 1000 elementos aleatórios na rubro-negra
    for (i = 0; i < 1000; i++) {
        buscaRB(arv_rubronegra, listaChaves[i]);
        // Caso queira printar os elementos encontrados:
        // printf("\n%d", resultadoBuscaRB->chave);
    }
    fim = clock(); // tempo final de busca de 1000 elementos aleatórios na rubro-negra

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo total gasto na rubro-negra para buscar 1.000 elementos: %f segundos\n", tempo);

    inicio = clock(); // tempo inicial da remoção na rubro-negra
    for (i = 1; i < 10001; i++) {
        removeNoRB(arv_rubronegra, i);
    }
    fim = clock(); // tempo final da remoção na rubro-negra

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo total gasto na rubro-negra para remover 10.000 elementos: %f segundos\n", tempo);
    printf("Rotacoes para remover 10000 elementos na rubro-negra: %d\n", arv_rubronegra->rotacoesRemocaoRB);

    // Caso queira imprimir em pre-ordem ou em ordem após a remoção na rubro-negra:
    //imprimePreOrdemRB(getRaizRB(arv_rubronegra), arv_rubronegra->sentinela);
    //printf("\n");
    //imprimeOrdemRB(getRaizRB(arv_rubronegra), arv_rubronegra->sentinela);
    free(arv_rubronegra);



    // Para entrar com arquivo na AVL:
    //printf("Digite a entrada: ");
    //scanf(" %s", nomeArquivo);
    //processaCargaAVL(arv_avl, nomeArquivo, 1);

    printf("\nArvore AVL:\n");
    inicio = clock(); // tempo inicial da inserção na AVL
    for (i = 1; i < 10001; i++) {
        insereNoAVL(arv_avl, i);
    }
    fim = clock(); // tempo final da inserção na AVL

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo total gasto na AVL para inserir 10.000 elementos: %f segundos\n", tempo);
    printf("Rotacoes para inserir 10000 elementos na AVL: %d\n", arv_avl->rotacoesInsercaoAVL);

    // Caso queira imprimir em pre-ordem ou em ordem após a inserção na AVL:
    //imprimePreOrdemAVL(getRaizAVL(arv_avl));
    //printf("\n");
    //imprimeOrdemAVL(getRaizAVL(arv_avl));

    inicio = clock(); // tempo inicial de busca de 1000 elementos aleatórios
    for (i = 0; i < 1000; i++) {
        buscaAVL(arv_avl, listaChaves[i]);
    }
    fim = clock(); // tempo final de busca de 1000 elementos aleatórios

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo total gasto na AVL para buscar 1.000 elementos: %f segundos\n", tempo);

    inicio = clock(); // tempo inicial da remoção na AVL
    for (i = 1; i < 10001; i++) {
        removeNoAVL(arv_avl, i);
    }
    fim = clock(); // tempo final da remoção na AVL

    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo total gasto na AVL para remover 10.000 elementos: %f segundos\n", tempo);
    printf("Rotacoes para remover 10000 elementos na AVL: %d\n", arv_avl->rotacoesRemocaoAVL);

    // Caso queira imprimir em pre-ordem ou em ordem após a remoção na AVL:
    //imprimePreOrdemAVL(getRaizAVL(arv_avl));
    //printf("\n");
    //imprimeOrdemAVL(getRaizAVL(arv_avl));
    free(arv_avl);
    return 0;
}
