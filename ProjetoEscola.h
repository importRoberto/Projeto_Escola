#ifndef PROJETOESCOLA_H
#define PROJETOESCOLA_H

//Aluno


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


//Professores
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


//Disciplinas
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


//Relatórios

void MenuRelatoriosAlunos(Aluno alunos[], int qtdAlunos);

void MenuRelatoriosProfessores(Professor professores[], int qtdProfessores);

void MenuRelatoriosDisciplinas(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos);

void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas);

//Utilitários

void ToUpperStr(char destino[], const char origem[]);

void limparBuffer();

void imprimirProfessor(Professor p);

void imprimirAluno(Aluno a);

void gerarMatriculaAluno(char matricula[]);

void gerarMatriculaProfessor(char matricula[]);

void PreencherDadosComuns(char nome[], char matricula[], char dataNascimento[], char *sexo, char cpf[], int tipo);

int CompararDatas(const char *data1, const char *data2);

void ListarAniversariantesDoMes(Aluno alunos[], int qtdAlunos);

void BuscarPessoaPorNome(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, const char *termoBusca);



#endif