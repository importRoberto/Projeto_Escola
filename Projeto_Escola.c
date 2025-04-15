#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_ALUNOS 100

// Estrutura de Aluno
typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11]; // DD/MM/AAAA
    char sexo;
    char cpf[15]; // 000.000.000-00
} Aluno;

// Estrutura de Professor
typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11];
    char sexo;
    char cpf[15];
} Professor;

// Estrutura de Disciplina
typedef struct {
    char nome[100];
    char codigo[10];
    int semestre;
    char professor[100];
    int alunosMatriculados[MAX_ALUNOS]; 
    int qtdAlunos;
} Disciplina;

// Função auxiliar para preencher dados comuns
void PreencherDadosComuns(char nome[], int *matricula, char dataNascimento[], char *sexo, char cpf[]) {
    printf("Nome: ");
    getchar(); 
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

// Função para cadastrar professor
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

// Função para cadastrar disciplina
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

            // Verificar se aluno existe
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

            // Matricular aluno
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

int main() {
    Aluno alunos[MAX];
    Professor professores[MAX];
    Disciplina disciplinas[MAX];
    int qtdAlunos = 0;
    int qtdProfessores = 0;
    int qtdDisciplinas = 0;

    int opcao;
    int sair = 0;

    while (!sair) {
        printf("\n--- Projeto Escola ---\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Disciplina\n");
        printf("4 - Matricular Aluno em Disciplina\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                sair = 1;
                break;

            case 1:
                printf("\n--- Modulo Aluno ---\n");
                CadastrarAluno(alunos, &qtdAlunos);
                break;

            case 2:
                printf("\n--- Modulo Professor ---\n");
                CadastrarProfessor(professores, &qtdProfessores);
                break;

            case 3:
                printf("\n--- Modulo Disciplina ---\n");
                CadastrarDisciplina(disciplinas, &qtdDisciplinas);
                break;

            case 4:
                printf("\n--- Matricular Aluno em Disciplina ---\n");
                MatricularAlunoEmDisciplina(disciplinas, qtdDisciplinas, alunos, qtdAlunos);
                break;

            default:
                printf("Opcao Invalida\n");
                break;
        }
    }

    return 0;
}
