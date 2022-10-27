#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

// variaveis globais
char palavraSecreta[TAMANHO_PALAVRA];
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

    int erros = chutesErrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >=1 ? '(' : ' '), (erros >=1 ? '_' : ' '), (erros >=1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >=3 ? '\\' : ' '), (erros >=2 ? '|' : ' '), (erros >=3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >=2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >=4 ? '/' : ' '), (erros >=4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

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

        char novaPalavra[TAMANHO_PALAVRA];
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

int chutesErrados(){
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
    return erros;
}

int enforcou(){ // verifica se o jogador foi "enforcado"
    return chutesErrados() >= 4;
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

    if (acertou()){
        printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavraSecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    return 0;
}