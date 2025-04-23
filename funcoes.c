// funcoes.h
#define FUNCOES_H
#define FUNCOES_H

#define MAX 100
#define MAX_ALUNOS 100

typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11];
    char sexo;
    char cpf[15];
} Aluno;

typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11];
    char sexo;
    char cpf[15];
} Professor;

typedef struct {
    char nome[100];
    char codigo[10];
    int semestre;
    char professor[100];
    int alunosMatriculados[MAX_ALUNOS];
    int qtdAlunos;
} Disciplina;

void PreencherDadosComuns(char nome[], int *matricula, char dataNascimento[], char *sexo, char cpf[]);
void CadastrarAluno(Aluno alunos[], int *qtdAlunos);
void CadastrarProfessor(Professor professores[], int *qtdProfessores);
void CadastrarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas);
void MatricularAlunoEmDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos);
void ListarAlunos(Aluno alunos[], int qtdAlunos);
void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas);
