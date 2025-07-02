/*
 *  Nome do Arquivo: main.c
 *  Autores: Cau� Teixeira Gomes Vieira - 2024009195
 *           Marcos Paulo Cyrillo da Silva - 2024015871
 *           Melissa Vit�ria dos Santos - 2024000313
 *  Data de Cria��o: 27/06/2025
 *  �ltima Modifica��o: 02/07/2025
 *  Descri��o: Programa principal para teste das opera��es de �rvore Rubro-Negra
 *            (inser��o, remo��o, impress�o e balanceamento).
 */

#ifndef TRABALHO_PRATICO_02_H
#define TRABALHO_PRATICO_02_H

// ==================== DEFINI��ES DE TIPO DA �RVORE RUBRO NEGRA ==================== //
typedef struct ArvoreRubroNegra arvoreRN;
typedef struct NoRubroNegro noRN;

// ==================== DEFINI��ES DE TIPO DA �RVORE B 2-3-4 ==================== //
typedef struct noB noB;
typedef struct arvoreB arvoreB;

// ==================== ASSINATURA DAS FUN��ES DA �RVORE RUBRO-NEGRA ==================== //
/**
 * alocaArvoreRubroNegra
 * Aloca e inicializa uma estrutura de �rvore rubro-negra.
 * @return Ponteiro para a �rvore alocada, ou NULL em caso de falha.
 */
arvoreRN *alocaArvoreRubroNegra();

/**
 * alocaNo
 * Aloca e inicializa um novo n� rubro-negro.
 * @param arvore Ponteiro para a �rvore
 * @param chave Valor a ser armazenado no n�
 * @return Ponteiro para o n� alocado, ou NULL em caso de falha
 */
noRN *alocaNo(arvoreRN *arvore, int chave);

/**
 * inserirNo
 * Insere um novo n� na �rvore rubro-negra.
 * @param arvore Ponteiro para a �rvore
 * @param novoNo Ponteiro para o n� a ser inserido
 */
void inserirNo(arvoreRN *arvore, noRN *novoNo);

/**
 * removerNo
 * Remove um n� da �rvore rubro-negra.
 * @param arvore Ponteiro para a �rvore
 * @param valor Chave do n� a ser removido
 * @return 1 se o n� foi removido, 0 caso contr�rio
 */
int removerNo(arvoreRN *arvore, int valor);

/**
 * imprimirPreOrdem
 * Imprime a �rvore em pr�-ordem (raiz-esquerda-direita).
 * @param arvore Ponteiro para a �rvore
 * @param no N� atual (come�a pela raiz)
 */
void imprimirPreOrdem(arvoreRN *arvore, noRN *no);

/**
 * retornarRaiz
 * Retorna o n� raiz da �rvore.
 * @param arvore Ponteiro para a �rvore
 * @return Ponteiro para a raiz da �rvore
 */
noRN *retornarRaiz(arvoreRN *arvore);

/**
 * rotacionarEsquerda
 * Realiza uma rota��o para a esquerda em torno de um n�.
 * @param arvore Ponteiro para a �rvore
 * @param no N� em torno do qual ser� feita a rota��o
 */
void rotacionarEsquerda(arvoreRN *arvore, noRN *no);

/**
 * rotacionarDireita
 * Realiza uma rota��o para a direita em torno de um n�.
 * @param arvore Ponteiro para a �rvore
 * @param no N� em torno do qual ser� feita a rota��o
 */
void rotacionarDireita(arvoreRN *arvore, noRN *no);

/**
 * balancearAposInsercao
 * Corrige o balanceamento ap�s a inser��o de um novo n�.
 * @param arvore Ponteiro para a �rvore
 * @param novoNo N� rec�m-inserido
 */
void balancearAposInsercao(arvoreRN *arvore, noRN *novoNo);

/**
 * balancearAposRemocao
 * Corrige o balanceamento ap�s a remo��o de um n�.
 * @param arvore Ponteiro para a �rvore
 * @param noSucessor N� que substituiu o n� removido
 * @param noPai Pai do n� substitu�do
 */
void balancearAposRemocao(arvoreRN *arvore, noRN *noSucessor, noRN *noPai);

/**
 * atualizarAlturaPreta
 * Atualiza recursivamente a altura preta dos n�s.
 * @param arvore Ponteiro para a �rvore
 * @param no N� a partir do qual ser� atualizada a altura
 * @return Altura preta do n�
 */
int atualizarAlturaPreta(arvoreRN *arvore, noRN *no);

/**
 * atualizarAlturaPretaArvore
 * Atualiza a altura preta da �rvore (altura da raiz).
 * @param arvore Ponteiro para a �rvore
 */
void atualizarAlturaPretaArvore(arvoreRN *arvore);

/**
 * liberarArvoreRubroNegra
 * Libera toda a mem�ria alocada pela �rvore.
 * @param arvore Ponteiro para a �rvore
 */
void liberarArvoreRubroNegra(arvoreRN *arvore);

// ==================== ASSINATURA DAS FUN��ES DA �RVORE B 2-3-4 ==================== //
/**
 * alocaArvoreB
 * Aloca e inicializa uma estrutura de �rvore B (ordem 4).
 * @return Ponteiro para a �rvore alocada, ou NULL em caso de falha.
 */
arvoreB *alocaArvoreB();

/**
 * alocaNoB
 * Aloca e inicializa um novo n� da �rvore B.
 * @return Ponteiro para o n� alocado, ou NULL em caso de falha.
 */
noB *alocaNoB();

/**
 * inserirChave
 * Insere uma nova chave na �rvore B.
 * @param arv Ponteiro para a �rvore
 * @param valor Chave a ser inserida
 */
void inserirChave(int valor, arvoreB *arv);

/**
 * dividirFilho
 * Divide um filho cheio de um n� pai (conforme B-TREE-SPLIT-CHILD do Cormen).
 * @param pai Ponteiro para o n� pai
 * @param indiceFilho �ndice do filho cheio no vetor de filhos do pai
 * @param arv Ponteiro para a �rvore
 */
void dividirFilho(noB *pai, int indiceFilho, arvoreB *arv);

/**
 * inserirNaoCheio
 * Insere uma chave em um n� n�o cheio (conforme B-TREE-INSERT-NONFULL do Cormen).
 * @param no Ponteiro para o n� (n�o cheio)
 * @param valor Chave a ser inserida
 * @param arv Ponteiro para a �rvore
 */
void inserirNaoCheio(noB *no, int valor, arvoreB *arv);

/**
 * removerChave
 * Remove uma chave da �rvore B.
 * @param valor Chave a ser removida
 * @param arv Ponteiro para a �rvore
 */
void removerChave(int valor, arvoreB *arv);

/**
 * buscarNo
 * Busca um n� que cont�m a chave especificada.
 * @param no N� atual
 * @param valor Chave a ser buscada
 * @param indiceChave [sa�da] �ndice da chave no n�, se encontrada
 * @return Ponteiro para o n� que cont�m a chave, ou NULL se n�o encontrada.
 */
noB *buscarNo(noB *no, int valor, int *indiceChave);

/**
 * removerChaveDoNo
 * Remove uma chave de um n� espec�fico.
 * @param no Ponteiro para o n�
 * @param indiceChave �ndice da chave no n�
 * @param arv Ponteiro para a �rvore
 */
void removerChaveDoNo(noB *no, int indiceChave, arvoreB *arv);

/**
 * corrigirUnderflow
 * Corrige um n� que ficou com menos chaves que o m�nimo (underflow).
 * @param no Ponteiro para o n� em underflow
 * @param arv Ponteiro para a �rvore
 */
void corrigirUnderflow(noB *no, arvoreB *arv);

/**
 * fundirFilhos
 * Funde dois filhos de um n� pai (conforme opera��o de fus�o do Cormen).
 * @param pai Ponteiro para o n� pai
 * @param indiceFilhoEsq �ndice do filho esquerdo no vetor de filhos do pai
 * @param arv Ponteiro para a �rvore
 */
void fundirFilhos(noB *pai, int indiceFilhoEsq, arvoreB *arv);

/**
 * getPredecessor
 * Obt�m a maior chave na sub�rvore esquerda (predecessor).
 * @param no N� de in�cio
 * @return Predecessor (maior chave na sub�rvore esquerda)
 */
int getPredecessor(noB *no);

/**
 * getSucessor
 * Obt�m a menor chave na sub�rvore direita (sucessor).
 * @param no N� de in�cio
 * @return Sucessor (menor chave na sub�rvore direita)
 */
int getSucessor(noB *no);

/**
 * imprimirArvore
 * Imprime a �rvore B em pr�-ordem (com detalhes dos n�s).
 * @param arv Ponteiro para a �rvore
 */
void imprimirArvore(arvoreB *arv);

/**
 * imprimirNo
 * Fun��o auxiliar para imprimir um n� (recursivamente).
 * @param no Ponteiro para o n�
 */
void imprimirNo(noB *no);

/**
 * calcularAltura
 * Calcula recursivamente a altura de um n� na �rvore B 2-3-4.
 * @param no Ponteiro para o n� a ser calculado
 * @return Altura da sub�rvore a partir do n�
 */
int calcularAltura(noB *no);

/**
 * contarBlocosCheios
 * Conta recursivamente os n�s que est�o totalmente ocupados (3 chaves).
 * @param no Ponteiro para o n� inicial da contagem
 * @return Quantidade de n�s com 3 chaves na sub�rvore
 */
int contarBlocosCheios(noB *no);

/**
 * converterBparaRB
 * Converte uma �rvore B 2-3-4 em uma �rvore Rubro-Negra.
 * @param arvB Ponteiro para a �rvore B
 * @return Ponteiro para a �rvore Rubro-Negra resultante
 */
arvoreRN *converterBparaRB(arvoreB *arvB);

/**
 * liberarNoB
 * Libera recursivamente a mem�ria de um n� da �rvore B.
 * @param no Ponteiro para o n�
 */
void liberarNoB(noB *no);

/**
 * liberarArvoreB
 * Libera toda a mem�ria da �rvore B.
 * @param arv Ponteiro para a �rvore
 */
void liberarArvoreB(arvoreB *arv);

// ==================== ASSINATURA DAS FUN��ES PARA ACESSAR AS ESTAT�STICAS DA �RVORE B 2-3-4 ==================== //
/**
 * alturaArvoreB
 * Retorna a altura total da �rvore B 2-3-4.
 * @param arv Ponteiro para a �rvore
 * @return Altura total da �rvore (0 se vazia)
 */
int alturaArvoreB(arvoreB *arv);

/**
 * obterContadorSplits
 * Retorna o n�mero total de splits realizados durante inser��es.
 * @param arv Ponteiro para a �rvore
 * @return Quantidade total de splits
 */
int obterContadorSplits(arvoreB *arv);

/**
 * obterContadorRotacoes
 * Retorna o n�mero total de rota��es realizadas durante remo��es.
 * @param arv Ponteiro para a �rvore
 * @return Quantidade total de rota��es
 */
int obterContadorRotacoes(arvoreB *arv);

/**
 * obterContadorMerges
 * Retorna o n�mero total de merges realizados durante remo��es.
 * @param arv Ponteiro para a �rvore
 * @return Quantidade total de merges
 */
int obterContadorMerges(arvoreB *arv);

/**
 * obterBlocosCheios
 * Retorna o n�mero total de n�s com 3 chaves na �rvore.
 * @param arv Ponteiro para a �rvore
 * @return Quantidade de n�s totalmente ocupados (3 chaves)
 */
int obterBlocosCheios(arvoreB *arv);

/**
 * resetarContadoresSplits
 * Zera o contador de splits da �rvore B para permitir isolar estat�sticas de opera��es individuais.
 * @param arv Ponteiro para a �rvore
 */
void resetarContadorSplits(arvoreB *arv);

/**
 * resetarContadoresRemocao
 * Zera os contadores de rota��es e merges da �rvore para permitir isolar estat�sticas de opera��es individuais.
 * @param arv Ponteiro para a �rvore
 */
void resetarContadoresRemocao(arvoreB *arv);
// ==================== ASSINATURA DA FUN��O AUXILIAR PARA GERAR ARQUIVO ==================== //
/**
 * gerarArquivoAleatorio
 * Gera um arquivo contendo valores inteiros aleat�rios, um por linha.
 * @param nomeArquivo Nome do arquivo a ser criado (ex.: "entrada.txt")
 * @param quantidade N�mero de valores aleat�rios a gerar
 */
void gerarArquivoAleatorio(const char *nomeArquivo, int quantidade);

// ==================== ASSINATURAS DAS FUN��ES UTILIZADAS NA REMO��O EM LOTE ==================== //
/**
 * arvoreBContarChaves
 * Retorna o total de chaves na �rvore.
 * @param arv Ponteiro para a �rvore
 * @return N�mero total de chaves
 */
int arvoreBContarChaves(arvoreB *arv);

/**
 * arvoreB_coletarChaves
 * Coleta todas as chaves da �rvore em um array.
 * @param arv Ponteiro para a �rvore
 * @param n   Ponteiro para armazenar o n�mero de chaves
 * @return Array de chaves (deve ser liberado pelo chamador)
 */
int *arvoreB_coletarChaves(arvoreB *arv, int *n);

/**
 * arvoreB_contarChaves
 * Retorna o total de chaves na �rvore.
 * @param arv Ponteiro para a �rvore
 * @return N�mero total de chaves
 */
int arvoreB_contarChaves(arvoreB *arv);

/**
 * arvoreB_coletarChaves
 * Coleta todas as chaves da �rvore em um array.
 * @param arv Ponteiro para a �rvore
 * @param n   Ponteiro para armazenar o n�mero de chaves
 * @return Array de chaves (deve ser liberado pelo chamador)
 */
int *arvoreB_coletarChaves(arvoreB *arv, int *n);
#endif //TRABALHO_PRATICO_02_H
