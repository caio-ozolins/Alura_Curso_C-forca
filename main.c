#include <stdio.h>
#include <string.h>
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

void escolhePalavra(){ // escolhe a palavra secreta
    sprintf(palavraSecreta, "MELANCIA");
}

int enforcou(){ // verifica se o jogador foi "enforcado"
    int erros=0;
    for (int i = 0; i < chutesDados; ++i) {
        int existe = 0;
        for (int j = 0; j < strlen(palavraSecreta); ++j) {
            //if (chutes[i] == palavraSecreta[j]){
            if (jaChutou(palavraSecreta[i])){
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

    return 0;
}