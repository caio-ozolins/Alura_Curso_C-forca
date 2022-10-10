#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char palavraSecreta[20];

    sprintf(palavraSecreta, "MELANCIA");

    int acertou=0, enforcou=0;

    do {
        char chute;
        printf("Chute uma letra:");
        scanf("%c", &chute);

        for (int i = 0; i < strlen(palavraSecreta); i++) {
            if (palavraSecreta[i] == chute){
            printf("A posição %d tem essa letra\n", i);
            }
        }

    } while (!acertou && !enforcou);

    return 0;
}