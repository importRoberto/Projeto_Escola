#include <stdio.h>
#include <string.h>
#include "aluno.h"
#include "utils.h"

// Função para cadastrar aluno
void CadastrarAluno(Aluno alunos[], int *qtdAlunos) {
    if (*qtdAlunos >= MAX) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno novo;
    PreencherDadosComuns(novo.nome, &novo.matricula, novo.dataNascimento, &novo.sexo, novo.cpf);
    alunos[*qtdAlunos] = novo;
    (*qtdAlunos)++;

    printf("\nAluno cadastrado com sucesso!\n\n");
}

// Listar alunos
void ListarAlunos(Aluno alunos[], int qtdAlunos) {
    if (qtdAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdAlunos; i++) {
        printf("Nome: %s\n", alunos[i].nome);
        printf("Matrícula: %d\n", alunos[i].matricula);
        printf("Data de Nascimento: %s\n", alunos[i].dataNascimento);
        printf("Sexo: %c\n", alunos[i].sexo);
        printf("CPF: %s\n", alunos[i].cpf);
        printf("-----------------------------\n");
    }
}

// Remover aluno
void removerAluno(Aluno alunos[], int *qtdAlunos) {
    if (*qtdAlunos == 0) {
        printf("Não há alunos cadastrados.\n");
        return;
    }

    char busca[100];
    printf("Digite o nome (ou parte) para buscar o aluno: ");
    limparBuffer();
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    char buscaUpper[100];
    ToUpperStr(buscaUpper, busca);

    int encontrados[MAX];
    int qtdEncontrados = 0;

    for (int i = 0; i < *qtdAlunos; i++) {
        char nomeUpper[100];
        ToUpperStr(nomeUpper, alunos[i].nome);

        if (strstr(nomeUpper, buscaUpper) != NULL) {
            printf("[%d] - Nome: %s | Matrícula: %d\n", qtdEncontrados, alunos[i].nome, alunos[i].matricula);
            encontrados[qtdEncontrados] = i;
            qtdEncontrados++;
        }
    }

    if (qtdEncontrados == 0) {
        printf("Nenhum aluno encontrado com o nome informado.\n");
        return;
    }

    int opcao;
    printf("Digite o índice do aluno que deseja remover: ");
    scanf("%d", &opcao);
    limparBuffer();

    if (opcao < 0 || opcao >= qtdEncontrados) {
        printf("Índice inválido.\n");
        return;
    }

    int indiceReal = encontrados[opcao];

    char confirmacao;
    printf("Tem certeza que deseja remover o aluno %s? (S/N): ", alunos[indiceReal].nome);
    scanf(" %c", &confirmacao);
    limparBuffer();

    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indiceReal; i < *qtdAlunos - 1; i++) {
            alunos[i] = alunos[i + 1];
        }
        (*qtdAlunos)--;
        printf("Aluno removido com sucesso!\n");
    } else {
        printf("Remoção cancelada.\n");
    }
}
