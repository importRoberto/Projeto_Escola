
#ifndef PROFESSOR_H
#define PROFESSOR_H


typedef struct {
    char nome[100];
    char matricula[15];
    char dataNascimento[11];
    char sexo;
    char cpf[15];
} Professor;


#define MAX 100

void CadastrarProfessor(Professor professores[], int *qtdProfessores);

void removerProfessor(Professor professores[], int *qtdProfessor);

void atualizarProfessor(Professor professores[], int qtdProfessores);

void listarTodosProfessores(Professor professores[], int qtdProfessores);

void listarProfessorPorNome(Professor professores[], int qtdProfessores);

void ListarProfessoresPorSexo(Professor professores[], int qtdProfessores);

void ListarProfessoresPorDataNascimento(Professor professores[], int qtdProfessores);


#endif