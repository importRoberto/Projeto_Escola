#include <stdio.h>
#include <string.h>
#include "professores.h"
#include "utils.h"
#include "structs.h"


void CadastrarProfessor(Professor professores[], int *qtdProfessores) {
    if (*qtdProfessores >= MAX) {
        printf("Limite de professores atingido.\n");
        return;
    }

    Professor novo;
    PreencherDadosComuns(novo.nome, &novo.matricula, novo.dataNascimento, &novo.sexo, novo.cpf);
    professores[*qtdProfessores] = novo;
    (*qtdProfessores)++;
    printf("\nProfessor cadastrado com sucesso!\n\n");
}

void removerProfessor(Professor professores[], int *qtdProfessor) {
    if (*qtdProfessor == 0) {
        printf("Não há professores cadastrados.\n");
        return;
    }

    char busca[100];
    printf("Digite o nome para buscar: ");
    limparBuffer();
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    char buscaUpper[100];
    ToUpperStr(buscaUpper, busca);

    int encontrados[MAX], qtdEncontrados = 0;
    for (int i = 0; i < *qtdProfessor; i++) {
        char nomeUpper[100];
        ToUpperStr(nomeUpper, professores[i].nome);

        if (strstr(nomeUpper, buscaUpper)) {
            printf("[%d] - %s\n", qtdEncontrados, professores[i].nome);
            encontrados[qtdEncontrados++] = i;
        }
    }

    if (qtdEncontrados == 0) {
        printf("Nenhum professor encontrado.\n");
        return;
    }

    int opcao;
    printf("Digite o índice: ");
    scanf("%d", &opcao);

    if (opcao < 0 || opcao >= qtdEncontrados) {
        printf("Índice inválido.\n");
        return;
    }

    int indice = encontrados[opcao];
    char confirmacao;
    printf("Remover %s? (S/N): ", professores[indice].nome);
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indice; i < *qtdProfessor - 1; i++)
            professores[i] = professores[i + 1];
        (*qtdProfessor)--;
        printf("Professor removido com sucesso!\n");
    } else {
        printf("Remoção cancelada.\n");
    }
}
