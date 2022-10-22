#include <stdio.h>
#include <string.h>

// variaveis globais
char palavraSecreta[20];
char chutes[26];
int tentativas=0;

void cabecalho(){ // imprime o cabeçalho
    printf("|*****************|\n");
    printf("|* Jogo de Forca *|\n");
    printf("|*****************|\n\n");
}

void chuta(){ //chute do jogador
    char chute;
    printf("Chute uma letra:");
    scanf(" %c", &chute);

    chutes[tentativas] = chute;
    tentativas++;
}

int jaChutou(char letra){ // verifica se a letra já foi chutada
    int achou=0;
    for (int j = 0; j < tentativas; j++) {
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

int enforcou(){
    int erros=0;
    for (int i = 0; i < tentativas; ++i) {
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

int main(){

    int acertou=0;

    escolhePalavra();
    cabecalho();

    do {

        desenhaForca();
        chuta();

    } while (!acertou && !enforcou());

    return 0;
}