#include <stdio.h>
#include "alunos.h"
#include "professores.h"
#include "disciplinas.h"
#include "relatorios.h"

int main() {
    Aluno alunos[MAX];
    Professor professores[MAX];
    Disciplina disciplinas[MAX];
    int qtdAlunos = 0, qtdProfessores = 0, qtdDisciplinas = 0;
    int opcao;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1 - Aluno\n2 - Professor\n3 - Disciplina\n4 - Matricular Aluno\n5 - Relatórios\n0 - Sair\nOpção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                CadastrarAluno(alunos, &qtdAlunos);
                break;
            case 2:
                CadastrarProfessor(professores, &qtdProfessores);
                break;
            case 3:
                CadastrarDisciplina(disciplinas, &qtdDisciplinas);
                break;
            case 4:
                MatricularAlunoEmDisciplina(disciplinas, qtdDisciplinas, alunos, qtdAlunos);
                break;
            case 5:
                ExibirMenuRelatorios(alunos, qtdAlunos, professores, qtdProfessores, disciplinas, qtdDisciplinas);
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
