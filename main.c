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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trabalho_pratico_02.h"

// Função para embaralhar um array (Fisher-Yates)
static void shuffle(int *array, int n) {
    if (array == NULL || n <= 1) return;
    srand((unsigned int)time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i+1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main(void) {
    arvoreB *arvB = alocaArvoreB();
    if (!arvB) {
        fprintf(stderr, "Falha ao alocar Arvore B\n");
        return EXIT_FAILURE;
    }

    arvoreRN *arvoreRN = NULL;
    int valor, opcao, metodo;

    // Tempos de execução e estatísticas
    clock_t tempoInsercaoB = 0, tempoRemocaoB = 0;
    clock_t tempoInsercaoRN = 0, tempoRemocaoRN = 0;
    clock_t tempoConversaoBparaRN = 0;

    // Variáveis para estatísticas
    int splits_total = 0, altura_atual = 0, blocos_cheios_atual = 0;
    int splits_individual = 0; // Para inserções individuais

    printf("MENU INICIAL:\n");
    printf("1. Gerar arquivo aleatorio automaticamente e carregar a arvore\n");
    printf("2. Carregar arvore a partir de um arquivo existente\n");
    printf("3. Inserir valores manualmente\n");
    printf("Escolha: ");
    scanf("%d", &metodo);

    if (metodo == 1) {
        const char *ARQ_ENTRADA = "entrada.txt";
        const int QTDE_VALORES = 1000;
        gerarArquivoAleatorio(ARQ_ENTRADA, QTDE_VALORES);
        printf("Arquivo '%s' gerado com %d valores aleatorios.\n", ARQ_ENTRADA, QTDE_VALORES);

        FILE *arq = fopen(ARQ_ENTRADA, "r");
        if (!arq) {
            perror("Erro ao abrir arquivo");
            return EXIT_FAILURE;
        }

        clock_t ini = clock();
        while (fscanf(arq, "%d", &valor) == 1) {
            inserirChave(valor, arvB);
        }
        clock_t fim = clock();
        tempoInsercaoB = fim - ini;
        fclose(arq);

        // Estatísticas totais para inserção em lote
        splits_total = obterContadorSplits(arvB);
        altura_atual = alturaArvoreB(arvB);
        blocos_cheios_atual = obterBlocosCheios(arvB);

        printf("\n=== ESTATISTICAS POS-INSERCAO (LOTE) ===\n");
        printf("Splits utilizados: %d\n", splits_total);
        printf("Altura da arvore: %d\n", altura_atual);
        printf("Blocos totalmente ocupados: %d\n", blocos_cheios_atual);
        printf("=========================================\n");

    } else if (metodo == 2) {
        char nomeArquivo[100];
        printf("Digite o nome do arquivo: ");
        scanf("%s", nomeArquivo);

        FILE *arq = fopen(nomeArquivo, "r");
        if (!arq) {
            perror("Erro ao abrir arquivo");
            return EXIT_FAILURE;
        }

        clock_t ini = clock();
        while (fscanf(arq, "%d", &valor) == 1) {
            inserirChave(valor, arvB);
        }
        clock_t fim = clock();
        tempoInsercaoB = fim - ini;
        fclose(arq);

        // Estatísticas totais para inserção em lote
        splits_total = obterContadorSplits(arvB);
        altura_atual = alturaArvoreB(arvB);
        blocos_cheios_atual = obterBlocosCheios(arvB);

        printf("\n=== ESTATISTICAS POS-INSERCAO (LOTE) ===\n");
        printf("Splits utilizados: %d\n", splits_total);
        printf("Altura da arvore: %d\n", altura_atual);
        printf("Blocos totalmente ocupados: %d\n", blocos_cheios_atual);
        printf("=========================================\n");

    } else if (metodo == 3) {
        printf("Digite valores para inserir na arvore 2-3-4. Digite -1 para parar.\n");
        while (1) {
            printf("Valor: ");
            if (scanf("%d", &valor) != 1) {
                printf("Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n')
                continue;
            }
            if (valor == -1) break;
            clock_t ini = clock();
            inserirChave(valor, arvB);
            clock_t fim = clock();
            tempoInsercaoB += fim - ini;
        }

        // Estatísticas totais para inserção manual em lote
        splits_total = obterContadorSplits(arvB);
        altura_atual = alturaArvoreB(arvB);
        blocos_cheios_atual = obterBlocosCheios(arvB);

        printf("\n=== ESTATISTICAS POS-INSERCAO (LOTE) ===\n");
        printf("Splits utilizados: %d\n", splits_total);
        printf("Altura da arvore: %d\n", altura_atual);
        printf("Blocos totalmente ocupados: %d\n", blocos_cheios_atual);
        printf("=========================================\n");
    } else {
        printf("Opcao invalida!\n");
        liberarArvoreB(arvB);
        return EXIT_FAILURE;
    }

    printf("\nArvore 2-3-4 gerada:\n");
    imprimirArvore(arvB);

    do {
        printf("\nArvores Balanceadas : Menu\n");
        if (arvoreRN == NULL) {
            printf("1. Inserir novo elemento na arvore 2-3-4\n");
            printf("2. Remover elemento da arvore 2-3-4\n");
            printf("3. Imprimir arvore 2-3-4\n");
            printf("4. Converter em uma arvore rubro-negra\n");
            printf("5. Remover uma porcentagem de chaves em lote\n");
            printf("6. Sair\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o valor a ser inserido: ");
                    scanf("%d", &valor);
                    {
                        // Resetar apenas para esta operação individual
                        resetarContadorSplits(arvB);

                        clock_t ini = clock();
                        inserirChave(valor, arvB);
                        clock_t fim = clock();
                        tempoInsercaoB += fim - ini;

                        // Estatísticas específicas desta inserção
                        splits_individual = obterContadorSplits(arvB);
                        altura_atual = alturaArvoreB(arvB);
                        blocos_cheios_atual = obterBlocosCheios(arvB);

                        printf("\n=== ESTATISTICAS POS-INSERCAO (INDIVIDUAL) ===\n");
                        printf("Splits desta insercao: %d\n", splits_individual);
                        printf("Altura da arvore: %d\n", altura_atual);
                        printf("Blocos totalmente ocupados: %d\n", blocos_cheios_atual);
                        printf("==============================================\n");
                    }
                    break;
                case 2:
                    printf("Digite o valor a ser removido: ");
                    scanf("%d", &valor);
                    {
                        // Resetar contadores de remoção
                        resetarContadoresRemocao(arvB);

                        clock_t ini = clock();
                        removerChave(valor, arvB);
                        clock_t fim = clock();
                        tempoRemocaoB += fim - ini;

                        // Estatísticas específicas desta remoção
                        int rotacoes = obterContadorRotacoes(arvB);
                        int merges = obterContadorMerges(arvB);
                        altura_atual = alturaArvoreB(arvB);
                        blocos_cheios_atual = obterBlocosCheios(arvB);

                        printf("\n=== ESTATISTICAS POS-REMOCAO ===\n");
                        printf("Rotacoes: %d\n", rotacoes);
                        printf("Merges: %d\n", merges);
                        printf("Altura da arvore: %d\n", altura_atual);
                        printf("Blocos totalmente ocupados: %d\n", blocos_cheios_atual);
                        printf("===============================\n");
                    }
                    break;
                case 3:
                    imprimirArvore(arvB);
                    break;
                case 4:
                    {
                        clock_t ini = clock();
                        arvoreRN = converterBparaRB(arvB);
                        clock_t fim = clock();
                        tempoConversaoBparaRN = fim - ini;

                        printf("\nArvore convertida para rubro-negra:\n");
                        imprimirPreOrdem(arvoreRN, retornarRaiz(arvoreRN));
                    }
                    break;
            case 5: {
                    int porcentagem;
                    printf("Digite a porcentagem de chaves a remover (0-100): ");
                    scanf("%d", &porcentagem);

                    if (porcentagem < 0 || porcentagem > 100) {
                        printf("Porcentagem invalida!\n");
                        break;
                    }

                    int totalChaves;
                    int *todas_chaves = arvoreB_coletarChaves(arvB, &totalChaves);
                    if (todas_chaves == NULL || totalChaves == 0) {
                        printf("A arvore esta vazia ou erro de alocacao!\n");
                        if (todas_chaves) free(todas_chaves);
                        break;
                    }

                    // Embaralhar as chaves para seleção aleatória
                    shuffle(todas_chaves, totalChaves);

                    int n_remover = (porcentagem * totalChaves) / 100;
                    if (n_remover <= 0) {
                        printf("Nenhuma chave a remover.\n");
                        free(todas_chaves);
                        break;
                    }

                    // Resetar contadores para a operação em lote
                    resetarContadoresRemocao(arvB);

                    clock_t ini_lote = clock();
                    for (int i = 0; i < n_remover; i++) {
                        removerChave(todas_chaves[i], arvB);
                    }
                    clock_t fim_lote = clock();
                    tempoRemocaoB += fim_lote - ini_lote;

                    int rotacoes_lote = obterContadorRotacoes(arvB);
                    int merges_lote = obterContadorMerges(arvB);
                    altura_atual = alturaArvoreB(arvB);
                    blocos_cheios_atual = obterBlocosCheios(arvB);

                    printf("\n=== ESTATISTICAS REMOCAO EM LOTE (%d%%) ===\n", porcentagem);
                    printf("Chaves removidas: %d\n", n_remover);
                    printf("Tempo de remocao: %.6f s\n", (double)(fim_lote - ini_lote) / CLOCKS_PER_SEC);
                    printf("Rotacoes: %d\n", rotacoes_lote);
                    printf("Merges: %d\n", merges_lote);
                    printf("Altura da arvore: %d\n", altura_atual);
                    printf("Blocos totalmente ocupados: %d\n", blocos_cheios_atual);
                    printf("==========================================\n");

                    free(todas_chaves);
                    break;
            }
                case 6:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        } else {
            printf("\nArvores Balanceadas : Menu (Rubro-Negra)\n");
            printf("1. Inserir novo elemento na arvore rubro-negra\n");
            printf("2. Remover elemento na arvore rubro-negra\n");
            printf("3. Imprimir arvore rubro-negra\n");
            printf("4. Voltar ao menu da arvore 2-3-4\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o valor a ser inserido: ");
                    scanf("%d", &valor);
                    {
                        clock_t ini = clock();
                        noRN *novoNo = alocaNo(arvoreRN, valor);
                        inserirNo(arvoreRN, novoNo);
                        clock_t fim = clock();
                        tempoInsercaoRN += fim - ini;

                        printf("Arvore apos insercao:\n");
                        imprimirPreOrdem(arvoreRN, retornarRaiz(arvoreRN));
                    }
                    break;
                case 2:
                    printf("Digite o valor a ser removido: ");
                    scanf("%d", &valor);
                    {
                        clock_t ini = clock();
                        removerNo(arvoreRN, valor);
                        clock_t fim = clock();
                        tempoRemocaoRN += fim - ini;
                    }
                    break;
                case 3:
                    imprimirPreOrdem(arvoreRN, retornarRaiz(arvoreRN));
                    break;
                case 4:
                    liberarArvoreRubroNegra(arvoreRN);
                    arvoreRN = NULL;
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        }
    } while (opcao != 6);

    // Mostra tempos acumulados
    printf("\n================= RELATORIO DE TEMPOS =================\n");
    printf("Insercao na Arvore 2-3-4             : %.6f s\n", (double)tempoInsercaoB/ CLOCKS_PER_SEC);
    printf("Remocao na Arvore 2-3-4              : %.6f s\n", (double)tempoRemocaoB/ CLOCKS_PER_SEC);
    printf("Conversao de B 2-3-4 para Rubro-Negra: %.6f s\n", (double)tempoConversaoBparaRN/ CLOCKS_PER_SEC);
    printf("Insercao na Arvore Rubro-Negra       : %.6f s\n", (double)tempoInsercaoRN/ CLOCKS_PER_SEC);
    printf("Remocao na Arvore Rubro-Negra        : %.6f s\n", (double)tempoRemocaoRN/ CLOCKS_PER_SEC);
    printf("=======================================================\n");

    liberarArvoreB(arvB);
    return EXIT_SUCCESS;
}





/*
int main(void) {
    arvoreB *arvB = alocaArvoreB();
    if (!arvB) {
        fprintf(stderr, "Falha ao alocar Arvore B\n");
        return EXIT_FAILURE;
    }

    arvoreRN *arvoreRN = NULL;
    int valor, opcao, metodo;

    // Tempos de execução
    clock_t tempoInsercaoB = 0, tempoRemocaoB = 0;
    clock_t tempoInsercaoRN = 0, tempoRemocaoRN = 0;
    clock_t tempoConversaoBparaRN = 0;

    printf("MENU INICIAL:\n");
    printf("1. Gerar arquivo aleatorio automaticamente e carregar a arvore\n");
    printf("2. Carregar arvore a partir de um arquivo existente\n");
    printf("3. Inserir valores manualmente\n");
    printf("Escolha: ");
    scanf("%d", &metodo);

    if (metodo == 1) {
        const char *ARQ_ENTRADA = "entrada.txt";
        const int QTDE_VALORES = 1000;
        gerarArquivoAleatorio(ARQ_ENTRADA, QTDE_VALORES);
        printf("Arquivo '%s' gerado com %d valores aleatorios.\n", ARQ_ENTRADA, QTDE_VALORES);

        FILE *arq = fopen(ARQ_ENTRADA, "r");
        if (!arq) {
            perror("Erro ao abrir arquivo");
            return EXIT_FAILURE;
        }

        clock_t ini = clock();
        while (fscanf(arq, "%d", &valor) == 1) {
            inserirChave(valor, arvB);
        }
        clock_t fim = clock();
        tempoInsercaoB = fim - ini;
        fclose(arq);

    } else if (metodo == 2) {
        char nomeArquivo[100];
        printf("Digite o nome do arquivo: ");
        scanf("%s", nomeArquivo);

        FILE *arq = fopen(nomeArquivo, "r");
        if (!arq) {
            perror("Erro ao abrir arquivo");
            return EXIT_FAILURE;
        }

        clock_t ini = clock();
        while (fscanf(arq, "%d", &valor) == 1) {
            inserirChave(valor, arvB);
        }
        clock_t fim = clock();
        tempoInsercaoB = fim - ini;
        fclose(arq);

    } else if (metodo == 3) {
        printf("Digite valores para inserir na arvore 2-3-4. Digite -1 para parar.\n");
        while (1) {
            printf("Valor: ");
            if (scanf("%d", &valor) != 1) {
                printf("Entrada invalida. Tente novamente.\n");
                while (getchar() != '\n')
                continue;
            }
            if (valor == -1) break;
            clock_t ini = clock();
            inserirChave(valor, arvB);
            clock_t fim = clock();
            tempoInsercaoB += fim - ini;
        }
    } else {
        printf("Opcao invalida!\n");
        liberarArvoreB(arvB);
        return EXIT_FAILURE;
    }

    printf("\nArvore 2-3-4 gerada:\n");
    imprimirArvore(arvB);

    do {
        printf("\nArvores Balanceadas : Menu\n");
        if (arvoreRN == NULL) {
            printf("1. Inserir novo elemento na arvore 2-3-4\n");
            printf("2. Remover elemento da arvore 2-3-4\n");
            printf("3. Imprimir arvore 2-3-4\n");
            printf("4. Converter em uma arvore rubro-negra\n");
            printf("5. Sair\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o valor a ser inserido: ");
                    scanf("%d", &valor);
                    {
                        clock_t ini = clock();
                        inserirChave(valor, arvB);
                        clock_t fim = clock();
                        tempoInsercaoB += fim - ini;
                    }
                    break;
                case 2:
                    printf("Digite o valor a ser removido: ");
                    scanf("%d", &valor);
                    {
                        clock_t ini = clock();
                        removerChave(valor, arvB);
                        clock_t fim = clock();
                        tempoRemocaoB += fim - ini;
                    }
                    break;
                case 3:
                    imprimirArvore(arvB);
                    break;
                case 4:
                    {
                        clock_t ini = clock();
                        arvoreRN = converterBparaRB(arvB);
                        clock_t fim = clock();
                        tempoConversaoBparaRN = fim - ini;

                        printf("\nArvore convertida para rubro-negra:\n");
                        imprimirPreOrdem(arvoreRN, retornarRaiz(arvoreRN));
                    }
                    break;
                case 5:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        } else {
            printf("\nArvores Balanceadas : Menu (Rubro-Negra)\n");
            printf("1. Inserir novo elemento na arvore rubro-negra\n");
            printf("2. Remover elemento na arvore rubro-negra\n");
            printf("3. Imprimir arvore rubro-negra\n");
            printf("4. Voltar ao menu da arvore 2-3-4\n");
            printf("Escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o valor a ser inserido: ");
                    scanf("%d", &valor);
                    {
                        clock_t ini = clock();
                        noRN *novoNo = alocaNo(arvoreRN, valor);
                        inserirNo(arvoreRN, novoNo);
                        clock_t fim = clock();
                        tempoInsercaoRN += fim - ini;

                        printf("Arvore apos insercao:\n");
                        imprimirPreOrdem(arvoreRN, retornarRaiz(arvoreRN));
                    }
                    break;
                case 2:
                    printf("Digite o valor a ser removido: ");
                    scanf("%d", &valor);
                    {
                        clock_t ini = clock();
                        removerNo(arvoreRN, valor);
                        clock_t fim = clock();
                        tempoRemocaoRN += fim - ini;
                    }
                    break;
                case 3:
                    imprimirPreOrdem(arvoreRN, retornarRaiz(arvoreRN));
                    break;
                case 4:
                    liberarArvoreRubroNegra(arvoreRN);
                    arvoreRN = NULL;
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        }
    } while (opcao != 5);

    // Mostra tempos acumulados
    printf("\n================= RELATORIO DE TEMPOS =================\n");
    printf("Insercao na Arvore 2-3-4             : %.6f s\n", (double)tempoInsercaoB/ CLOCKS_PER_SEC);
    printf("Remocao na Arvore 2-3-4              : %.6f s\n", (double)tempoRemocaoB/ CLOCKS_PER_SEC);
    printf("Conversao de B 2-3-4 para Rubro-Negra: %.6f s\n", (double)tempoConversaoBparaRN/ CLOCKS_PER_SEC);
    printf("Insercao na Arvore Rubro-Negra       : %.6f s\n", (double)tempoInsercaoRN/ CLOCKS_PER_SEC);
    printf("Remocao na Arvore Rubro-Negra        : %.6f s\n", (double)tempoRemocaoRN/ CLOCKS_PER_SEC);
    printf("=======================================================\n");

    liberarArvoreB(arvB);
    return EXIT_SUCCESS;
}
*/