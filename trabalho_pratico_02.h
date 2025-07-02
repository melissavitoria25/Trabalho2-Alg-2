/*
 *  Nome do Arquivo: main.c
 *  Autores: Cauã Teixeira Gomes Vieira - 2024009195
 *           Marcos Paulo Cyrillo da Silva - 2024015871
 *           Melissa Vitória dos Santos - 2024000313
 *  Data de Criação: 27/06/2025
 *  Última Modificação: 02/07/2025
 *  Descrição: Programa principal para teste das operações de Árvore Rubro-Negra
 *            (inserção, remoção, impressão e balanceamento).
 */

#ifndef TRABALHO_PRATICO_02_H
#define TRABALHO_PRATICO_02_H

// ==================== DEFINIÇÕES DE TIPO DA ÁRVORE RUBRO NEGRA ==================== //
typedef struct ArvoreRubroNegra arvoreRN;
typedef struct NoRubroNegro noRN;

// ==================== DEFINIÇÕES DE TIPO DA ÁRVORE B 2-3-4 ==================== //
typedef struct noB noB;
typedef struct arvoreB arvoreB;

// ==================== ASSINATURA DAS FUNÇÕES DA ÁRVORE RUBRO-NEGRA ==================== //
/**
 * alocaArvoreRubroNegra
 * Aloca e inicializa uma estrutura de árvore rubro-negra.
 * @return Ponteiro para a árvore alocada, ou NULL em caso de falha.
 */
arvoreRN *alocaArvoreRubroNegra();

/**
 * alocaNo
 * Aloca e inicializa um novo nó rubro-negro.
 * @param arvore Ponteiro para a árvore
 * @param chave Valor a ser armazenado no nó
 * @return Ponteiro para o nó alocado, ou NULL em caso de falha
 */
noRN *alocaNo(arvoreRN *arvore, int chave);

/**
 * inserirNo
 * Insere um novo nó na árvore rubro-negra.
 * @param arvore Ponteiro para a árvore
 * @param novoNo Ponteiro para o nó a ser inserido
 */
void inserirNo(arvoreRN *arvore, noRN *novoNo);

/**
 * removerNo
 * Remove um nó da árvore rubro-negra.
 * @param arvore Ponteiro para a árvore
 * @param valor Chave do nó a ser removido
 * @return 1 se o nó foi removido, 0 caso contrário
 */
int removerNo(arvoreRN *arvore, int valor);

/**
 * imprimirPreOrdem
 * Imprime a árvore em pré-ordem (raiz-esquerda-direita).
 * @param arvore Ponteiro para a árvore
 * @param no Nó atual (começa pela raiz)
 */
void imprimirPreOrdem(arvoreRN *arvore, noRN *no);

/**
 * retornarRaiz
 * Retorna o nó raiz da árvore.
 * @param arvore Ponteiro para a árvore
 * @return Ponteiro para a raiz da árvore
 */
noRN *retornarRaiz(arvoreRN *arvore);

/**
 * rotacionarEsquerda
 * Realiza uma rotação para a esquerda em torno de um nó.
 * @param arvore Ponteiro para a árvore
 * @param no Nó em torno do qual será feita a rotação
 */
void rotacionarEsquerda(arvoreRN *arvore, noRN *no);

/**
 * rotacionarDireita
 * Realiza uma rotação para a direita em torno de um nó.
 * @param arvore Ponteiro para a árvore
 * @param no Nó em torno do qual será feita a rotação
 */
void rotacionarDireita(arvoreRN *arvore, noRN *no);

/**
 * balancearAposInsercao
 * Corrige o balanceamento após a inserção de um novo nó.
 * @param arvore Ponteiro para a árvore
 * @param novoNo Nó recém-inserido
 */
void balancearAposInsercao(arvoreRN *arvore, noRN *novoNo);

/**
 * balancearAposRemocao
 * Corrige o balanceamento após a remoção de um nó.
 * @param arvore Ponteiro para a árvore
 * @param noSucessor Nó que substituiu o nó removido
 * @param noPai Pai do nó substituído
 */
void balancearAposRemocao(arvoreRN *arvore, noRN *noSucessor, noRN *noPai);

/**
 * atualizarAlturaPreta
 * Atualiza recursivamente a altura preta dos nós.
 * @param arvore Ponteiro para a árvore
 * @param no Nó a partir do qual será atualizada a altura
 * @return Altura preta do nó
 */
int atualizarAlturaPreta(arvoreRN *arvore, noRN *no);

/**
 * atualizarAlturaPretaArvore
 * Atualiza a altura preta da árvore (altura da raiz).
 * @param arvore Ponteiro para a árvore
 */
void atualizarAlturaPretaArvore(arvoreRN *arvore);

/**
 * liberarArvoreRubroNegra
 * Libera toda a memória alocada pela árvore.
 * @param arvore Ponteiro para a árvore
 */
void liberarArvoreRubroNegra(arvoreRN *arvore);

// ==================== ASSINATURA DAS FUNÇÕES DA ÁRVORE B 2-3-4 ==================== //
/**
 * alocaArvoreB
 * Aloca e inicializa uma estrutura de árvore B (ordem 4).
 * @return Ponteiro para a árvore alocada, ou NULL em caso de falha.
 */
arvoreB *alocaArvoreB();

/**
 * alocaNoB
 * Aloca e inicializa um novo nó da árvore B.
 * @return Ponteiro para o nó alocado, ou NULL em caso de falha.
 */
noB *alocaNoB();

/**
 * inserirChave
 * Insere uma nova chave na árvore B.
 * @param arv Ponteiro para a árvore
 * @param valor Chave a ser inserida
 */
void inserirChave(int valor, arvoreB *arv);

/**
 * dividirFilho
 * Divide um filho cheio de um nó pai (conforme B-TREE-SPLIT-CHILD do Cormen).
 * @param pai Ponteiro para o nó pai
 * @param indiceFilho Índice do filho cheio no vetor de filhos do pai
 * @param arv Ponteiro para a árvore
 */
void dividirFilho(noB *pai, int indiceFilho, arvoreB *arv);

/**
 * inserirNaoCheio
 * Insere uma chave em um nó não cheio (conforme B-TREE-INSERT-NONFULL do Cormen).
 * @param no Ponteiro para o nó (não cheio)
 * @param valor Chave a ser inserida
 * @param arv Ponteiro para a árvore
 */
void inserirNaoCheio(noB *no, int valor, arvoreB *arv);

/**
 * removerChave
 * Remove uma chave da árvore B.
 * @param valor Chave a ser removida
 * @param arv Ponteiro para a árvore
 */
void removerChave(int valor, arvoreB *arv);

/**
 * buscarNo
 * Busca um nó que contém a chave especificada.
 * @param no Nó atual
 * @param valor Chave a ser buscada
 * @param indiceChave [saída] Índice da chave no nó, se encontrada
 * @return Ponteiro para o nó que contém a chave, ou NULL se não encontrada.
 */
noB *buscarNo(noB *no, int valor, int *indiceChave);

/**
 * removerChaveDoNo
 * Remove uma chave de um nó específico.
 * @param no Ponteiro para o nó
 * @param indiceChave Índice da chave no nó
 * @param arv Ponteiro para a árvore
 */
void removerChaveDoNo(noB *no, int indiceChave, arvoreB *arv);

/**
 * corrigirUnderflow
 * Corrige um nó que ficou com menos chaves que o mínimo (underflow).
 * @param no Ponteiro para o nó em underflow
 * @param arv Ponteiro para a árvore
 */
void corrigirUnderflow(noB *no, arvoreB *arv);

/**
 * fundirFilhos
 * Funde dois filhos de um nó pai (conforme operação de fusão do Cormen).
 * @param pai Ponteiro para o nó pai
 * @param indiceFilhoEsq Índice do filho esquerdo no vetor de filhos do pai
 * @param arv Ponteiro para a árvore
 */
void fundirFilhos(noB *pai, int indiceFilhoEsq, arvoreB *arv);

/**
 * getPredecessor
 * Obtém a maior chave na subárvore esquerda (predecessor).
 * @param no Nó de início
 * @return Predecessor (maior chave na subárvore esquerda)
 */
int getPredecessor(noB *no);

/**
 * getSucessor
 * Obtém a menor chave na subárvore direita (sucessor).
 * @param no Nó de início
 * @return Sucessor (menor chave na subárvore direita)
 */
int getSucessor(noB *no);

/**
 * imprimirArvore
 * Imprime a árvore B em pré-ordem (com detalhes dos nós).
 * @param arv Ponteiro para a árvore
 */
void imprimirArvore(arvoreB *arv);

/**
 * imprimirNo
 * Função auxiliar para imprimir um nó (recursivamente).
 * @param no Ponteiro para o nó
 */
void imprimirNo(noB *no);

/**
 * calcularAltura
 * Calcula recursivamente a altura de um nó na árvore B 2-3-4.
 * @param no Ponteiro para o nó a ser calculado
 * @return Altura da subárvore a partir do nó
 */
int calcularAltura(noB *no);

/**
 * contarBlocosCheios
 * Conta recursivamente os nós que estão totalmente ocupados (3 chaves).
 * @param no Ponteiro para o nó inicial da contagem
 * @return Quantidade de nós com 3 chaves na subárvore
 */
int contarBlocosCheios(noB *no);

/**
 * converterBparaRB
 * Converte uma árvore B 2-3-4 em uma árvore Rubro-Negra.
 * @param arvB Ponteiro para a árvore B
 * @return Ponteiro para a árvore Rubro-Negra resultante
 */
arvoreRN *converterBparaRB(arvoreB *arvB);

/**
 * liberarNoB
 * Libera recursivamente a memória de um nó da árvore B.
 * @param no Ponteiro para o nó
 */
void liberarNoB(noB *no);

/**
 * liberarArvoreB
 * Libera toda a memória da árvore B.
 * @param arv Ponteiro para a árvore
 */
void liberarArvoreB(arvoreB *arv);

// ==================== ASSINATURA DAS FUNÇÕES PARA ACESSAR AS ESTATÍSTICAS DA ÁRVORE B 2-3-4 ==================== //
/**
 * alturaArvoreB
 * Retorna a altura total da árvore B 2-3-4.
 * @param arv Ponteiro para a árvore
 * @return Altura total da árvore (0 se vazia)
 */
int alturaArvoreB(arvoreB *arv);

/**
 * obterContadorSplits
 * Retorna o número total de splits realizados durante inserções.
 * @param arv Ponteiro para a árvore
 * @return Quantidade total de splits
 */
int obterContadorSplits(arvoreB *arv);

/**
 * obterContadorRotacoes
 * Retorna o número total de rotações realizadas durante remoções.
 * @param arv Ponteiro para a árvore
 * @return Quantidade total de rotações
 */
int obterContadorRotacoes(arvoreB *arv);

/**
 * obterContadorMerges
 * Retorna o número total de merges realizados durante remoções.
 * @param arv Ponteiro para a árvore
 * @return Quantidade total de merges
 */
int obterContadorMerges(arvoreB *arv);

/**
 * obterBlocosCheios
 * Retorna o número total de nós com 3 chaves na árvore.
 * @param arv Ponteiro para a árvore
 * @return Quantidade de nós totalmente ocupados (3 chaves)
 */
int obterBlocosCheios(arvoreB *arv);

/**
 * resetarContadoresSplits
 * Zera o contador de splits da árvore B para permitir isolar estatísticas de operações individuais.
 * @param arv Ponteiro para a árvore
 */
void resetarContadorSplits(arvoreB *arv);

/**
 * resetarContadoresRemocao
 * Zera os contadores de rotações e merges da árvore para permitir isolar estatísticas de operações individuais.
 * @param arv Ponteiro para a árvore
 */
void resetarContadoresRemocao(arvoreB *arv);
// ==================== ASSINATURA DA FUNÇÃO AUXILIAR PARA GERAR ARQUIVO ==================== //
/**
 * gerarArquivoAleatorio
 * Gera um arquivo contendo valores inteiros aleatórios, um por linha.
 * @param nomeArquivo Nome do arquivo a ser criado (ex.: "entrada.txt")
 * @param quantidade Número de valores aleatórios a gerar
 */
void gerarArquivoAleatorio(const char *nomeArquivo, int quantidade);

// ==================== ASSINATURAS DAS FUNÇÕES UTILIZADAS NA REMOÇÃO EM LOTE ==================== //
/**
 * arvoreBContarChaves
 * Retorna o total de chaves na árvore.
 * @param arv Ponteiro para a árvore
 * @return Número total de chaves
 */
int arvoreBContarChaves(arvoreB *arv);

/**
 * arvoreB_coletarChaves
 * Coleta todas as chaves da árvore em um array.
 * @param arv Ponteiro para a árvore
 * @param n   Ponteiro para armazenar o número de chaves
 * @return Array de chaves (deve ser liberado pelo chamador)
 */
int *arvoreB_coletarChaves(arvoreB *arv, int *n);

/**
 * arvoreB_contarChaves
 * Retorna o total de chaves na árvore.
 * @param arv Ponteiro para a árvore
 * @return Número total de chaves
 */
int arvoreB_contarChaves(arvoreB *arv);

/**
 * arvoreB_coletarChaves
 * Coleta todas as chaves da árvore em um array.
 * @param arv Ponteiro para a árvore
 * @param n   Ponteiro para armazenar o número de chaves
 * @return Array de chaves (deve ser liberado pelo chamador)
 */
int *arvoreB_coletarChaves(arvoreB *arv, int *n);
#endif //TRABALHO_PRATICO_02_H
