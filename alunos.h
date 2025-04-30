
#ifndef ALUNO_H
#define ALUNO_H


#define MAX_ALUNOS 100

typedef struct {
    char nome[100];
    char matricula[15];
    char dataNascimento[11]; // DD/MM/AAAA
    char sexo;
    char cpf[15]; // 000.000.000-00
} Aluno;

void CadastrarAluno(Aluno alunos[], int *qtdAlunos);

void ListarTodosAlunos(Aluno alunos[], int qtdAlunos);

void ListarAlunosPorSexo(Aluno alunos[], int qtdAlunos);

void ListarAlunosOrdenadosPorNome(Aluno alunos[], int qtdAlunos);

void ListarAlunosPorDataNascimento(Aluno alunos[], int qtdAlunos);

void removerAluno(Aluno alunos[], int *qtdAlunos);

void atualizarAluno(Aluno alunos[], int qtdAlunos);

void ListarAniversariantesDoMes(Aluno alunos[], int qtdAlunos);

#endif