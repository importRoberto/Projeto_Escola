#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ProjetoEscola.h"

// Implementações das funções de relatório...



/*---------------------------------------------------------
  BLOCO DE FUNÇÕES DE RELATÓRIOS
  Gera relatórios consolidados com diferentes critérios
  Oferece opções de filtragem e ordenação
-----------------------------------------------------------*/

// Função para Menu de Relatórios de Alunos
void MenuRelatoriosAlunos(Aluno alunos[], int qtdAlunos) {
    int escolha;
    do {
        printf("\n=== RELATÓRIOS DE ALUNOS ===\n");
        printf("1. Listar Todos\n");
        printf("2. Listar por Sexo\n");
        printf("3. Listar por Nome (Ordenado)\n");
        printf("4. Listar por Data de Nascimento\n");
        printf("5. Aniversariantes do Mês\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: ListarTodosAlunos(alunos, qtdAlunos); break;
            case 2: ListarAlunosPorSexo(alunos, qtdAlunos); break;
            case 3: ListarAlunosOrdenadosPorNome(alunos, qtdAlunos); break;
            case 4: ListarAlunosPorDataNascimento(alunos, qtdAlunos); break;
            case 5: ListarAniversariantesDoMes(alunos, qtdAlunos); break;
        }
    } while (escolha != 0);
}


// Menu de Relatórios de Professores
void MenuRelatoriosProfessores(Professor professores[], int qtdProfessores) {
    int escolha;
    do {
        printf("\n=== RELATÓRIOS DE PROFESSORES ===\n");
        printf("1. Listar Todos\n");
        printf("2. Listar por Sexo\n");
        printf("3. Listar por Nome (Ordenado)\n");
        printf("4. Listar por Data de Nascimento\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: listarTodosProfessores(professores, qtdProfessores); break;
            case 2: ListarProfessoresPorSexo(professores, qtdProfessores); break;
            case 3: listarProfessorPorNome(professores, qtdProfessores); break;
            case 4: ListarProfessoresPorDataNascimento(professores, qtdProfessores); break;
        }
    } while (escolha != 0);
}


// Menu de Relatórios de Disciplinas
void MenuRelatoriosDisciplinas(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos) {
    int escolha;
    do {
        printf("\n=== RELATÓRIOS DE DISCIPLINAS ===\n");
        printf("1. Listar Todas\n");
        printf("2. Listar com Mais de 40 Alunos\n");
        printf("3. Listar Detalhes de uma Disciplina\n");
        printf("4. Listar com Mais de 40 Vagas\n");
        printf("5. Listar Disciplina sem Aluno");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: listarTodasDisciplinas(disciplinas, qtdDisciplinas); break;
            case 2: listarDisciplinasMais40(disciplinas, qtdDisciplinas); break;
            case 3: ListarUmaDisciplina(disciplinas, qtdDisciplinas, alunos, qtdAlunos); break;
            case 4: listarDisciplinasComMaisDe40Vagas(disciplinas, qtdDisciplinas); break;
            case 5: listarDisciplinasSemAlunos(disciplinas, qtdDisciplinas); break;
        }
    } while (escolha != 0);
}

void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas) {
    int escolha;
    do {
        printf("\n=== MENU DE RELATÓRIOS ===\n");
        printf("1. Relatórios de Alunos\n");
        printf("2. Relatórios de Professores\n");
        printf("3. Relatórios de Disciplinas\n");
        printf("4. Buscar Pessoa por Nome\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: MenuRelatoriosAlunos(alunos, qtdAlunos); break;
            case 2: MenuRelatoriosProfessores(professores, qtdProfessores); break;
            case 3: MenuRelatoriosDisciplinas(disciplinas, qtdDisciplinas, alunos, qtdAlunos); break;
            case 4: {
                char busca[100];
                printf("Digite parte do nome: ");
                limparBuffer();
                fgets(busca, sizeof(busca), stdin);
                busca[strcspn(busca, "\n")] = '\0';
                BuscarPessoaPorNome(alunos, qtdAlunos, professores, qtdProfessores, busca);
                break;
            }
        }
    } while (escolha != 0);
}

