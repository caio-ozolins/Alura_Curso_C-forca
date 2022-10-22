#include <stdio.h>
#include <string.h>

void cabecalho(){
    printf("|*****************|\n");
    printf("|* Jogo de Forca *|\n");
    printf("|*****************|\n\n");
}

void chuta(char chutes[26], int* tentativas){ //chute do jogador
    char chute;
    printf("Chute uma letra:");
    scanf(" %c", &chute);

    chutes[(*tentativas)] = chute;
    (*tentativas)++;
}

int jachutou(char letra, char chutes[26], int tentativas){
    int achou=0;
    for (int j = 0; j < tentativas; j++) {
        if (chutes[j] == letra){
            achou=1;
            break;
        }
    }
    return achou;
}

void desenhaForca(char palavraSecreta[20], char chutes[26], int tentativas){
    for (int i = 0; i < strlen(palavraSecreta); i++) {

        int achou = jachutou(palavraSecreta[i], chutes, tentativas);

        if(achou){
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void escolhePalavra(char palavraSecreta[20]){
    sprintf(palavraSecreta, "MELANCIA");
}

int main(){

    char palavraSecreta[20];
    int acertou=0, enforcou=0;
    char chutes[26];
    int tentativas=0;

    escolhePalavra(palavraSecreta);

    cabecalho();

    do {

        desenhaForca(palavraSecreta, chutes, tentativas);

        chuta(chutes, &tentativas);

    } while (!acertou && !enforcou);

    return 0;
}