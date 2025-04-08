#include <stdio.h>
#include <string.h>

#define MAX 100

// Estrutura de Aluno
typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11]; // DD/MM/AAAA
    char sexo;
    char cpf[15]; // 000.000.000-00
} Aluno;

// Função para cadastrar um novo aluno
void CadastrarAluno(Aluno alunos[], int *qtdAlunos) {
    if (*qtdAlunos >= MAX) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno novo;

    printf("Nome: ");
    getchar(); // Limpa o buffer do ENTER anterior
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o \n do final

    printf("Matrícula: ");
    scanf("%d", &novo.matricula);

    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", novo.dataNascimento);

    printf("Sexo (M/F): ");
    scanf(" %c", &novo.sexo); // Espaço antes para ignorar lixo no buffer

    printf("CPF (000.000.000-00): ");
    scanf("%s", novo.cpf);

    alunos[*qtdAlunos] = novo;
    (*qtdAlunos)++;

    printf("\nAluno cadastrado com sucesso!\n\n");
}

int main () {
    Aluno alunos[MAX];
    int qtdAlunos = 0;

    int opcao; // Opção que o usuário insere no Menu
    int sair = 0; // Condição de saída

    while (!sair) {
        // Opções para a visualização do usuário
        printf("Projeto Escola\n");
        printf("1 - Aluno\n2 - Professor\n3 - Disciplina\n0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao); // Leitura do input do usuário

        switch (opcao) {
            case 0: {
                sair = 1;
                break;
            }

            case 1: {
                printf("\n--- Módulo Aluno ---\n");
                CadastrarAluno(alunos, &qtdAlunos);
                break;
            }

            case 2: {
                printf("\n--- Módulo Professor ---\n(Em desenvolvimento)\n\n");
                break;
            }

            case 3: {
                printf("\n--- Módulo Disciplina ---\n(Em desenvolvimento)\n\n");
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
