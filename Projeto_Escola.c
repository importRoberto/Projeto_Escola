#include <stdio.h>



int main () {

    int opcao; // Opção que o usuário insere no Menu
    int sair = 0; // Condição de saída

    while (!sair) {
        // Opções para a visualização do usuário
        printf("Projeto Escola\n1 - Aluno\n2 - Professor\n3 - Disciplina\n0 - Sair\n");
        scanf("%d", &opcao); // Leitura do input do usuário

        switch (opcao) {
            case 0: {
                sair = 1;
                break;
            }

            case 1: {
                printf("Módulo Aluno\n");
                break;
            }

            case 2: {
                printf("Módulo Professor\n");
                break;
            }

            case 3: {
                printf("Módulo Disciplina\n");
                break;
            }

            default: {
                printf("Opção Inválida\n");
                break;
            }
        }
    }



    return 0;
}