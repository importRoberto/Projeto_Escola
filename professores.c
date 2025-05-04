#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ProjetoEscola.h"


/*---------------------------------------------------------
  BLOCO DE FUNÇÕES DE PROFESSOR
  Operações CRUD para professores com geração de matrícula
  Valida integridade dos dados e relações com disciplinas
-----------------------------------------------------------*/

void CadastrarProfessor(Professor professores[], int *qtdProfessores) {
    if (*qtdProfessores >= MAX) {
        printf("Limite de professores atingido.\n");
        return;
    }

    Professor novo;
    PreencherDadosComuns(novo.nome, novo.matricula, novo.dataNascimento, &novo.sexo, novo.cpf,2);
    professores[*qtdProfessores] = novo;
    (*qtdProfessores)++;
    printf("\nProfessor cadastrado com sucesso! Matrícula: %s\n\n", novo.matricula);
}

void removerProfessor(Professor professores[], int *qtdProfessor) {
    if (*qtdProfessor == 0) {
        printf("Não há professores cadastrados.\n");
        return;
    }

    char busca[100];
    printf("Digite o nome para buscar: ");
    limparBuffer();
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    char buscaUpper[100];
    ToUpperStr(buscaUpper, busca);

    int encontrados[MAX], qtdEncontrados = 0;
    for (int i = 0; i < *qtdProfessor; i++) {
        char nomeUpper[100];
        ToUpperStr(nomeUpper, professores[i].nome);

        if (strstr(nomeUpper, buscaUpper)) {
            printf("[%d] - %s\n", qtdEncontrados, professores[i].nome);
            encontrados[qtdEncontrados++] = i;
        }
    }

    if (qtdEncontrados == 0) {
        printf("Nenhum professor encontrado.\n");
        return;
    }

    int opcao;
   while(1){
    printf("Digite o índice do professor que deseja remover:");
    if(scanf("%d", &opcao)==1 && opcao>=0 && opcao <qtdEncontrados){
        limparBuffer();
        break;
    }else{
        printf("Entrada inválida. Digite um número válido.\n");
        limparBuffer();
    }
   }

    int indice = encontrados[opcao];
    char confirmacao;
    printf("Remover %s? (S/N): ", professores[indice].nome);
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indice; i < *qtdProfessor - 1; i++)
            professores[i] = professores[i + 1];
        (*qtdProfessor)--;
        printf("Professor removido com sucesso!\n");
    } else {
        printf("Remoção cancelada.\n");
    }
}

void atualizarProfessor(Professor professores[], int qtdProfessores){
    if(qtdProfessores == 0){
        printf("Não há professores cadastrados.\n");
        return;
    }

    char busca[100];
    printf("Digite o nome (ou parte dele) para buscar o aluno:");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] ='\0';

    char buscaUpper[100];
    ToUpperStr(buscaUpper, busca);

    int encontrados[MAX];
    int qtdEncontrados = 0;

    for(int i =0; i <qtdProfessores; i++){
        char nomeUpper[100];
        ToUpperStr(nomeUpper, professores[i].nome);

        if(strstr(nomeUpper, buscaUpper)){
            printf("[%d] Nome: %s | Matrícula: %s\n", qtdEncontrados, professores[i].nome, professores[i].matricula);
            encontrados[qtdEncontrados] = i;
            qtdEncontrados++;
        }
    }

    if(qtdEncontrados ==0){
        printf("Nenhum professor encontrado.\n");
        return;
    }

    int opcao;
    while(1){
        printf("Digite o índice do professor que deseja atualizar:");
        if(scanf("%d", &opcao)==1 && opcao<=0 && opcao >qtdEncontrados){
            limparBuffer();
            break;
        }else{
            printf("Entrada inválida. Digite um número válido.\n");
            limparBuffer();
        }
       }
        int indiceReal = encontrados[opcao];

        printf("Atualizando dados do professor: %s\n", professores[indiceReal].nome);
        char buffer[100];

        //Atualizando nome
        printf("Novo nome (ENTER para manter '%s'): ", professores[indiceReal].nome);
        fgets(buffer, sizeof(buffer), stdin);
        
        // Se usuário não pressionou ENTER (quer alterar)
        if(buffer[0] != '\n') {
            // Remove quebra de linha
            buffer[strcspn(buffer, "\n")] = '\0';
            
            // Validação do novo nome
            int valido = 1;
            for(int i = 0; buffer[i] != '\0'; i++) {
                if(!isalpha(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\'') {
                    valido = 0;
                    break;
                }
            }
            
            if(valido && strlen(buffer) > 0) {
                // Converter para maiúsculas antes de copiar
                ToUpperStr(professores[indiceReal].nome, buffer);
                printf("Nome alterado com sucesso!\n");
            } else {
                printf("Nome inválido. Alteração cancelada.\n");
            }
        } else {
            printf("Nome mantido sem alterações.\n");
        }
        // Data de Nascimento
        printf("Nova data de nascimento(ENTER para manter '%s'):", professores[indiceReal].dataNascimento);
        fgets(buffer, sizeof(buffer), stdin);
        if(buffer[0] != '\n'){
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(professores[indiceReal].dataNascimento, buffer);
        }

        //Sexo
        printf("Novo sexo: (ENTER para manter '%c'):", professores[indiceReal].sexo);
        fgets(buffer, sizeof(buffer),stdin);

        if(buffer[0] != '\n'){
            char novoSexo = toupper(buffer[0]);
                
            while((novoSexo != 'F')&&(novoSexo != 'M')){
                printf("Entrada inválida. Digite 'M' para masculino ou 'F' para feminino:");
                scanf(" %c", &novoSexo);
                limparBuffer();
                novoSexo=toupper(novoSexo);
        }
        professores[indiceReal].sexo = novoSexo;
    }

    printf("Professor atualizado com sucesso!\n");
    
}

// Funções de Listagem de Professor
void listarTodosProfessores(Professor professores[], int qtdProfessores){
    if(qtdProfessores == 0){
        printf("Não há professores cadastrados.");
        return;
    }
    printf("\n--- Lista de Professores ---\n");
    for(int i =0; i <qtdProfessores; i++){
       imprimirProfessor(professores[i]);

    }
}

void listarProfessorPorNome(Professor professores[], int qtdProfessores){
    if(qtdProfessores==0){
        printf("Não existem professores cadastrados.\n");
        return;
    }

    Professor copia[qtdProfessores];
    for(int i =0; i <qtdProfessores; i++){
        copia[i] = professores[i];
    }

    //Ordena os professores por nome utilizando Bubble Sort
    for(int i=0; i < qtdProfessores -1; i++){
        for(int j = 0; j <qtdProfessores - i - 1 ; j++){
            if(strcmp(copia[j].nome, copia[j + 1].nome) > 0) {
                Professor temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }
    
    printf("\n--- Lista de professores ordenada em ordem alfabética ---\n");
    for(int i =0; i <qtdProfessores; i++){
        imprimirProfessor(copia[i]);
    }
}

void ListarProfessoresPorSexo(Professor professores[], int qtdProfessores) {
    char sexoFiltro;

    printf("Digite o sexo dos professores a listar (M/F): ");
    scanf(" %c", &sexoFiltro);
    limparBuffer(); // se você já tem essa função, use para evitar bugs no buffer

    sexoFiltro = toupper(sexoFiltro);

    while (sexoFiltro != 'M' && sexoFiltro != 'F') {
        printf("Entrada inválida. Digite 'M' para masculino ou 'F' para feminino: ");
        scanf(" %c", &sexoFiltro);
        limparBuffer();
        sexoFiltro = toupper(sexoFiltro);
    }

    int encontrou = 0;
    printf("\n--- Professores do sexo %c ---\n", sexoFiltro);

    for (int i = 0; i < qtdProfessores; i++) {
        if (toupper(professores[i].sexo) == sexoFiltro) {
            imprimirProfessor(professores[i]);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum professor do sexo %c encontrado.\n", sexoFiltro);
    }
}

void ListarProfessoresPorDataNascimento(Professor professores[], int qtdProfessores) {
    if (qtdProfessores == 0) {
        printf("Nenhum professor cadastrado.\n");
        return;
    }

    Professor copia[qtdProfessores];
    for (int i = 0; i < qtdProfessores; i++) {
        copia[i] = professores[i];
    }

    for (int i = 0; i < qtdProfessores - 1; i++) {
        for (int j = 0; j < qtdProfessores - i - 1; j++) {
            if (CompararDatas(copia[j].dataNascimento, copia[j + 1].dataNascimento) > 0) {
                Professor temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- Professores por data de nascimento ---\n");
    for (int i = 0; i < qtdProfessores; i++) {
        imprimirProfessor(professores[i]);
    }
}

void BuscarPessoaPorNome(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, const char *termoBusca) {
    char termoBuscaUpper[100];
    ToUpperStr(termoBuscaUpper, termoBusca);

    int encontrou = 0;

    // Buscar em alunos
    for (int i = 0; i < qtdAlunos; i++) {
        char nomeUpper[100];
        ToUpperStr(nomeUpper, alunos[i].nome);

        if (strstr(nomeUpper, termoBuscaUpper)) {
            imprimirAluno(alunos[i]);
            encontrou = 1;
        }
    }

    // Buscar em professores
    for (int i = 0; i < qtdProfessores; i++) {
        char nomeUpper[100];
        ToUpperStr(nomeUpper, professores[i].nome);

        if (strstr(nomeUpper, termoBuscaUpper)) {
            imprimirProfessor(professores[i]);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum aluno ou professor encontrado com o nome contendo \"%s\".\n", termoBusca);
    }
}
