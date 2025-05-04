#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ProjetoEscola.h"

/*---------------------------------------------------------
  BLOCO DE FUNÇÕES DE DISCIPLINA
  Gerencia disciplinas com controle de capacidade
  Valida relações com professores e alunos matriculados
-----------------------------------------------------------*/

void CadastrarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas, Professor professores[], int qtdProfessores) {
    if (*qtdDisciplinas >= MAX) {
        printf("Limite de disciplinas atingido.\n");
        return;
    }

    Disciplina nova;
    char nomeProfessor[100];
    int professorEncontrado = 0;
    char nomeDisciplinaTemp[100];

    printf("Nome da disciplina: ");
    fgets(nomeDisciplinaTemp, 100, stdin);
    nomeDisciplinaTemp[strcspn(nomeDisciplinaTemp, "\n")] = '\0';
    ToUpperStr(nova.nome, nomeDisciplinaTemp);

    char codigoTemp[10];
    printf("Código da disciplina: ");
    scanf("%s", codigoTemp);
    limparBuffer();
    ToUpperStr(nova.codigo, codigoTemp);
    
    printf("Semestre: ");
    scanf("%f", &nova.semestre);
    limparBuffer();

    printf("Capacidade máxima de alunos: ");
    scanf("%d", &nova.capacidadeMaxima);
    limparBuffer();

    // Validação do professor (com case-insensitive)
    do {
        printf("Nome do professor responsável: ");
        fgets(nomeProfessor, 100, stdin);
        nomeProfessor[strcspn(nomeProfessor, "\n")] = '\0';

        // Verifica se não há professores cadastrados
        if (qtdProfessores == 0) {
            printf("\nNão é possível cadastrar a disciplina: não existem professores cadastrados.\n");
            return; // Encerra a função
        }

        // Converter entrada para maiúsculas
        char nomeProfessorUpper[100];
        ToUpperStr(nomeProfessorUpper, nomeProfessor);

        professorEncontrado = 0;
        for(int i = 0; i < qtdProfessores; i++) {
            // Converter nome do professor cadastrado para maiúsculas
            char nomeCadastradoUpper[100];
            ToUpperStr(nomeCadastradoUpper, professores[i].nome);

            // Comparar versões em maiúsculas
            if(strcmp(nomeCadastradoUpper, nomeProfessorUpper) == 0) {
                professorEncontrado = 1;
                strcpy(nova.professor, professores[i].nome); // Usa o nome original
                break;
            }
        }

        if(!professorEncontrado) {
            printf("\nProfessor não encontrado! Professores disponíveis:\n");
            
            for(int i = 0; i < qtdProfessores; i++) {
                printf("[%d] %s\n", i+1, professores[i].nome);
            }
            
            int escolha;
            printf("\nDigite o número do professor desejado (ou 0 para cancelar): ");
            scanf("%d", &escolha);
            limparBuffer();
            
            if(escolha > 0 && escolha <= qtdProfessores) {
                strcpy(nova.professor, professores[escolha-1].nome);
                professorEncontrado = 1;
            } else {
                printf("Cadastro de disciplina cancelado!\n");
                return;
            }
        }
    } while(!professorEncontrado);

    nova.qtdAlunos = 0;
    disciplinas[*qtdDisciplinas] = nova;
    (*qtdDisciplinas)++;
    printf("\nDisciplina cadastrada com sucesso!\n\n");
}


void listarTodasDisciplinas(Disciplina disciplinas[], int qtdDisciplinas){
    printf("\n--- Lista de Disciplinas ---\n");
    if(qtdDisciplinas == 0){
        printf("Não existem disciplinas cadastradas.\n");
        return;
    }
    for(int i = 0; i < qtdDisciplinas; i++){  
        printf("[%d] Nome: %s | Código: %s | Semestre: %.1f | Professor: %s\n",i + 1,disciplinas[i].nome, disciplinas[i].codigo, disciplinas[i].semestre,disciplinas[i].professor);
    }
    printf("--------------------------------\n");
}


void listarDisciplinasMais40(Disciplina disciplinas[], int qtdDisciplinas){
    int encontrou = 0;
    printf("\n--- Lista de Disciplinas com mais de 40 alunos ---\n");
    for(int i =0; i < qtdDisciplinas; i++){
        if(disciplinas[i].qtdAlunos>40){
        printf("[%d] Nome: %s | Código: %s | Professor: %s| Semestre: %.1f\n", i+1, disciplinas[i].nome, disciplinas[i].codigo, disciplinas[i].professor, disciplinas[i].semestre);
        encontrou = 1;
    }
}
    if (!encontrou){
        printf("Nenuma disciplina com mais de 40 alunos cadastrados.");

    }
    printf("--------------------------------\n");
}

void ListarAlunosMenosDeTresDisciplinas(Aluno alunos[], int qtdAlunos, Disciplina disciplinas[], int qtdDisciplinas) {
    int matriculas[MAX_ALUNOS] = {0};  // Contador de disciplinas por aluno

    // Percorre todas as disciplinas
    for (int i = 0; i < qtdDisciplinas; i++) {
        // Percorre os alunos matriculados na disciplina
        for (int j = 0; j < disciplinas[i].qtdAlunos; j++) {
            char matriculaAluno[10];
            
            // Copia diretamente a matrícula (já é string)
            strcpy(matriculaAluno, disciplinas[i].matriculasAlunos[j]);

            // Busca o aluno correspondente
            for (int k = 0; k < qtdAlunos; k++) {
                if (strcmp(alunos[k].matricula, matriculaAluno) == 0) {
                    matriculas[k]++;  // Incrementa o contador
                    break;
                }
            }
        }
    }

    // Exibe os alunos com menos de 3 disciplinas
    printf("\nAlunos matriculados em menos de 3 disciplinas:\n");
    int encontrado = 0;
    for (int i = 0; i < qtdAlunos; i++) {
        if (matriculas[i] < 3) {
            imprimirAluno(alunos[i]);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum aluno matriculado em menos de 3 disciplinas.\n");
    }
}

void matricularAlunoEmDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos) {
    char codigoBusca[10];
    char matriculaBusca[15]; // Aumentado para 15 (tamanho da matrícula)
    int encontrouDisciplina = 0;

    printf("Digite o código da disciplina: ");
    scanf("%s", codigoBusca);

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoBusca) == 0) {
            encontrouDisciplina = 1;

            // Verifica se a disciplina está cheia
            if (disciplinas[i].qtdAlunos >= disciplinas[i].capacidadeMaxima) {
                printf("Limite de alunos nesta disciplina atingido.\n");
                return;
            }

            // Busca o aluno pela matrícula
            printf("Digite a matrícula do aluno: ");
            scanf("%s", matriculaBusca);
            limparBuffer();

            int alunoEncontrado = 0;
            for (int j = 0; j < qtdAlunos; j++) {
                if (strcmp(alunos[j].matricula, matriculaBusca) == 0) {
                    alunoEncontrado = 1;

                    // Verifica se o aluno já está matriculado
                    int jaMatriculado = 0;
                    for (int k = 0; k < disciplinas[i].qtdAlunos; k++) {
                        if (strcmp(disciplinas[i].matriculasAlunos[k], matriculaBusca) == 0) {
                            jaMatriculado = 1;
                            break;
                        }
                    }

                    if (jaMatriculado) {
                        printf("Aluno já está matriculado nesta disciplina.\n");
                        return;
                    }

                    // Adiciona a matrícula à disciplina
                    strcpy(disciplinas[i].matriculasAlunos[disciplinas[i].qtdAlunos], matriculaBusca);
                    disciplinas[i].qtdAlunos++;
                    printf("Aluno matriculado com sucesso!\n");
                    return;
                }
            }

            if (!alunoEncontrado) {
                printf("Matrícula não encontrada.\n");
                return;
            }
        }
    }

    if (!encontrouDisciplina) {
        printf("Disciplina não encontrada.\n");
    }
}


void atualizarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas, Professor professores[], int qtdProfessores) {
    if (*qtdDisciplinas == 0) {
        printf("Não há disciplinas cadastradas.\n");
        return;
    }

    char busca[100];
    printf("Digite o nome ou código da disciplina: ");
    limparBuffer();
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    char buscaUpper[100];
    ToUpperStr(buscaUpper, busca);

    int encontradas[MAX];
    int qtdEncontradas = 0;

    for (int i = 0; i < *qtdDisciplinas; i++) {
        char nomeUpper[100], codigoUpper[10];
        ToUpperStr(nomeUpper, disciplinas[i].nome);
        ToUpperStr(codigoUpper, disciplinas[i].codigo);

        if (strstr(nomeUpper, buscaUpper) != NULL || strstr(codigoUpper, buscaUpper) != NULL) {
            printf("[%d] %s (%s)\n", qtdEncontradas, disciplinas[i].nome, disciplinas[i].codigo);
            encontradas[qtdEncontradas] = i;
            qtdEncontradas++;
        }
    }

    if (qtdEncontradas == 0) {
        printf("Nenhuma disciplina encontrada.\n");
        return;
    }

    int opcao;
    while(1) {
        printf("Digite o índice da disciplina que deseja atualizar: ");
        if(scanf("%d", &opcao) == 1 && opcao >= 0 && opcao < qtdEncontradas) {
            limparBuffer();
            break;
        } else {
            printf("Índice inválido!\n");
            limparBuffer();
        }
    }

    int indice = encontradas[opcao];
    Disciplina *d = &disciplinas[indice];
    char buffer[100];

    printf("\nAtualizando disciplina: %s (%s)\n", d->nome, d->codigo);
    
    // --- Atualização do Nome (com conversão para maiúsculas) ---
    printf("Novo nome (ENTER para manter '%s'): ", d->nome);
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        ToUpperStr(buffer, buffer); // Converte para maiúsculas
        strcpy(d->nome, buffer);
    }

    // --- Atualização do Código (com conversão para maiúsculas) ---
    printf("Novo código (ENTER para manter '%s'): ", d->codigo);
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        ToUpperStr(buffer, buffer); // Converte para maiúsculas
        strcpy(d->codigo, buffer);
    }

    // Semestre

    printf("Novo semestre (ENTER para manter %.1f): ", d->semestre);
    fgets(buffer, sizeof(buffer), stdin);
    limparBuffer(); // Limpa o buffer de entrada após o fgets()

    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &d->semestre);
}

    // Capacidade
    printf("Nova capacidade máxima (ENTER para manter %d): ", d->capacidadeMaxima);
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[0] != '\n') {
        sscanf(buffer, "%d", &d->capacidadeMaxima);
    }

    // --- Atualização do Professor (com validação case-insensitive) ---
    while(1) {
        printf("Novo professor (ENTER para manter '%s'): ", d->professor);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if(buffer[0] == '\n') break;

        // Converter entrada para maiúsculas
        char bufferUpper[100];
        ToUpperStr(bufferUpper, buffer);

        int professorExiste = 0;
        for(int i = 0; i < qtdProfessores; i++) {
            // Converter nome cadastrado para maiúsculas
            char nomeCadastradoUpper[100];
            ToUpperStr(nomeCadastradoUpper, professores[i].nome);

            if(strcmp(nomeCadastradoUpper, bufferUpper) == 0) {
                strcpy(d->professor, professores[i].nome); // Mantém formatação original
                professorExiste = 1;
                break;
            }
        }

        if(professorExiste) break;

        printf("Professor não encontrado! Selecione um válido:\n");
        for(int i = 0; i < qtdProfessores; i++) {
            printf("[%d] %s\n", i+1, professores[i].nome);
        }

        int escolha;
        while(1) {
            printf("Digite o número do professor (0 para cancelar): ");
            if(scanf("%d", &escolha) == 1 && escolha >= 0 && escolha <= qtdProfessores) {
                limparBuffer();
                break;
            } else {
                printf("Entrada inválida!\n");
                limparBuffer();
            }
        }

        if(escolha == 0) break;
        strcpy(d->professor, professores[escolha-1].nome);
        break;
    }

    printf("Disciplina atualizada com sucesso!\n");
}

void removerDisciplina(Disciplina disciplinas[], int *qtdDisciplinas){
    if (*qtdDisciplinas == 0){  // Desreferenciar o ponteiro
        printf("Não há disciplinas cadastradas.\n");
        return;
    }

    int opcao = -1;
    do{
        listarTodasDisciplinas(disciplinas, *qtdDisciplinas);  // Passar *qtdDisciplinas aqui, valor inteiro
        printf("Digite o número da disciplina que deseja remover (ou 0 para sair):");
        scanf("%d", &opcao);
        limparBuffer();
    
        if (opcao == 0){
            printf("Remoção cancelada.\n");
            return;
        }

        if(opcao < 1 || opcao > *qtdDisciplinas){  // Verificar o valor de *qtdDisciplinas
            printf("Escolha inválida, tente novamente.\n\n");
        }
    } while(opcao < 1 || opcao > *qtdDisciplinas);

    int indice = opcao - 1;

    printf("Deseja realmente remover a disciplina %s? (S/N): ", disciplinas[indice].nome);
    char confirmacao;
    scanf(" %c", &confirmacao);
    limparBuffer();
    confirmacao = toupper(confirmacao);

    if(confirmacao != 'S'){
        printf("Remoção cancelada.\n");
        return;
    }

    // Realiza a remoção (desloca as disciplinas para a esquerda)
    for(int i = indice; i < (*qtdDisciplinas) - 1; i++){
        disciplinas[i] = disciplinas[i + 1];
    }
    
    (*qtdDisciplinas)--;  // Decrementa a quantidade de disciplinas

    printf("Disciplina removida com sucesso.\n");
}

void ListarUmaDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos) {
    char codigoBusca[10];
    int encontrada = 0;

    printf("Digite o código da disciplina que deseja listar: ");
    scanf("%s", codigoBusca);

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoBusca) == 0) {
            encontrada = 1;

            // Exibindo dados da disciplina
            printf("\n--- Dados da Disciplina ---\n");
            printf("Nome: %s\n", disciplinas[i].nome);
            printf("Código: %s\n", disciplinas[i].codigo);
            printf("Semestre: %.1f\n", disciplinas[i].semestre);
            printf("Professor: %s\n", disciplinas[i].professor);
            printf("Capacidade Máxima: %d\n", disciplinas[i].capacidadeMaxima); // Novo campo
            printf("Alunos Matriculados: %d\n", disciplinas[i].qtdAlunos);

            // Listando os alunos matriculados
            printf("\n--- Alunos Matriculados ---\n");
            
            if (disciplinas[i].qtdAlunos == 0) {
                printf("Nenhum aluno matriculado.\n");
            } else {
                for (int j = 0; j < disciplinas[i].qtdAlunos; j++) {
                    char matriculaAtual[10];
                    strcpy(matriculaAtual, disciplinas[i].matriculasAlunos[j]); // Novo array de strings

                    // Busca o aluno pela matrícula
                    for (int k = 0; k < qtdAlunos; k++) {
                        if (strcmp(alunos[k].matricula, matriculaAtual) == 0) {
                            imprimirAluno(alunos[k]);
                            break;
                        }
                    }
                }
            }
            return;
        }
    }

    if (!encontrada) {
        printf("Disciplina não encontrada.\n");
    }
}

void listarDisciplinasComMaisDe40Vagas(Disciplina disciplinas[], int qtdDisciplinas) {
    int encontrou = 0;
    printf("\n--- Lista de Disciplinas com mais de 40 vagas ---\n");
    for (int i = 0; i < qtdDisciplinas; i++) {
        if (disciplinas[i].capacidadeMaxima > 40) {
            printf("[%d] Nome: %s | Código: %s | Professor: %s | Semestre: %.1f | Vagas: %d\n", 
                   i + 1, 
                   disciplinas[i].nome, 
                   disciplinas[i].codigo, 
                   disciplinas[i].professor, 
                   disciplinas[i].semestre,
                   disciplinas[i].capacidadeMaxima);  // Mostra a capacidade total
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhuma disciplina com mais de 40 vagas cadastrada.\n");
    }
    printf("--------------------------------\n");
}
void listarDisciplinasSemAlunos(Disciplina disciplinas[], int qtdDisciplinas) {
    printf("\n--- Disciplinas sem alunos matriculados ---\n");
    
    if(qtdDisciplinas == 0) { // Verifica primeiro se há disciplinas
        printf("Nenhuma disciplina cadastrada no sistema.\n");
        printf("------------------------------------------\n");
        return;
    }
    
    int encontrou = 0;
    for(int i = 0; i < qtdDisciplinas; i++) {
        if(disciplinas[i].qtdAlunos == 0) {
            printf("[%d] Código: %s | Nome: %s | Professor: %s | Semestre: %.1f\n",
                   i + 1,
                   disciplinas[i].codigo,
                   disciplinas[i].nome,
                   disciplinas[i].professor,
                   disciplinas[i].semestre);
            encontrou = 1;
        }
    }
    
    if(!encontrou) {
        printf("Todas as %d disciplinas possuem alunos matriculados.\n", qtdDisciplinas);
    }
    printf("------------------------------------------\n");
}