//Estruturas de controle (loops e condicionais) para a lógica do jogo.
//Funções modularizadas para organização do código.
//Structs para manipulação de palavras e estatísticas.
//Manipulação de arquivos para armazenar palavras e resultados anteriores.
//Menu interativo para a experiência do usuário.

//implementação do jogo "Termo" em C, seguindo os requisitos do trabalho prático. 
//Ele carrega palavras de um arquivo, escolhe uma aleatoriamente e permite até 6 tentativas para adivinhar.

// "()" -> Letra correta em local errado.
// "[]" -> Letra correta em local correto.

//Alunos: Douglas Lima Menezes (552590)
//Carol Lima Fonseca (567179)
//Francisco Wandallis (553083)
//Mateus de Oliveira Trajano (540020)
//Jânio Cayo Borges Lima (519325)
//Fransico Kaue Borges Bezerra (553878)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PALAVRA 6
#define MAX_TENTATIVAS 6
#define ARQUIVO_PALAVRAS "palavras.txt"
#define ARQUIVO_PONTUACAO "pontuacao.txt"

typedef struct {
    char palavra[MAX_PALAVRA];
} Palavra;

void carregarPalavras(Palavra palavras[], int *quantidade);
void escolherPalavra(Palavra palavras[], int quantidade, char palavraEscolhida[]);
void jogar(char palavraSecreta[], int *pontuacao);
void mostrarResultado(char tentativa[], char palavraSecreta[]);
void salvarPontuacao(int pontuacao);

int main() {
    Palavra palavras[100];
    int quantidade = 0;
    char palavraSecreta[MAX_PALAVRA];
    int pontuacao = 0;

    carregarPalavras(palavras, &quantidade);
    escolherPalavra(palavras, quantidade, palavraSecreta);

    printf("Bem-vindo ao Termo!\n\n");
    jogar(palavraSecreta, &pontuacao);
    salvarPontuacao(pontuacao);

    return 0;
}

void carregarPalavras(Palavra palavras[], int *quantidade) {
    FILE *arquivo = fopen(ARQUIVO_PALAVRAS, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo das palavras.\n");
        exit(1);
    }
    while (fscanf(arquivo, "%s", palavras[*quantidade].palavra) != EOF) {
        (*quantidade)++;
    }
    fclose(arquivo);
}

void escolherPalavra(Palavra palavras[], int quantidade, char palavraEscolhida[]) {
    srand(time(NULL));
    int indice = rand() % quantidade;
    strcpy(palavraEscolhida, palavras[indice].palavra);
}

void jogar(char palavraSecreta[], int *pontuacao) {
    char tentativa[MAX_PALAVRA];
    int tentativas = 0;

    while (tentativas < MAX_TENTATIVAS) {
        printf("Tentativa %d/%d: ", tentativas + 1, MAX_TENTATIVAS);
        scanf("%s", tentativa);
        
        if (strcmp(tentativa, palavraSecreta) == 0) {
            printf("Parabéns! Você acertou a palavra!\n");
            *pontuacao += (MAX_TENTATIVAS - tentativas) * 10;
            return;
        }
        
        mostrarResultado(tentativa, palavraSecreta);
        tentativas++;
    }
    printf("Você perdeu! A palavra era: %s\n", palavraSecreta);
}

void mostrarResultado(char tentativa[], char palavraSecreta[]) {
    for (int i = 0; i < MAX_PALAVRA - 1; i++) {
        if (tentativa[i] == palavraSecreta[i]) {
            printf("[%c] ", tentativa[i]);
        } else if (strchr(palavraSecreta, tentativa[i])) {
            printf("(%c) ", tentativa[i]);
        } else {
            printf(" %c  ", tentativa[i]);
        }
    }
    printf("\n");
}

void salvarPontuacao(int pontuacao) {
    FILE *arquivo = fopen(ARQUIVO_PONTUACAO, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de pontuação.\n");
        return;
    }
    fprintf(arquivo, "Pontuação: %d\n", pontuacao);
    fclose(arquivo);
}
