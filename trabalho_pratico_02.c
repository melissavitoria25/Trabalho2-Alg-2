/*
 * Nome do Arquivo: trabalho_pratico_02.c
 * Autores: Cauã Teixeira Gomes Vieira - 2024009195
 *          Marcos Paulo Cyrillo da Silva - 2024015871
 *          Melissa Vitória dos Santos - 2024000313
 * Data de Criação: 27/06/2025
 * Última Modificação: 02/07/2025
 * Descrição: Este arquivo contém a implementação das funções referentes à estrutura de busca Árvore Rubro-Negra
 * referentes ao Trabalho Prático 02 da disciplina de Algoritmos e Estrutura de Dados II (CTCO02), cujo objetivo é
 * realizar a conversão de uma árvore 2-3-4 em uma árvore rubro-negra válida.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "trabalho_pratico_02.h"

#define ORDEM 4 // Árvore 2-3-4 (ordem 4)

// ==================== ESTRUTURAS ÁRVORE RUBRO NEGRA ==================== //
struct ArvoreRubroNegra {
    noRN *sentinelaRaiz;   // Nó sentinela superior
    noRN *sentinelaFolha;  // Nó sentinela folha (nulo)
    int alturaPreta;       // Altura preta da árvore
};

struct NoRubroNegro {
    int chave;
    char cor;              // 'V': vermelho ou 'P': preto
    int alturaPreta;       // Altura preta do nó
    noRN *esquerda;
    noRN *direita;
    noRN *pai;
};

// ==================== FUNÇÕES ÁRVORE RUBRO-NEGRA ==================== //
arvoreRN *alocaArvoreRubroNegra() {
    arvoreRN *arvore = (arvoreRN *)malloc(sizeof(arvoreRN));
    if (arvore == NULL) {
        return NULL;
    }

    // Aloca sentinela raiz
    noRN *sentinelaRaiz = (noRN *)malloc(sizeof(noRN));
    if (sentinelaRaiz == NULL) {
        free(arvore);
        return NULL;
    }

    // Aloca sentinela folha (nulo)
    noRN *sentinelaFolha = (noRN *)malloc(sizeof(noRN));
    if (sentinelaFolha == NULL) {
        free(sentinelaRaiz);
        free(arvore);
        return NULL;
    }

    // Inicializa sentinelas
    sentinelaRaiz->chave = -1000;
    sentinelaRaiz->cor = 'P';
    sentinelaRaiz->pai = NULL;
    sentinelaRaiz->esquerda = sentinelaFolha;
    sentinelaRaiz->direita = sentinelaFolha;

    sentinelaFolha->chave = -1000;
    sentinelaFolha->cor = 'P';
    sentinelaFolha->esquerda = NULL;
    sentinelaFolha->direita = NULL;
    sentinelaFolha->pai = NULL;

    arvore->sentinelaRaiz = sentinelaRaiz;
    arvore->sentinelaFolha = sentinelaFolha;
    arvore->alturaPreta = 0;

    return arvore;
}

noRN *alocaNo(arvoreRN *arvore, int chave) {
    noRN *novoNo = (noRN *)malloc(sizeof(noRN));
    if (novoNo == NULL) {
        return NULL;
    }

    novoNo->chave = chave;
    novoNo->cor = 'V';  // Novo nó sempre vermelho
    novoNo->alturaPreta = 0;
    novoNo->esquerda = arvore->sentinelaFolha;
    novoNo->direita = arvore->sentinelaFolha;
    novoNo->pai = NULL;

    return novoNo;
}

void inserirNo(arvoreRN *arvore, noRN *novoNo) {
    // Caso 1: Árvore vazia
    if (arvore->sentinelaRaiz->direita == arvore->sentinelaFolha) {
        arvore->sentinelaRaiz->direita = novoNo;
        novoNo->pai = arvore->sentinelaRaiz;
    }
    else {
        // Buscar posição de inserção
        noRN *atual = arvore->sentinelaRaiz->direita;
        noRN *paiAtual = arvore->sentinelaRaiz;

        while (atual != arvore->sentinelaFolha) {
            paiAtual = atual;
            if (novoNo->chave < atual->chave) {
                atual = atual->esquerda;
            } else {
                atual = atual->direita;
            }
        }

        // Inserir como filho do paiAtual
        if (novoNo->chave < paiAtual->chave) {
            paiAtual->esquerda = novoNo;
        } else {
            paiAtual->direita = novoNo;
        }
        novoNo->pai = paiAtual;
    }

    // Balancear após inserção
    balancearAposInsercao(arvore, novoNo);
    atualizarAlturaPretaArvore(arvore);
}

int removerNo(arvoreRN *arvore, int valor) {
    if (arvore == NULL) {
        return 0;
    }

    // z: nó a ser removido
    noRN *z = arvore->sentinelaRaiz->direita;
    noRN *paiZ = arvore->sentinelaRaiz;

    // Buscar z
    while (z != arvore->sentinelaFolha && z->chave != valor) {
        paiZ = z;
        if (valor < z->chave) {
            z = z->esquerda;
        } else {
            z = z->direita;
        }
    }

    if (z == arvore->sentinelaFolha) {
        return 0;
    }

    // y: nó que será efetivamente removido
    noRN *y = z;
    char corOriginalY = y->cor;
    noRN *x;  // x: nó que substituirá y

    // Caso 1: z tem no máximo um filho
    if (z->esquerda == arvore->sentinelaFolha) {
        x = z->direita;
        // Transplanta z por x
        if (z == paiZ->esquerda) {
            paiZ->esquerda = x;
        } else {
            paiZ->direita = x;
        }
        x->pai = paiZ;
    }
    else if (z->direita == arvore->sentinelaFolha) {
        x = z->esquerda;
        // Transplanta z por x
        if (z == paiZ->esquerda) {
            paiZ->esquerda = x;
        } else {
            paiZ->direita = x;
        }
        x->pai = paiZ;
    }
    else {
        // Caso 2: z tem dois filhos
        // y é o sucessor de z (menor nó da subárvore direita)
        y = z->direita;
        while (y->esquerda != arvore->sentinelaFolha) {
            y = y->esquerda;
        }
        corOriginalY = y->cor;
        x = y->direita;  // Filho de y

        // Atualiza pai de x
        if (y->pai != z) {
            if (y == y->pai->esquerda) {
                y->pai->esquerda = x;
            } else {
                y->pai->direita = x;
            }
            x->pai = y->pai;
        } else {
            // Caso especial: y é filho direito de z
            x->pai = y;
        }

        // Substitui z por y
        if (z == paiZ->esquerda) {
            paiZ->esquerda = y;
        } else {
            paiZ->direita = y;
        }
        y->pai = paiZ;

        // Atualiza ponteiros de y
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;

        if (y != z->direita) {
            y->direita = z->direita;
            y->direita->pai = y;
        }
        y->cor = z->cor;
    }

    // Se y era preto, balanceia
    if (corOriginalY == 'P') {
        balancearAposRemocao(arvore, x, x->pai);
    }

    free(z);
    atualizarAlturaPretaArvore(arvore);
    return 1;
}

void imprimirPreOrdem(arvoreRN *arvore, noRN *no) {
    if (no == arvore->sentinelaFolha) {
        return;
    }

    printf("%d -- %c -- %d\n", no->chave, no->cor, no->alturaPreta);
    imprimirPreOrdem(arvore, no->esquerda);
    imprimirPreOrdem(arvore, no->direita);
}

noRN *retornarRaiz(arvoreRN *arvore) {
    return arvore->sentinelaRaiz->direita;
}

void rotacionarEsquerda(arvoreRN *arvore, noRN *x) {
    // y é o filho direito de x
    noRN *y = x->direita;

    // Transfere subárvore esquerda de y
    x->direita = y->esquerda;
    if (y->esquerda != arvore->sentinelaFolha) {
        y->esquerda->pai = x;
    }

    // Atualiza pai de y
    y->pai = x->pai;
    if (x == x->pai->esquerda) {
        x->pai->esquerda = y;
    } else {
        x->pai->direita = y;
    }

    // Coloca x à esquerda de y
    y->esquerda = x;
    x->pai = y;
}

void rotacionarDireita(arvoreRN *arvore, noRN *x) {
    // y é o filho esquerdo de x
    noRN *y = x->esquerda;

    // Transfere subárvore direita de y
    x->esquerda = y->direita;
    if (y->direita != arvore->sentinelaFolha) {
        y->direita->pai = x;
    }

    // Atualiza pai de y
    y->pai = x->pai;
    if (x == x->pai->direita) {
        x->pai->direita = y;
    } else {
        x->pai->esquerda = y;
    }

    // Coloca x à direita de y
    y->direita = x;
    x->pai = y;
}

void balancearAposInsercao(arvoreRN *arvore, noRN *z) {
    while (z->pai->cor == 'V') {
        // Caso A: Pai é filho esquerdo
        if (z->pai == z->pai->pai->esquerda) {
            noRN *tio = z->pai->pai->direita;

            // Caso 1: Tio vermelho
            if (tio->cor == 'V') {
                z->pai->cor = 'P';
                tio->cor = 'P';
                z->pai->pai->cor = 'V';
                z = z->pai->pai;
            }
            else {
                // Caso 2: Tio preto e z é filho direito
                if (z == z->pai->direita) {
                    z = z->pai;
                    rotacionarEsquerda(arvore, z);
                }
                // Caso 3: Tio preto e z é filho esquerdo
                z->pai->cor = 'P';
                z->pai->pai->cor = 'V';
                rotacionarDireita(arvore, z->pai->pai);
            }
        }
        // Caso B: Pai é filho direito (simétrico)
        else {
            noRN *tio = z->pai->pai->esquerda;

            // Caso 1: Tio vermelho
            if (tio->cor == 'V') {
                z->pai->cor = 'P';
                tio->cor = 'P';
                z->pai->pai->cor = 'V';
                z = z->pai->pai;
            }
            else {
                // Caso 2: Tio preto e z é filho esquerdo
                if (z == z->pai->esquerda) {
                    z = z->pai;
                    rotacionarDireita(arvore, z);
                }
                // Caso 3: Tio preto e z é filho direito
                z->pai->cor = 'P';
                z->pai->pai->cor = 'V';
                rotacionarEsquerda(arvore, z->pai->pai);
            }
        }
    }
    arvore->sentinelaRaiz->direita->cor = 'P';  // Raiz sempre preta
}

void balancearAposRemocao(arvoreRN *arvore, noRN *x, noRN *paiX) {
    while (x != arvore->sentinelaRaiz->direita && x->cor == 'P') {
        if (x == paiX->esquerda) {
            // w: irmão de x
            noRN *w = paiX->direita;

            // Caso 1: Irmão vermelho
            if (w->cor == 'V') {
                w->cor = 'P';
                paiX->cor = 'V';
                rotacionarEsquerda(arvore, paiX);
                w = paiX->direita;
            }

            // Caso 2: Ambos os filhos do irmão são pretos
            if (w->esquerda->cor == 'P' && w->direita->cor == 'P') {
                w->cor = 'V';
                x = paiX;
                paiX = x->pai;
            }
            else {
                // Caso 3: Filho direito do irmão é preto
                if (w->direita->cor == 'P') {
                    w->esquerda->cor = 'P';
                    w->cor = 'V';
                    rotacionarDireita(arvore, w);
                    w = paiX->direita;
                }

                // Caso 4: Filho direito do irmão é vermelho
                w->cor = paiX->cor;
                paiX->cor = 'P';
                w->direita->cor = 'P';
                rotacionarEsquerda(arvore, paiX);
                x = arvore->sentinelaRaiz->direita;  // Sair do loop
            }
        }
        else {  // Simétrico: x é filho direito
            noRN *w = paiX->esquerda;

            // Caso 1: Irmão vermelho
            if (w->cor == 'V') {
                w->cor = 'P';
                paiX->cor = 'V';
                rotacionarDireita(arvore, paiX);
                w = paiX->esquerda;
            }

            // Caso 2: Ambos os filhos do irmão são pretos
            if (w->direita->cor == 'P' && w->esquerda->cor == 'P') {
                w->cor = 'V';
                x = paiX;
                paiX = x->pai;
            }
            else {
                // Caso 3: Filho esquerdo do irmão é preto
                if (w->esquerda->cor == 'P') {
                    w->direita->cor = 'P';
                    w->cor = 'V';
                    rotacionarEsquerda(arvore, w);
                    w = paiX->esquerda;
                }

                // Caso 4: Filho esquerdo do irmão é vermelho
                w->cor = paiX->cor;
                paiX->cor = 'P';
                w->esquerda->cor = 'P';
                rotacionarDireita(arvore, paiX);
                x = arvore->sentinelaRaiz->direita;  // Sair do loop
            }
        }
    }
    x->cor = 'P';  // Garante propriedade rubro-negra
}

int atualizarAlturaPreta(arvoreRN *arvore, noRN *no) {
    if (no == arvore->sentinelaFolha) {
        return 0;
    }

    int alturaEsquerda = atualizarAlturaPreta(arvore, no->esquerda);
    int alturaDireita = atualizarAlturaPreta(arvore, no->direita);

    int incremento;
    if (no->cor == 'P') {
        incremento = 1;
    } else {
        incremento = 0;
    }

    int alturaNo;
    if (alturaEsquerda > alturaDireita) {
        alturaNo = alturaEsquerda;
    } else {
        alturaNo = alturaDireita;
    }
    alturaNo += incremento;

    no->alturaPreta = alturaNo;
    return alturaNo;
}

void atualizarAlturaPretaArvore(arvoreRN *arvore) {
    if (arvore->sentinelaRaiz->direita != arvore->sentinelaFolha) {
        arvore->alturaPreta = atualizarAlturaPreta(arvore, arvore->sentinelaRaiz->direita);
    } else {
        arvore->alturaPreta = 0;
    }
}

void liberarNosRecursivo(arvoreRN *arvore, noRN *no) {
    if (no == arvore->sentinelaFolha) {
        return;
    }

    liberarNosRecursivo(arvore, no->esquerda);
    liberarNosRecursivo(arvore, no->direita);
    free(no);
}

void liberarArvoreRubroNegra(arvoreRN *arvore) {
    if (arvore == NULL) {
        return;
    }

    liberarNosRecursivo(arvore, arvore->sentinelaRaiz->direita);
    free(arvore->sentinelaRaiz);
    free(arvore->sentinelaFolha);
    free(arvore);
}
// ==================== ESTRUTURA DA ÁRVORE B ==================== //
struct noB {
    int *chaves;
    noB **filhos;
    noB *pai;
    int quantidadeChaves;
    char ehFolha;
};

struct arvoreB {
    noB *raiz;
    int contadorSplits;
    int contadorRotacoes;
    int contadorMerges;
};

// ==================== FUNÇÕES ÁRVORE B 2-3-4 ==================== //
arvoreB *alocaArvoreB() {
    arvoreB *arvore = (arvoreB *)malloc(sizeof(arvoreB));
    if (arvore == NULL) {
        return NULL;
    }
    arvore->raiz = NULL;
    arvore->contadorSplits = 0;
    arvore->contadorRotacoes = 0;
    arvore->contadorMerges = 0;
    return arvore;
}

noB *alocaNoB() {
    noB *novoNo = (noB *)malloc(sizeof(noB));
    if (novoNo == NULL) {
        return NULL;
    }

    novoNo->pai = NULL;
    novoNo->quantidadeChaves = 0;
    novoNo->ehFolha = 'S';

    novoNo->chaves = (int *)malloc((ORDEM - 1) * sizeof(int));
    if (novoNo->chaves == NULL) {
        free(novoNo);
        return NULL;
    }

    novoNo->filhos = (noB **)malloc(ORDEM * sizeof(noB *));
    if (novoNo->filhos == NULL) {
        free(novoNo->chaves);
        free(novoNo);
        return NULL;
    }

    for (int i = 0; i < ORDEM; i++) {
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}

void inserirChave(int valor, arvoreB *arv) {
    // Caso 1: Árvore vazia
    if (arv->raiz == NULL) {
        arv->raiz = alocaNoB();
        if (arv->raiz == NULL) {
            return;
        }
        arv->raiz->chaves[0] = valor;
        arv->raiz->quantidadeChaves = 1;
        return;
    }

    // Caso 2: Raiz cheia
    if (arv->raiz->quantidadeChaves == ORDEM - 1) {
        // Cria nova raiz
        noB *novaRaiz = alocaNoB();
        if (novaRaiz == NULL) {
            return;
        }
        novaRaiz->ehFolha = 'N';
        novaRaiz->filhos[0] = arv->raiz;
        arv->raiz->pai = novaRaiz;
        arv->raiz = novaRaiz;

        // Divide a antiga raiz
        dividirFilho(novaRaiz, 0, arv);

        // Insere a chave na árvore modificada
        inserirNaoCheio(novaRaiz, valor, arv);
    } else {
        inserirNaoCheio(arv->raiz, valor, arv);
    }
}

void dividirFilho(noB *pai, int indiceFilho, arvoreB *arv) {
    // y: filho cheio que será dividido
    noB *y = pai->filhos[indiceFilho];
    // z: novo nó que receberá as chaves maiores de y
    noB *z = alocaNoB();
    if (z == NULL) {
        return;
    }
    z->ehFolha = y->ehFolha;

    // O nó y (cheio) tem ORDEM-1 chaves. A chave do meio é a de índice 1 (0-indexed)
    int chaveMeio = y->chaves[1];

    // Transfere a última chave de y para z
    z->chaves[0] = y->chaves[2];
    z->quantidadeChaves = 1;
    y->quantidadeChaves = 1; // y agora tem uma chave (a primeira)

    // Se y não for folha, transfere os dois últimos filhos para z
    if (y->ehFolha == 'N') {
        z->filhos[0] = y->filhos[2];  // Correto: filho 2 de y -> filho 0 de z
        z->filhos[1] = y->filhos[3];  // Correto: filho 3 de y -> filho 1 de z
        if (z->filhos[0] != NULL) {
            z->filhos[0]->pai = z;
        }
        if (z->filhos[1] != NULL) {
            z->filhos[1]->pai = z;
        }
        // Atualiza os ponteiros de filhos de y
        y->filhos[2] = NULL;
        y->filhos[3] = NULL;
    }

    // Abre espaço no pai para a nova chave (chaveMeio) e para o novo filho (z)
    for (int j = pai->quantidadeChaves; j > indiceFilho; j--) {
        pai->chaves[j] = pai->chaves[j - 1];
    }
    for (int j = pai->quantidadeChaves + 1; j > indiceFilho + 1; j--) {
        pai->filhos[j] = pai->filhos[j - 1];
    }

    // Insere a chave do meio no pai e conecta z como filho à direita
    pai->chaves[indiceFilho] = chaveMeio;
    pai->filhos[indiceFilho + 1] = z;
    z->pai = pai;
    pai->quantidadeChaves++;

    arv->contadorSplits++;
}

void inserirNaoCheio(noB *no, int valor, arvoreB *arv) {
    // i: índice para percorrer as chaves
    int i = no->quantidadeChaves - 1;

    // Caso 1: nó é folha
    if (no->ehFolha == 'S') {
        // Desloca chaves maiores para abrir espaço para a nova chave
        while (i >= 0 && valor < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = valor;
        no->quantidadeChaves++;
    }
    // Caso 2: nó não é folha
    else {
        // Encontra o filho onde a chave deve ser inserida
        while (i >= 0 && valor < no->chaves[i]) {
            i--;
        }
        i++;

        // Se o filho encontrado estiver cheio, divide-o
        if (no->filhos[i]->quantidadeChaves == ORDEM - 1) {
            dividirFilho(no, i, arv);
            if (valor > no->chaves[i]) {
                i++;
            }
        }
        // Correção: ordem dos parâmetros corrigida
        inserirNaoCheio(no->filhos[i], valor, arv); // Chamada recursiva corrigida
    }
}


noB *buscarNo(noB *no, int valor, int *indiceChave) {
    if (no == NULL) {
        return NULL;
    }

    int i = 0;
    while (i < no->quantidadeChaves && valor > no->chaves[i]) {
        i++;
    }

    if (i < no->quantidadeChaves && valor == no->chaves[i]) {
        *indiceChave = i;
        return no;
    } else if (no->ehFolha == 'S') {
        return NULL;
    } else {
        return buscarNo(no->filhos[i], valor, indiceChave);
    }
}

void removerChave(int valor, arvoreB *arv) {
    if (arv == NULL || arv->raiz == NULL) {
        return;
    }

    int indiceChave;
    noB *noAlvo = buscarNo(arv->raiz, valor, &indiceChave);

    if (noAlvo == NULL) {
        return;
    }

    removerChaveDoNo(noAlvo, indiceChave, arv);

    // Se a raiz ficou sem chaves e tem um filho, o filho se torna a nova raiz
    if (arv->raiz->quantidadeChaves == 0 && arv->raiz->ehFolha == 'N') {
        noB *antigaRaiz = arv->raiz;
        arv->raiz = antigaRaiz->filhos[0];
        if (arv->raiz != NULL) {
            arv->raiz->pai = NULL;
        }
        free(antigaRaiz->chaves);
        free(antigaRaiz->filhos);
        free(antigaRaiz);
    }
}

void removerChaveDoNo(noB *no, int indiceChave, arvoreB *arv) {
    // Caso 1: Remoção em folha
    if (no->ehFolha == 'S') {
        // Desloca as chaves para preencher o espaço
        for (int i = indiceChave; i < no->quantidadeChaves - 1; i++) {
            no->chaves[i] = no->chaves[i + 1];
        }
        no->quantidadeChaves--;
    }
    // Caso 2: Remoção em nó interno
    else {
        int chave = no->chaves[indiceChave];
        noB *filhoEsq = no->filhos[indiceChave];
        noB *filhoDir = no->filhos[indiceChave + 1];

        // Caso 2a: O filho esquerdo tem pelo menos uma chave extra
        if (filhoEsq->quantidadeChaves >= 2) {
            int predecessor = getPredecessor(filhoEsq);
            no->chaves[indiceChave] = predecessor;
            // Busca o nó folha que contém o predecessor para removê-lo
            int predIndice;
            noB *predNo = buscarNo(filhoEsq, predecessor, &predIndice);
            removerChaveDoNo(predNo, predIndice, arv);
        }
        // Caso 2b: O filho direito tem pelo menos uma chave extra
        else if (filhoDir->quantidadeChaves >= 2) {
            int sucessor = getSucessor(filhoDir);
            no->chaves[indiceChave] = sucessor;
            // Busca o nó folha que contém o sucessor para removê-lo
            int sucIndice;
            noB *sucNo = buscarNo(filhoDir, sucessor, &sucIndice);
            removerChaveDoNo(sucNo, sucIndice, arv);
        }
        // Caso 2c: Ambos os filhos têm o número mínimo de chaves (1)
        else {
            // Funde a chave e o filho direito no filho esquerdo
            fundirFilhos(no, indiceChave, arv);
            // Agora a chave a ser removida está no filho esquerdo (na posição 1)
            removerChaveDoNo(filhoEsq, 1, arv);
        }
    }

    // Após a remoção, verifica se o nó ficou em underflow
    if (no->quantidadeChaves < 1) {
        corrigirUnderflow(no, arv);
    }
}

void corrigirUnderflow(noB *no, arvoreB *arv) {
    noB *pai = no->pai;
    if (pai == NULL) {
        return;
    }

    // Encontra o índice do nó no vetor de filhos do pai
    int indiceNo = 0;
    while (indiceNo <= pai->quantidadeChaves && pai->filhos[indiceNo] != no) {
        indiceNo++;
    }

    // Tenta emprestar do irmão esquerdo
    if (indiceNo > 0) {
        noB *irmaoEsq = pai->filhos[indiceNo - 1];
        if (irmaoEsq->quantidadeChaves >= 2) {
            // Rotação à direita
            // Desloca chaves e filhos do nó para a direita
            for (int i = no->quantidadeChaves; i > 0; i--) {
                no->chaves[i] = no->chaves[i - 1];
            }
            if (no->ehFolha == 'N') {
                for (int i = no->quantidadeChaves + 1; i > 0; i--) {
                    no->filhos[i] = no->filhos[i - 1];
                }
            }

            // A chave do pai desce para o nó
            no->chaves[0] = pai->chaves[indiceNo - 1];
            no->quantidadeChaves++;

            // A última chave do irmão esquerdo sobe para o pai
            pai->chaves[indiceNo - 1] = irmaoEsq->chaves[irmaoEsq->quantidadeChaves - 1];

            // Move o último filho do irmão esquerdo para o nó, se não for folha
            if (no->ehFolha == 'N') {
                no->filhos[0] = irmaoEsq->filhos[irmaoEsq->quantidadeChaves];
                if (no->filhos[0] != NULL) {
                    no->filhos[0]->pai = no;
                }
                irmaoEsq->filhos[irmaoEsq->quantidadeChaves] = NULL;
            }

            irmaoEsq->quantidadeChaves--;
            arv->contadorRotacoes++;
            return;
        }
    }

    // Tenta emprestar do irmão direito
    if (indiceNo < pai->quantidadeChaves) {
        noB *irmaoDir = pai->filhos[indiceNo + 1];
        if (irmaoDir->quantidadeChaves >= 2) {
            // Rotação à esquerda
            // A chave do pai desce para o nó
            no->chaves[no->quantidadeChaves] = pai->chaves[indiceNo];
            no->quantidadeChaves++;

            // A primeira chave do irmão direito sobe para o pai
            pai->chaves[indiceNo] = irmaoDir->chaves[0];

            // Desloca as chaves do irmão direito para a esquerda
            for (int i = 0; i < irmaoDir->quantidadeChaves - 1; i++) {
                irmaoDir->chaves[i] = irmaoDir->chaves[i + 1];
            }

            // Move o primeiro filho do irmão direito para o nó, se não for folha
            if (no->ehFolha == 'N') {
                no->filhos[no->quantidadeChaves] = irmaoDir->filhos[0];
                if (no->filhos[no->quantidadeChaves] != NULL) {
                    no->filhos[no->quantidadeChaves]->pai = no;
                }
                for (int i = 0; i < irmaoDir->quantidadeChaves; i++) {
                    irmaoDir->filhos[i] = irmaoDir->filhos[i + 1];
                }
                irmaoDir->filhos[irmaoDir->quantidadeChaves] = NULL;
            }

            irmaoDir->quantidadeChaves--;
            arv->contadorRotacoes++;
            return;
        }
    }

    // Não foi possível emprestar: fundir com um irmão
    if (indiceNo > 0) {
        // Fundir com o irmão esquerdo
        fundirFilhos(pai, indiceNo - 1, arv);
    } else {
        // Fundir com o irmão direito
        fundirFilhos(pai, indiceNo, arv);
    }
}

void fundirFilhos(noB *pai, int indiceFilhoEsq, arvoreB *arv) {
    // y: filho esquerdo (que receberá a fusão)
    noB *y = pai->filhos[indiceFilhoEsq];
    // z: filho direito (que será fundido em y e depois liberado)
    noB *z = pai->filhos[indiceFilhoEsq + 1];

    // A chave do pai desce para y
    y->chaves[y->quantidadeChaves] = pai->chaves[indiceFilhoEsq];
    y->quantidadeChaves++;

    // Copia as chaves de z para y
    for (int i = 0; i < z->quantidadeChaves; i++) {
        y->chaves[y->quantidadeChaves + i] = z->chaves[i];
    }

    // Copia os filhos de z para y, se não forem folhas
    if (y->ehFolha == 'N') {
        for (int i = 0; i <= z->quantidadeChaves; i++) {
            y->filhos[y->quantidadeChaves + 1 + i] = z->filhos[i];
            if (z->filhos[i] != NULL) {
                z->filhos[i]->pai = y;
            }
        }
    }

    y->quantidadeChaves += z->quantidadeChaves;

    // Remove a chave do pai e o ponteiro para z
    for (int i = indiceFilhoEsq; i < pai->quantidadeChaves - 1; i++) {
        pai->chaves[i] = pai->chaves[i + 1];
    }
    for (int i = indiceFilhoEsq + 1; i < pai->quantidadeChaves; i++) {
        pai->filhos[i] = pai->filhos[i + 1];
    }
    pai->quantidadeChaves--;

    // Libera z
    free(z->chaves);
    free(z->filhos);
    free(z);

    // Se o pai ficou em underflow, corrige recursivamente
    if (pai->quantidadeChaves < 1 && pai->pai != NULL) {
        corrigirUnderflow(pai, arv);
    }
    arv->contadorMerges++;
}

int getPredecessor(noB *no) {
    // Vai até o filho mais à direita
    while (no->ehFolha == 'N') {
        no = no->filhos[no->quantidadeChaves];
    }
    return no->chaves[no->quantidadeChaves - 1];
}

int getSucessor(noB *no) {
    // Vai até o filho mais à esquerda
    while (no->ehFolha == 'N') {
        no = no->filhos[0];
    }
    return no->chaves[0];
}

void imprimirArvore(arvoreB *arv) {
    if (arv == NULL || arv->raiz == NULL) {
        printf("Arvore vazia!\n");
        return;
    }
    printf("\n=== Arvore B (2-3-4) ===\n");
    imprimirNo(arv->raiz);
    printf("=========================\n");
}

void imprimirNo(noB *no) {
    if (no == NULL) {
        return;
    }

    printf("[");
    for (int i = 0; i < no->quantidadeChaves; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->quantidadeChaves - 1) {
            printf(", ");
        }
    }
    printf("] (ocupacao: %d)", no->quantidadeChaves);

    if (no->pai != NULL) {
        printf(" (pai: ");
        for (int i = 0; i < no->pai->quantidadeChaves; i++) {
            printf("%d ", no->pai->chaves[i]);
        }
        printf(")");
    }
    printf("\n");

    if (no->ehFolha == 'N') {
        for (int i = 0; i <= no->quantidadeChaves; i++) {
            imprimirNo(no->filhos[i]);
        }
    }
}

int calcularAltura(noB *no) {
    if (no == NULL) return 0;
    if (no->ehFolha == 'S') return 1;
    return 1 + calcularAltura(no->filhos[0]);
}

int contarBlocosCheios(noB *no) {
    if (no == NULL) return 0;
    int count = (no->quantidadeChaves == 3) ? 1 : 0;
    if (no->ehFolha == 'N') {
        for (int i = 0; i <= no->quantidadeChaves; i++) {
            count += contarBlocosCheios(no->filhos[i]);
        }
    }
    return count;
}

void liberarNoB(noB *no) {
    if (no == NULL) {
        return;
    }
    if (no->ehFolha == 'N') {
        for (int i = 0; i <= no->quantidadeChaves; i++) {
            liberarNoB(no->filhos[i]);
        }
    }
    free(no->chaves);
    free(no->filhos);
    free(no);
}

void liberarArvoreB(arvoreB *arv) {
    if (arv == NULL) {
        return;
    }
    liberarNoB(arv->raiz);
    free(arv);
}

/**
 * converterNoBparaRN
 * Converte recursivamente um nó da Árvore B 2-3-4 em uma subárvore
 * correspondente na Árvore Rubro-Negra.
 * @param noB    Ponteiro para o nó da Árvore B a ser convertido
 * @param arvRN  Ponteiro para a Árvore Rubro-Negra destino (com sentinelas)
 * @return       Ponteiro para o nó raiz da subárvore Rubro-Negra criada
 */
static noRN* converterNoBparaRN(noB *noB, arvoreRN *arvRN) {
    // Caso base: nó B nulo — retorna sentinela folha
    if (noB == NULL) {
        return arvRN->sentinelaFolha;
    }

    int n = noB->quantidadeChaves;
    noRN *meuNo = NULL;

    // Caso 1: (2-nó, k = 2) — 1 chave, 2 filhos
    if (n == 1) {
        meuNo = alocaNo(arvRN, noB->chaves[0]);
        meuNo->cor = 'P';
        meuNo->esquerda = converterNoBparaRN(noB->filhos[0], arvRN);
        meuNo->direita  = converterNoBparaRN(noB->filhos[1], arvRN);
    }
    // Caso 2: (3-nó, k = 3) — 2 chaves, 3 filhos
    else if (n == 2) {
        meuNo = alocaNo(arvRN, noB->chaves[1]);
        meuNo->cor = 'P';

        noRN *esq = alocaNo(arvRN, noB->chaves[0]);
        esq->cor = 'V';
        esq->pai = meuNo;
        esq->esquerda = converterNoBparaRN(noB->filhos[0], arvRN);
        esq->direita  = converterNoBparaRN(noB->filhos[1], arvRN);

        meuNo->esquerda = esq;
        meuNo->direita  = converterNoBparaRN(noB->filhos[2], arvRN);
    }
    // Caso 3: (4-nó, k = 4) — 3 chaves, 4 filhos
    else if (n == 3) {
        meuNo = alocaNo(arvRN, noB->chaves[1]);
        meuNo->cor = 'P';

        noRN *esq = alocaNo(arvRN, noB->chaves[0]);
        noRN *dir = alocaNo(arvRN, noB->chaves[2]);
        esq->cor = dir->cor = 'V';
        esq->pai = dir->pai = meuNo;

        esq->esquerda = converterNoBparaRN(noB->filhos[0], arvRN);
        esq->direita  = converterNoBparaRN(noB->filhos[1], arvRN);
        dir->esquerda = converterNoBparaRN(noB->filhos[2], arvRN);
        dir->direita  = converterNoBparaRN(noB->filhos[3], arvRN);

        meuNo->esquerda = esq;
        meuNo->direita  = dir;
    }

    // Ajusta ponteiros pai dos filhos válidos
    if (meuNo->esquerda != arvRN->sentinelaFolha)
        meuNo->esquerda->pai = meuNo;
    if (meuNo->direita != arvRN->sentinelaFolha)
        meuNo->direita->pai = meuNo;

    return meuNo;
}

arvoreRN *converterBparaRB(arvoreB *arvB) {
    if (arvB == NULL) return NULL;

    arvoreRN *arvRN = alocaArvoreRubroNegra();
    if (arvB->raiz == NULL) return arvRN;

    // Converte raiz de B e encaixa como filho do sentinela raiz
    noRN *root = converterNoBparaRN(arvB->raiz, arvRN);
    arvRN->sentinelaRaiz->direita = root;
    root->pai = arvRN->sentinelaRaiz;

    atualizarAlturaPretaArvore(arvRN);
    return arvRN;
}

// ==================== FUNÇÕES PARA ACESSAR AS ESTATÍSTICAS DA ÁRVORE ==================== //
int alturaArvoreB(arvoreB *arv) {
    return calcularAltura(arv->raiz);
}

int obterContadorSplits(arvoreB *arv) {
    return arv->contadorSplits;
}

int obterContadorRotacoes(arvoreB *arv) {
    return arv->contadorRotacoes;
}

int obterContadorMerges(arvoreB *arv) {
    return arv->contadorMerges;
}

int obterBlocosCheios(arvoreB *arv) {
    return contarBlocosCheios(arv->raiz);
}

void resetarContadorSplits(arvoreB *arv) {
    if (arv) {
        arv->contadorSplits = 0;
    }
}

void resetarContadoresRemocao(arvoreB *arv) {
    if (arv) {
        arv->contadorRotacoes = 0;
        arv->contadorMerges = 0;
    }
}

// ==================== FUNÇÃO AUXILIAR PARA GERAR AQUIVO ==================== //
void gerarArquivoAleatorio(const char *nomeArquivo, int quantidade) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        perror("Erro ao criar arquivo");
        exit(EXIT_FAILURE);
    }
    srand((unsigned)time(NULL));
    for (int i = 0; i < quantidade; i++) {
        int num = rand() % quantidade + 1;  // valores entre 0 e quantidade
        fprintf(fp, "%d\n", num);
    }
    fclose(fp);
}

// ==================== FUNÇÕES UTILIZADAS NA REMOÇÃO EM LOTE ==================== //
static int contarChavesRec(noB *no) {
    if (no == NULL) return 0;

    int count = no->quantidadeChaves;

    if (no->ehFolha == 'N') {
        for (int i = 0; i <= no->quantidadeChaves; i++) {
            if (no->filhos[i] != NULL) {
                count += contarChavesRec(no->filhos[i]);
            }
        }
    }
    return count;
}

int arvoreB_contarChaves(arvoreB *arv) {
    if (arv == NULL || arv->raiz == NULL) return 0;
    return contarChavesRec(arv->raiz);
}

// Função recursiva para coletar chaves
static void coletarChavesRec(noB *no, int *array, int *index) {
    if (no == NULL) return;

    // Coletar chaves do nó atual
    for (int i = 0; i < no->quantidadeChaves; i++) {
        array[*index] = no->chaves[i];
        (*index)++;
    }

    // Coletar recursivamente dos filhos
    if (no->ehFolha == 'N') {
        for (int i = 0; i <= no->quantidadeChaves; i++) {
            if (no->filhos[i] != NULL) {
                coletarChavesRec(no->filhos[i], array, index);
            }
        }
    }
}

int *arvoreB_coletarChaves(arvoreB *arv, int *n) {
    if (arv == NULL || arv->raiz == NULL) {
        *n = 0;
        return NULL;
    }

    *n = arvoreB_contarChaves(arv);
    if (*n <= 0) {
        return NULL;
    }

    int *array = (int *)malloc(*n * sizeof(int));
    if (array == NULL) {
        *n = 0;
        return NULL;
    }

    int index = 0;
    coletarChavesRec(arv->raiz, array, &index);
    return array;
}