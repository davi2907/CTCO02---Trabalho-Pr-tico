//
// Created by davi on 10/06/2024.
//

#ifndef RUBRONEGRA_H
#define RUBRONEGRA_H

// Definição das cores dos nós
#define V 'V'
#define P 'P'

// Estrutura do nó da árvore rubro-negra
typedef struct noRB {
    int chave;
    struct noRB *esq, *dir, *pai;
    char cor;
} noRB;

// Estrutura da árvore rubro-negra
typedef struct rubronegra {
    noRB *raiz;
    noRB *sentinela;
    int numElementos;
    int rotacoesInsercaoRB;
    int rotacoesRemocaoRB;
} rubronegra;

// Função que cria e retorna uma estrutura do tipo árvore balanceada utilizando o algoritmo rubro-negra
rubronegra *criaArvoreRB();

noRB *criaNoRB(int chave);

// Função que insere um elemento na árvore
int insereNoRB(rubronegra *arv, int valor);

// Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
int removeNoRB(rubronegra *arv, int valor);

// Função que imprime a árvore em ordem
void imprimeOrdemRB(noRB *raiz, noRB *sentinela);

// Função que imprime a árvore em pré-ordem
void imprimePreOrdemRB(noRB *raiz, noRB *sentinela);

// Função que retorna a raiz da árvore
noRB *getRaizRB(rubronegra *arv);

// Função que retorna a quantidade de elementos da árvore
int getNumElementosRB(rubronegra *arv);

//Função que lê um arquivo com números inteiros e um tipo
//Se o tipo for 1, a função deve chamar insereNo
//Se o tipo for 2, a função deve chamar removeNo
//Retorna -2 se o arquivo não puder ter sido lido
//Se o tipo for 1, insere os elementos na árvore e retorna os valores obtidos com o processamento da inserção
//Retorna 1 se a inserção foi realizada com sucesso
//Retorna 0 se não foi possível realizar a inserção
//Se o tipo for 2, remove os elementos da árvore e retorna os valores obtidos com o processamento da remoção
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Os valores retornados são tratados na main
int processaCargaRB(rubronegra *arv, char *nomeArquivo, int tipo);

//Função para encontrar o predecessor na remoção de nó com dois filhos
noRB *predecessor(noRB *x, noRB *sentinela);

//Função que corrige as cores e faz o balanceamento necessário após remoção
void corrigeRemocao(rubronegra *arv, noRB *x);

//Função que corrige as cores e faz o balanceamento necessário após inserção
void corrigeInsercao(rubronegra *arv, noRB *z);

//Função que implementa a rotação à esquerda
void rotacaoEsqRB(rubronegra *arv, noRB *x, int tipo);

//Função que implementa a rotação à direita
void rotacaoDirRB(rubronegra *arv, noRB *x, int tipo);

//Função que implementa a busca na árvore AVL
noRB *buscaRB(rubronegra *arv, int chave);

#endif // RUBRONEGRA_H
