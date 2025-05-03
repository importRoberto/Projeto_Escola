#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ProjetoEscola.h"


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
        printf("4 - Relatórios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                sair = 1;
                break;

            case 1:
                printf("\n--- Modulo Aluno ---\n");
				int opc;
				printf("Desejas:\n[1]- Cadastrar\n[2]- Atualizar\n[3]- Remover\n[4]- Matricular Aluno em Disciplina\n");
				printf("Digite a opção: ");
				scanf("%d", &opc); 
				limparBuffer();   
				
				if (opc == 1) {
				    CadastrarAluno(alunos, &qtdAlunos);
				}
				else if (opc == 2) {
				    atualizarAluno(alunos, qtdAlunos);
				}
				else if (opc == 3) {
				    removerAluno(alunos, &qtdAlunos);
				}
                else if(opc ==4){
                    printf("\n--- Matricular Aluno em Disciplina ---\n");
                    matricularAlunoEmDisciplina(disciplinas, qtdDisciplinas, alunos, qtdAlunos);
                }
				else {
				    printf("Opção inválida.\n");
				}

                
                break;

            case 2:
                printf("\n--- Módulo Professor ---\n");
				printf("Deseja:\n[1] Cadastrar\n[2] Atualizar\n[3] Remover\n");
				printf("Digite a opção: ");
				scanf("%d", &opc);
				limparBuffer();  
				
				if (opc == 1) {
				    CadastrarProfessor(professores, &qtdProfessores);
				}
				else if (opc == 2) {
				    atualizarProfessor(professores, qtdProfessores);
				}
				else if (opc == 3) {
				    removerProfessor(professores, &qtdProfessores);
				}
				else {
				    printf("Opção inválida.\n");
				}

                break;

                case 3:
                printf("\n--- Módulo Disciplina ---\n");
                printf("Deseja:\n[1] Cadastrar\n[2] Atualizar\n[3] Remover\n");
                printf("Digite a opção: ");
                scanf("%d", &opc);
                limparBuffer();
                
                if (opc == 1) {
                    CadastrarDisciplina(disciplinas, &qtdDisciplinas, professores, qtdProfessores);
                }
                else if (opc == 2) {
                    atualizarDisciplina(disciplinas, &qtdDisciplinas, professores, qtdProfessores);
                }
                else if (opc == 3) {
                    removerDisciplina(disciplinas, &qtdDisciplinas);
                }                 
                else {
                    printf("Opção inválida.\n");
                }
                break;
            case 4:
                ExibirMenuRelatorios(alunos, qtdAlunos, professores, qtdProfessores, disciplinas, qtdDisciplinas);
                break;
            
            default:
                printf("Opcao Invalida\n");
                break;
        }
    }

    return 0;
}
