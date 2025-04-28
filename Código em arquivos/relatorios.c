#include <stdio.h>
#include "relatorios.h"
#include "alunos.h"

void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas) {
    int opcao;
    do {
        printf("\n--- Relatórios ---\n");
        printf("1 - Listar Alunos\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                ListarAlunos(alunos, qtdAlunos);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}
