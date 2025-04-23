#include <stdio.h>
#include <string.h>
#include "funcoes.h"

void PreencherDadosComuns(char nome[], int *matricula, char dataNascimento[], char *sexo, char cpf[]) {
    printf("Nome: ");
    while (getchar() != '\n');
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Matricula: ");
    scanf("%d", matricula);

    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", dataNascimento);

    printf("Sexo (M/F): ");
    scanf(" %c", sexo);

    printf("CPF (000.000.000-00): ");
    scanf("%s", cpf);
}

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

void CadastrarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas) {
    if (*qtdDisciplinas >= MAX) {
        printf("Limite de disciplinas atingido.\n");
        return;
    }

    Disciplina nova;

    printf("Nome da disciplina: ");
    getchar();
    fgets(nova.nome, 100, stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0';

    printf("Código da disciplina: ");
    scanf("%s", nova.codigo);

    printf("Semestre: ");
    scanf("%d", &nova.semestre);

    printf("Nome do professor responsável: ");
    getchar();
    fgets(nova.professor, 100, stdin);
    nova.professor[strcspn(nova.professor, "\n")] = '\0';

    nova.qtdAlunos = 0;

    disciplinas[*qtdDisciplinas] = nova;
    (*qtdDisciplinas)++;

    printf("\nDisciplina cadastrada com sucesso!\n\n");
}

void MatricularAlunoEmDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos) {
    char codigoBusca[10];
    int matriculaBusca;
    int encontrado = 0;

    printf("Digite o código da disciplina: ");
    scanf("%s", codigoBusca);

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoBusca) == 0) {
            encontrado = 1;

            if (disciplinas[i].qtdAlunos >= MAX_ALUNOS) {
                printf("Limite de alunos nesta disciplina atingido.\n");
                return;
            }

            printf("Digite a matrícula do aluno: ");
            scanf("%d", &matriculaBusca);

            int alunoExiste = 0;
            for (int j = 0; j < qtdAlunos; j++) {
                if (alunos[j].matricula == matriculaBusca) {
                    alunoExiste = 1;
                    break;
                }
            }

            if (!alunoExiste) {
                printf("Aluno não encontrado.\n");
                return;
            }

            disciplinas[i].alunosMatriculados[disciplinas[i].qtdAlunos] = matriculaBusca;
            disciplinas[i].qtdAlunos++;

            printf("Aluno matriculado com sucesso!\n");
            return;
        }
    }

    if (!encontrado) {
        printf("Disciplina não encontrada.\n");
    }
}
