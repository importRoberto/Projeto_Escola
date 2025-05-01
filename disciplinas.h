#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H

#include "professores.h"
#include "alunos.h"

// Estrutura de Disciplina
typedef struct {
    char nome[100];
    char codigo[10];
    float semestre;
    char professor[100];
    char matriculasAlunos[MAX_ALUNOS][10]; // Armazena as matrículas dos alunos matriculados
    int capacidadeMaxima; 
    int qtdAlunos; // Quantidade atual de alunos matriculados
} Disciplina;


void CadastrarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas, Professor professores[], int qtdProfessores);

void listarTodasDisciplinas(Disciplina disciplinas[], int qtdDisciplinas);

void listarDisciplinasMais40(Disciplina disciplinas[], int qtdDisciplinas);

void ListarAlunosMenosDeTresDisciplinas(Aluno alunos[], int qtdAlunos, Disciplina disciplinas[], int qtdDisciplinas);

void matricularAlunoEmDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos);

void atualizarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas, Professor professores[], int qtdProfessores);

void removerDisciplina(Disciplina disciplinas[], int *qtdDisciplinas);

void ListarUmaDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos);

#endif


