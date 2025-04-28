#include <stdio.h>
#include "alunos.h"
#include "professores.h"
#include "disciplinas.h"
#include "relatorios.h"


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
        printf("5 - Relatórios\n");
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

            case 5:
                ExibirMenuRelatorios(alunos, qtdAlunos, professores, qtdProfessores, disciplinas, qtdDisciplinas);
                break;
            
            default:
                printf("Opcao Invalida\n");
                break;
        }
    }

    return 0;
}
