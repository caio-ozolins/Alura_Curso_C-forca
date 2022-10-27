#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

// variaveis globais
char palavraSecreta[20];
char chutes[26];
int chutesDados=0;

void cabecalho(){ // imprime o cabeçalho
    printf("|*****************|\n");
    printf("|* Jogo de Forca *|\n");
    printf("|*****************|\n\n");
}

void chuta(){ //chute do jogador
    char chute;
    printf("Chute uma letra:");
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra){ // verifica se a letra já foi chutada
    int achou=0;
    for (int j = 0; j < chutesDados; j++) {
        if (chutes[j] == letra){
            achou=1;
            break;
        }
    }
    return achou;
}

void desenhaForca(){ // imprime a palavra secreta
    for (int i = 0; i < strlen(palavraSecreta); i++) {

        int achou = jaChutou(palavraSecreta[i]);

        if(achou){
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void adicionaPalavra(){
    char quer;

    printf("Voce deseja asicionar uma nova palavra? (S/N)");
    scanf(" %c", &quer);

    if (quer =='S'){

        char novaPalavra[20];
        printf("Qual a nova palavra?");
        scanf("%s", novaPalavra);

        FILE* f;

        f = fopen("..\\palavras.txt", "r+");

        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);

        fprintf(f, "\n%s", novaPalavra);

        fclose(f);
    }
}

void escolhePalavra(){ // escolhe a palavra secreta
    FILE * f;
    f = fopen("..\\palavras.txt", "r");

    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtdPalavras;

    fscanf(f, "%d", &qtdPalavras);

    srand(time(0));
    int numRand = rand() % qtdPalavras;

    for (int i = 0; i <= numRand; i++) {
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

int enforcou(){ // verifica se o jogador foi "enforcado"
    int erros=0;
    for (int i = 0; i < chutesDados; ++i) {
        int existe = 0;
        for (int j = 0; j < strlen(palavraSecreta); ++j) {
            if (chutes[i] == palavraSecreta[j]){
                existe = 1;
                break;
            }
        }
        if (!existe){erros++;}
    }
    return erros >= 5;
}

int acertou(){
    for (int i = 0; i < strlen(palavraSecreta); ++i) {
        if (!jaChutou(palavraSecreta[i])){
            return 0;
        }
    }
    return 1;
}

int main(){

    escolhePalavra();
    cabecalho();

    do {

        desenhaForca();
        chuta();

    } while (!acertou() && !enforcou());

    adicionaPalavra();

    return 0;
}