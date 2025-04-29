#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100
#define MAX_PROFESSORES 50
#define MAX_DISCIPLINAS 50
#define MAX_ALUNOS_POR_DISCIPLINA 50

typedef struct {
    int matricula;
    char nome[100];
    int idade;
    char sexo;
    char cpf[15];
    char dataNascimento[11];
} Aluno;

typedef struct {
    int matricula;
    char nome[100];
    int idade;
    char sexo;
    char cpf[15];
    char dataNascimento[11];
} Professor;

typedef struct {
    char codigo[10];
    char nome[100];
    int semestre;
    int qtdAlunos;
    int alunosMatriculados[MAX_ALUNOS_POR_DISCIPLINA];
    int matriculaProfessor;
} Disciplina;

// Dados de teste disponíveis globalmente:
Aluno alunos[MAX_ALUNOS] = {
    {2025106001, "Ana Clara", 20, 'F', "12345678901", "01/01/2004"},
    {2025106002, "Carlos Eduardo", 21, 'M', "23456789012", "15/02/2003"},
    {2025106003, "Beatriz Silva", 22, 'F', "34567890123", "22/03/2002"}
};
int qtdAlunos = 3;

Professor professores[MAX_PROFESSORES] = {
    {2025117001, "Luciano Alves", 45, 'M', "45678901234", "12/07/1979"},
    {2025117002, "Juliana Souza", 39, 'F', "56789012345", "05/11/1985"}
};
int qtdProfessores = 2;

Disciplina disciplinas[MAX_DISCIPLINAS] = {
    {"INF101", "Algoritmos", 1, 2, {2025106001, 2025106002}, 2025117001},
    {"INF102", "Estrutura de Dados", 2, 1, {2025106003}, 2025117002}
};
int qtdDisciplinas = 2;
