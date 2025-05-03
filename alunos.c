#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ProjetoEscola.h"


void CadastrarAluno(Aluno alunos[], int *qtdAlunos) {
    if (*qtdAlunos >= MAX) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno novo;
    PreencherDadosComuns(novo.nome, novo.matricula, novo.dataNascimento, &novo.sexo, novo.cpf, 1);
    
    alunos[*qtdAlunos] = novo;
    (*qtdAlunos)++;

    // Nova linha para imprimir a matrícula gerada
    printf("\nAluno cadastrado com sucesso! Matrícula: %s\n\n", novo.matricula);
}

// Listar alunos
void ListarTodosAlunos(Aluno alunos[], int qtdAlunos) {
    if (qtdAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
    for (int i = 0; i < qtdAlunos; i++) {
        imprimirAluno(alunos[i]); // Chama a função de impressão
    }
}
void ListarAlunosPorSexo(Aluno alunos[], int qtdAlunos) {
    char sexoDesejado;
    
    if (qtdAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    printf("Digite o sexo que deseja listar (M/F): ");
    scanf(" %c", &sexoDesejado);
    limparBuffer();
    sexoDesejado = toupper(sexoDesejado);

    while (sexoDesejado != 'M' && sexoDesejado != 'F') {
        printf("Sexo inválido. Digite 'M' para masculino ou 'F' para feminino: ");
        scanf(" %c", &sexoDesejado);
        limparBuffer();
        sexoDesejado = toupper(sexoDesejado);
    }

    int encontrados = 0;
    for (int i = 0; i < qtdAlunos; i++) {
        if (alunos[i].sexo == sexoDesejado) {
           imprimirAluno(alunos[i]);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum aluno do sexo %c encontrado.\n", sexoDesejado);
    }
}

void ListarAlunosOrdenadosPorNome(Aluno alunos[], int qtdAlunos) {
    if (qtdAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    // Criar uma cópia para não modificar o array original
    Aluno copia[qtdAlunos];
    for (int i = 0; i < qtdAlunos; i++) {
        copia[i] = alunos[i];
    }

    // Bubble Sort por nome
    for (int i = 0; i < qtdAlunos - 1; i++) {
        for (int j = 0; j < qtdAlunos - i - 1; j++) {
            if (strcmp(copia[j].nome, copia[j + 1].nome) > 0) {
                Aluno temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- Lista de Alunos Ordenados por Nome ---\n");
    for (int i = 0; i < qtdAlunos; i++) {
        imprimirAluno(copia[i]);  
    }
}



void ListarAlunosPorDataNascimento(Aluno alunos[], int qtdAlunos) {
    if (qtdAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    // Cópia do array original
    Aluno copia[qtdAlunos];
    for (int i = 0; i < qtdAlunos; i++) {
        copia[i] = alunos[i];
    }

    // Ordenação por data de nascimento (mais velho primeiro)
    for (int i = 0; i < qtdAlunos - 1; i++) {
        for (int j = 0; j < qtdAlunos - i - 1; j++) {
            if (CompararDatas(copia[j].dataNascimento, copia[j + 1].dataNascimento) > 0) {
                Aluno temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- Lista de Alunos por Data de Nascimento ---\n");
    for (int i = 0; i < qtdAlunos; i++) {
       imprimirAluno(alunos[i]);
    }
}

// Remover aluno
void removerAluno(Aluno alunos[], int *qtdAlunos) {
    if (*qtdAlunos == 0) {
        printf("Não há alunos cadastrados.\n");
        return;
    }

    char busca[100];
    printf("Digite o nome (ou parte) para buscar o aluno: ");
    limparBuffer();
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    char buscaUpper[100];
    ToUpperStr(buscaUpper, busca);

    int encontrados[MAX];
    int qtdEncontrados = 0;

    for (int i = 0; i < *qtdAlunos; i++) {
        char nomeUpper[100];
        ToUpperStr(nomeUpper, alunos[i].nome);

        if (strstr(nomeUpper, buscaUpper) != NULL) {
            printf("[%d] - Nome: %s | Matrícula: %s\n", qtdEncontrados, alunos[i].nome, alunos[i].matricula);
            encontrados[qtdEncontrados] = i;
            qtdEncontrados++;
        }
    }

    if (qtdEncontrados == 0) {
        printf("Nenhum aluno encontrado com o nome informado.\n");
        return;
    }

    int opcao;
   while(1){
    printf("Digite o índice do aluno que deseja remover:");
    if(scanf("%d", &opcao) == 1 && opcao >= 0 && opcao < qtdEncontrados){
        limparBuffer();
        break;
    }else{
        printf("Entrada inválida. Digite um número válido.\n");
        limparBuffer();
    }
   }
    int indiceReal = encontrados[opcao];

    char confirmacao;
    printf("Tem certeza que deseja remover o aluno %s? (S/N): ", alunos[indiceReal].nome);
    scanf(" %c", &confirmacao);
    limparBuffer();

    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indiceReal; i < *qtdAlunos - 1; i++) {
            alunos[i] = alunos[i + 1];
        }
        (*qtdAlunos)--;
        printf("Aluno removido com sucesso!\n");
    } else {
        printf("Remoção cancelada.\n");
    }
}

//Função para atualizar alunos
void atualizarAluno(Aluno alunos[], int qtdAlunos){
    if(qtdAlunos == 0){
        printf("Não há alunos cadastraddos.\n");
        return;
    }

    char busca[100];
    printf("Digite o nome (ou parte dele) para buscar o aluno:");
    limparBuffer();
    fgets(busca, sizeof(busca),stdin);
    busca[strcspn(busca, "\n")] = 0;

    char buscaUpper[100];
    ToUpperStr(buscaUpper,busca);

    int encontrados[MAX];
    int qtdEncontrados = 0;

    for(int i =0; i <qtdAlunos; i++){
        char nomeUpper[100];
        ToUpperStr(nomeUpper, alunos[i].nome);

        if(strstr(nomeUpper,buscaUpper)){
            printf("[%d] Nome: %s | Matrícula: %s\n", qtdEncontrados, alunos[i].nome, alunos[i].matricula);
            encontrados[qtdEncontrados] = i;
            qtdEncontrados++;
        }
    }

    if(qtdEncontrados==0){
        printf("Nenhum aluno encontrado.\n");
        return;
    }

    int opcao;
    
 	while(1){
    printf("Digite o índice do aluno que deseja atualizar: ");
    if(scanf("%d", &opcao)==1 && (opcao >= 0 && opcao < qtdEncontrados)){
        limparBuffer();
        break;
    }else{
        printf("Entrada inválida. Digite um número válido.\n");
        limparBuffer();
    }
}

        int indiceReal = encontrados[opcao];

        printf("Atualizando dados do aluno: %s\n", alunos[indiceReal].nome);
        char buffer[100];

        //Atualização do nome

        printf("Novo nome (ENTER para manter '%s'):", alunos[indiceReal].nome);
        fgets(buffer, sizeof(buffer), stdin);
        if(buffer[0] != '\n'){
           buffer[strcspn(buffer, "\n")] = '\0';  // CERTO
            strcpy(alunos[indiceReal].nome, buffer);
        }

        // Data de Nascimento
        printf("Nova data de nascimento(ENTER para manter '%s'):", alunos[indiceReal].dataNascimento);
        fgets(buffer, sizeof(buffer), stdin);
        
       	if(buffer[0] != '\n'){
           buffer[strcspn(buffer, "\n")] = '\0';  // CERTO
           strcpy(alunos[indiceReal].dataNascimento, buffer);
        }

       // Sexo
			printf("Novo sexo: (ENTER para manter '%c'):", alunos[indiceReal].sexo);
			fgets(buffer, sizeof(buffer),stdin);

			if(buffer[0] != '\n'){
    			char novoSexo = toupper(buffer[0]);
        
   			 while((novoSexo != 'F') && (novoSexo != 'M')){
       				 printf("Entrada inválida. Digite 'M' para masculino ou 'F' para feminino:");
       				 scanf(" %c", &novoSexo); // ADICIONAR o &
     				 limparBuffer();          // COLOCAR os parênteses
       				 novoSexo = toupper(novoSexo);
  			}
   				alunos[indiceReal].sexo = novoSexo;
}


    printf("Aluno atualizado com sucesso!\n");
    
}


void ListarAniversariantesDoMes(Aluno alunos[], int qtdAlunos) {
    int mesBusca;
    printf("Digite o número do mês (1 a 12) para listar os aniversariantes: ");
    scanf("%d", &mesBusca);
    limparBuffer();

    while (mesBusca < 1 || mesBusca > 12) {
        printf("Mês inválido. Digite um número entre 1 e 12: ");
        scanf("%d", &mesBusca);
        limparBuffer();
    }

    int encontrou = 0;
    printf("\n--- Alunos aniversariantes do mês %02d ---\n", mesBusca);

    for (int i = 0; i < qtdAlunos; i++) {
        int mesAniversario;
        sscanf(alunos[i].dataNascimento, "%*d/%d/%*d", &mesAniversario); // pega o mês

        if (mesAniversario == mesBusca) {
           imprimirAluno(alunos[i]);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum aluno faz aniversário no mês %02d.\n", mesBusca);
    }
}

