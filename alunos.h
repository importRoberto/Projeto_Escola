#ifndef ALUNO_H
#define ALUNO_H

#define MAX 100

typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11]; // DD/MM/AAAA
    char sexo;
    char cpf[15]; // 000.000.000-00
} Aluno;

void CadastrarAluno(Aluno alunos[], int *qtdAlunos);
void ListarAlunos(Aluno alunos[], int qtdAlunos);
void removerAluno(Aluno alunos[], int *qtdAlunos);

#endif
