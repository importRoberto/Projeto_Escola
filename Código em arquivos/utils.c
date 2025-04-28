#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

void ToUpperStr(char destino[], const char origem[]) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = toupper(origem[i]);
        i++;
    }
    destino[i] = '\0';
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void PreencherDadosComuns(char nome[], int *matricula, char dataNascimento[], char *sexo, char cpf[]) {
    printf("Nome: ");
    while (getchar() != '\n'); // consome qualquer coisa no buffer
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Matrícula: ");
    scanf("%d", matricula);

    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", dataNascimento);

    printf("Sexo (M/F): ");
    scanf(" %c", sexo); 

    printf("CPF (000.000.000-00): ");
    scanf("%s", cpf);
}
