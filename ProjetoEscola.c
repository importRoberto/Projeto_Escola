#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX 100
#define MAX_ALUNOS 100

// Estrutura de Aluno
typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11]; // DD/MM/AAAA
    char sexo;
    char cpf[15]; // 000.000.000-00
} Aluno;

// Estrutura de Professor
typedef struct {
    char nome[100];
    int matricula;
    char dataNascimento[11];
    char sexo;
    char cpf[15];
} Professor;

// Estrutura de Disciplina
typedef struct {
    char nome[100];
    char codigo[10];
    int semestre;
    char professor[100];
    int alunosMatriculados[MAX_ALUNOS]; 
    int qtdAlunos;
} Disciplina;

void ToUpperStr(char destino[], const char origem[]) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = toupper(origem[i]);
        i++;
    }
    destino[i] = '\0';
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void PreencherDadosComuns(char nome[], int *matricula, char dataNascimento[], char *sexo, char cpf[]) {
    printf("Nome: ");
    while (getchar() != '\n'); // consome qualquer coisa no buffer
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Matrícula: ");
    scanf("%d", matricula);
    limparBuffer();

	// Data de nascimento
	while (1) {
	    printf("Data de nascimento (DD/MM/AAAA): ");
	    scanf("%s", dataNascimento);
	    limparBuffer();
	
	    // Verifica o formato básico da data: deve ter 10 caracteres no total e '/' nas posições 2 e 5
	    if (strlen(dataNascimento) == 10 &&
	        dataNascimento[2] == '/' &&
	        dataNascimento[5] == '/') {
	        break;
	    } else {
	        printf("Formato inválido. Use o formato DD/MM/AAAA.\n");
	    }
	}
	
	// Sexo
	printf("Sexo (M/F): ");
	scanf(" %c", sexo);
	limparBuffer();
	*sexo = toupper(*sexo);
	
	while ((*sexo != 'F') && (*sexo != 'M')) {
	    printf("Entrada inválida. Digite 'M' para masculino ou 'F' para feminino: ");
	    scanf(" %c", sexo);
	    limparBuffer();
	    *sexo = toupper(*sexo);
	}
	
	// CPF
	while (1) {
	    printf("CPF (000.000.000-00): ");
	    scanf("%s", cpf);
	    limparBuffer();
	
	    // Verifica se tem exatamente 14 caracteres e os pontos e hífen nas posições corretas
	    if (strlen(cpf) == 14 &&
	        cpf[3] == '.' &&
	        cpf[7] == '.' &&
	        cpf[11] == '-') {
	        break;
	    } else {
	        printf("CPF inválido. Use o formato 000.000.000-00.\n");
	    }
	}

}


// Função para cadastrar aluno
void CadastrarAluno(Aluno alunos[], int *qtdAlunos) {
    if (*qtdAlunos >= MAX) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno novo;
    PreencherDadosComuns(novo.nome, &novo.matricula, novo.dataNascimento, &novo.sexo, novo.cpf);
    alunos[*qtdAlunos] = novo;
    (*qtdAlunos)++;

    printf("\nAluno cadastrado com sucesso!\n\n");
}

// Listar alunos
void ListarAlunos(Aluno alunos[], int qtdAlunos) {
    if (qtdAlunos == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtdAlunos; i++) {
        printf("Nome: %s\n", alunos[i].nome);
        printf("Matrícula: %d\n", alunos[i].matricula);
        printf("Data de Nascimento: %s\n", alunos[i].dataNascimento);
        printf("Sexo: %c\n", alunos[i].sexo);
        printf("CPF: %s\n", alunos[i].cpf);
        printf("-----------------------------\n");
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
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matrícula: %d\n", alunos[i].matricula);
            printf("Data de Nascimento: %s\n", alunos[i].dataNascimento);
            printf("Sexo: %c\n", alunos[i].sexo);
            printf("CPF: %s\n", alunos[i].cpf);
            printf("-----------------------------\n");
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
        printf("Nome: %s\n", copia[i].nome);
        printf("Matrícula: %d\n", copia[i].matricula);
        printf("Data de Nascimento: %s\n", copia[i].dataNascimento);
        printf("Sexo: %c\n", copia[i].sexo);
        printf("CPF: %s\n", copia[i].cpf);
        printf("-----------------------------\n");
    }
}

 int CompararDatas(const char *data1, const char *data2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 != ano2)
        return ano1 - ano2;
    if (mes1 != mes2)
        return mes1 - mes2;
    return dia1 - dia2;
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
        printf("Nome: %s\n", copia[i].nome);
        printf("Matrícula: %d\n", copia[i].matricula);
        printf("Data de Nascimento: %s\n", copia[i].dataNascimento);
        printf("Sexo: %c\n", copia[i].sexo);
        printf("CPF: %s\n", copia[i].cpf);
        printf("-----------------------------\n");
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
            printf("[%d] - Nome: %s | Matrícula: %d\n", qtdEncontrados, alunos[i].nome, alunos[i].matricula);
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
    if(scanf("%d", &opcao)==1 && opcao<=0 && opcao >qtdEncontrados){
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
            printf("[%d] Nome: %s | Matrícula: %d\n", qtdEncontrados, alunos[i].nome, alunos[i].matricula);
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
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matrícula: %d\n", alunos[i].matricula);
            printf("Data de Nascimento: %s\n", alunos[i].dataNascimento);
            printf("Sexo: %c\n", alunos[i].sexo);
            printf("CPF: %s\n", alunos[i].cpf);
            printf("-----------------------------\n");
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum aluno faz aniversário no mês %02d.\n", mesBusca);
    }
}

/* Bloco de funções de Professor: Nesse bloco encontrará todas as funções relacionadas
 a professor, função de cadastro, atualização e exclusão.*/

void CadastrarProfessor(Professor professores[], int *qtdProfessores) {
    if (*qtdProfessores >= MAX) {
        printf("Limite de professores atingido.\n");
        return;
    }

    Professor novo;
    PreencherDadosComuns(novo.nome, &novo.matricula, novo.dataNascimento, &novo.sexo, novo.cpf);
    professores[*qtdProfessores] = novo;
    (*qtdProfessores)++;
    printf("\nProfessor cadastrado com sucesso!\n\n");
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
    if(scanf("%d", &opcao)==1 && opcao<=0 && opcao >qtdEncontrados){
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
    limparBuffer();
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
            printf("[%d] Nome: %s | Matrícula: %d\n", qtdEncontrados, professores[i].nome, professores[i].matricula);
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

        //Atualização do nome

        printf("Novo nome (ENTER para manter '%s'):", professores[indiceReal].nome);
        fgets(buffer, sizeof(buffer), stdin);
        if(buffer[0] != '\n'){
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(professores[indiceReal].nome, buffer);
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
                scanf(" %c", novoSexo);
                limparBuffer;
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
        printf("Nome: %s\n", professores[i].nome);
        printf("Matrícula: %d\n", professores[i].matricula);
        printf("Data de Nascimento: %s\n", professores[i].dataNascimento);
        printf("Sexo: %c\n", professores[i].sexo);
        printf("CPF: %s\n", professores[i].cpf);
        printf("-----------------------------\n");

    }
}

void listarProfessorPorNome(Professor professores[], int qtdProfessores){
    if(qtdProfessores==0){
        printf("Não existem professores cadastrados.\n");
        return;
    }

    //Ordena os professores por nome utilizando Bubble Sort
    for(int i=0; i < qtdProfessores -1; i++){
        for(int j = 0; i <qtdProfessores - i - 1 ; j++){
            if(strcmp(professores[j].nome, professores[j +1].nome)>0){
                Professor temp = professores[j];
                professores[j] = professores[j +1];
                professores[j+1] = temp;
            }
        }
    }
    
    printf("\n--- Lista de professores ordenada em ordem alfabética ---\n");
    for(int i =0; i <qtdProfessores; i++){
        printf("Nome: %s\n", professores[i].nome);
        printf("Matrícula: %d\n", professores[i].matricula);
        printf("Data de Nascimento: %s\n", professores[i].dataNascimento);
        printf("Sexo: %c\n", professores[i].sexo);
        printf("CPF: %s\n", professores[i].cpf);
    }
    printf("-----------------------------\n");
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
            printf("Nome: %s\n", professores[i].nome);
            printf("Matrícula: %d\n", professores[i].matricula);
            printf("Data de Nascimento: %s\n", professores[i].dataNascimento);
            printf("Sexo: %c\n", professores[i].sexo);
            printf("CPF: %s\n", professores[i].cpf);
            printf("-----------------------------\n");
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum professor do sexo %c encontrado.\n", sexoFiltro);
    }
}

int CompararDatasProf(const char *data1, const char *data2) {
    int dia1, mes1, ano1, dia2, mes2, ano2;
    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
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
            if (CompararDatasProf(copia[j].dataNascimento, copia[j + 1].dataNascimento) > 0) {
                Professor temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }

    printf("\n--- Professores por data de nascimento ---\n");
    for (int i = 0; i < qtdProfessores; i++) {
        printf("Nome: %s\n", copia[i].nome);
        printf("Matrícula: %d\n", copia[i].matricula);
        printf("Data de Nascimento: %s\n", copia[i].dataNascimento);
        printf("Sexo: %c\n", copia[i].sexo);
        printf("CPF: %s\n", copia[i].cpf);
        printf("-----------------------------\n");
    }
}

#include <string.h>
#include <ctype.h>

// Função auxiliar para transformar uma string em minúsculas
void toLowerStr(char *destino, const char *origem) {
    while (*origem) {
        *destino = tolower((unsigned char)*origem);
        destino++;
        origem++;
    }
    *destino = '\0';
}

void BuscarPessoaPorNome(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, const char *termoBusca) {
    char termoBuscaLower[100];
    toLowerStr(termoBuscaLower, termoBusca);

    int encontrou = 0;

    // Buscar em alunos
    for (int i = 0; i < qtdAlunos; i++) {
        char nomeLower[100];
        toLowerStr(nomeLower, alunos[i].nome);

        if (strstr(nomeLower, termoBuscaLower)) {
            printf("\n[Aluno]\n");
            printf("Nome: %s\n", alunos[i].nome);
            printf("Matrícula: %d\n", alunos[i].matricula);
            printf("Data de nascimento: %s\n", alunos[i].dataNascimento);
            printf("Sexo: %c\n", alunos[i].sexo);
            printf("CPF: %s\n", alunos[i].cpf);
            encontrou = 1;
        }
    }

    // Buscar em professores
    for (int i = 0; i < qtdProfessores; i++) {
        char nomeLower[100];
        toLowerStr(nomeLower, professores[i].nome);

        if (strstr(nomeLower, termoBuscaLower)) {
            printf("\n[Professor]\n");
            printf("Nome: %s\n", professores[i].nome);
            printf("Matrícula: %d\n", professores[i].matricula);
            printf("Data de nascimento: %s\n", professores[i].dataNascimento);
            printf("Sexo: %c\n", professores[i].sexo);
            printf("CPF: %s\n", professores[i].cpf);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum aluno ou professor encontrado com o nome contendo \"%s\".\n", termoBusca);
    }
}


//Bloco funções disciplina
void CadastrarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas) {
    if (*qtdDisciplinas >= MAX) {
        printf("Limite de disciplinas atingido.\n");
        return;
    }

    Disciplina nova;
    printf("Nome da disciplina: ");
    limparBuffer();
    fgets(nova.nome, 100, stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0';

    printf("Código da disciplina: ");
    scanf("%s", nova.codigo);

    printf("Semestre: ");
    scanf("%d", &nova.semestre);

    printf("Nome do professor responsável: ");
    limparBuffer();
    fgets(nova.professor, 100, stdin);
    nova.professor[strcspn(nova.professor, "\n")] = '\0';

    nova.qtdAlunos = 0;
    disciplinas[*qtdDisciplinas] = nova;
    (*qtdDisciplinas)++;
    printf("\nDisciplina cadastrada com sucesso!\n\n");
}

void listarTodasDisciplinas(Disciplina disciplinas[], int qtdDisciplinas){
    printf("\n--- Lista de Disciplinas ---\n");
    for(int i = 0; i < qtdDisciplinas; i++){  
        printf("[%d] Nome: %s | Código: %s | Professor: %s\n", i+1, disciplinas[i].nome, disciplinas[i].codigo, disciplinas[i].professor);
    }
    printf("--------------------------------\n");
}


void listarDisciplinasMais40(Disciplina disciplinas[], int qtdDisciplinas){
    int encontrou = 0;
    printf("\n--- Lista de Disciplinas com mais de 40 alunos ---\n");
    for(int i =0; i < qtdDisciplinas; i++){
        if(disciplinas[i].qtdAlunos>40){
        printf("[%d] Nome: %s | Código: %s | Professor: %s\n", i+1, disciplinas[i].nome, disciplinas[i].codigo, disciplinas[i].professor);
        encontrou = 1;
    }
}
    if (!encontrou){
        printf("Nenuma disciplina com mais de 40 alunos cadastrados.");

    }
    printf("--------------------------------\n");
}

void ListarAlunosMenosDeTresDisciplinas(Aluno alunos[], int qtdAlunos, Disciplina disciplinas[], int qtdDisciplinas) {
    int matriculas[MAX_ALUNOS] = {0};  // Array para contar quantas disciplinas cada aluno está matriculado

    // Percorrer todas as disciplinas
    for (int i = 0; i < qtdDisciplinas; i++) {
        for (int j = 0; j < disciplinas[i].qtdAlunos; j++) {
            int matriculaAluno = disciplinas[i].alunosMatriculados[j];
            
            // Contar a matrícula do aluno nas disciplinas
            for (int k = 0; k < qtdAlunos; k++) {
                if (alunos[k].matricula == matriculaAluno) {
                    matriculas[k]++;  // Incrementa o contador para o aluno
                    break;
                }
            }
        }
    }

    // Exibir os alunos matriculados em menos de 3 disciplinas
    printf("\nAlunos matriculados em menos de 3 disciplinas:\n");
    int encontrado = 0;
    for (int i = 0; i < qtdAlunos; i++) {
        if (matriculas[i] < 3) {
            printf("\nNome: %s\n", alunos[i].nome);
            printf("Matrícula: %d\n", alunos[i].matricula);
            printf("Data de nascimento: %s\n", alunos[i].dataNascimento);
            printf("Sexo: %c\n", alunos[i].sexo);
            printf("CPF: %s\n", alunos[i].cpf);
            printf("Número de disciplinas matriculadas: %d\n", matriculas[i]);
            printf("-----------------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum aluno matriculado em menos de 3 disciplinas.\n");
    }
}

void MatricularAlunoEmDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos) {
    char codigoBusca[10];
    int matriculaBusca, encontrado = 0;

    printf("Digite o código da disciplina: ");
    scanf("%s", codigoBusca);

    for (int i = 0; i < qtdDisciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoBusca) == 0) {
            encontrado = 1;

            if (disciplinas[i].qtdAlunos >= MAX_ALUNOS) {
                printf("Limite de alunos nesta disciplina atingido.\n");
                return;
            }

            printf("Digite a matrícula do aluno: ");
            scanf("%d", &matriculaBusca);

            int alunoExiste = 0;
            for (int j = 0; j < qtdAlunos; j++) {
                if (alunos[j].matricula == matriculaBusca) {
                    alunoExiste = 1;
                    break;
                }
            }

            if (!alunoExiste) {
                printf("Aluno não encontrado.\n");
                return;
            }

            disciplinas[i].alunosMatriculados[disciplinas[i].qtdAlunos] = matriculaBusca;
            disciplinas[i].qtdAlunos++;
            printf("Aluno matriculado com sucesso!\n");
            return;
        }
    }

    if (!encontrado) {
        printf("Disciplina não encontrada.\n");
    }
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
            printf("Semestre: %d\n", disciplinas[i].semestre);
            printf("Professor: %s\n", disciplinas[i].professor);
            printf("Quantidade de Alunos Matriculados: %d\n", disciplinas[i].qtdAlunos);

            // Listando os alunos matriculados
            printf("\n--- Alunos Matriculados ---\n");

            if (disciplinas[i].qtdAlunos == 0) {
                printf("Nenhum aluno matriculado nesta disciplina.\n");
            } else {
                for (int j = 0; j < disciplinas[i].qtdAlunos; j++) {
                    int matriculaAluno = disciplinas[i].alunosMatriculados[j];

                    // Procurar aluno no vetor de alunos
                    for (int k = 0; k < qtdAlunos; k++) {
                        if (alunos[k].matricula == matriculaAluno) {
                            printf("Nome: %s\n", alunos[k].nome);
                            printf("Matrícula: %d\n", alunos[k].matricula);
                            printf("Data de Nascimento: %s\n", alunos[k].dataNascimento);
                            printf("Sexo: %c\n", alunos[k].sexo);
                            printf("CPF: %s\n", alunos[k].cpf);
                            printf("---------------------------\n");
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


void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas) {
    int escolha;
    do {
        printf("\n===== MENU DE RELATÓRIOS =====\n");
        printf("1. Listar Alunos\n");
        printf("2. Listar Professores\n");
        printf("3. Listar Disciplinas\n");
        printf("4. Listar disciplina especifica com dados dos Alunos\n");
        printf("5. Listar Alunos por Sexo\n");
        printf("6. Listar Alunos Ordenados por Nome\n");
        printf("7. Listar Alunos Ordenados por Data de Nascimento\n");
        printf("8. Listar Professores por Sexo\n");
        printf("9. Listar Professores Ordenados por Nome\n");
        printf("10. Listar Professores Ordenados por Data de Nascimento\n");
        printf("11. Aniversariantes do Mês\n");
        printf("12. Buscar Pessoa por Substring no Nome\n");
        printf("13. Listar Alunos com Menos de 3 Disciplinas\n");
        printf("14. Listar Disciplinas com Mais de 40 Alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        
        switch (escolha) {
            case 1:
                ListarAlunos(alunos, qtdAlunos);
                break;
            case 2:
                listarTodosProfessores(professores, qtdProfessores);
                break;
            case 3:
                listarTodasDisciplinas(disciplinas, qtdDisciplinas);
                break;
            case 4:
                ListarUmaDisciplina(disciplinas, qtdDisciplinas, alunos, qtdAlunos);
                break;
            case 5:
                ListarAlunosPorSexo(alunos, qtdAlunos);
                break;
            case 6:
                ListarAlunosOrdenadosPorNome(alunos, qtdAlunos);
                break;
            case 7:
                ListarAlunosPorDataNascimento(alunos, qtdAlunos);
                break;
            case 8:
                ListarProfessoresPorSexo(professores, qtdProfessores); 
                break;
            case 9:
                listarProfessorPorNome(professores, qtdProfessores);
                break;
            case 10:
                ListarProfessoresPorDataNascimento(professores, qtdProfessores);
                break;
            case 11: {
                ListarAniversariantesDoMes(alunos, qtdAlunos);
                break;
            }
            case 12: {
               char busca[100];
				printf("Digite parte do nome a buscar: ");
				limparBuffer();  // sua função para limpar o buffer de entrada
				fgets(busca, sizeof(busca), stdin);
				busca[strcspn(busca, "\n")] = '\0';

				BuscarPessoaPorNome(alunos, qtdAlunos, professores, qtdProfessores, busca);
            }
            case 13:
                ListarAlunosMenosDeTresDisciplinas(alunos, qtdAlunos, disciplinas, qtdDisciplinas);
                break;
            case 14:
                listarDisciplinasMais40(disciplinas, qtdDisciplinas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (escolha != 0);  // Fechamento do do-while
}

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
				int opc;
				printf("Desejas:\n[1] Cadastrar\n[2] Atualizar\n[3] Remover\n");
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
				else {
				    printf("Opção inválida.\n");
				}

                
                break;

            case 2:
                printf("\n--- Módulo Professor ---\n");
				printf("Deseja:\n[1] Cadastrar\n[2] Atualizar\n[3] Remover\n");
				printf("Digite a opção: ");
				scanf("%d", &opc);
				limparBuffer();  // Se essa função estiver definida no seu código
				
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
				printf("Deseja:\n[1] Cadastrar\n[2] Remover\n");
				printf("Digite a opção: ");
				scanf("%d", &opc);
				limparBuffer();
				
				if (opc == 1) {
				    CadastrarDisciplina(disciplinas, &qtdDisciplinas);
				}
				else if (opc == 2) {
				    removerDisciplina(disciplinas, &qtdDisciplinas);
				}
				else {
				    printf("Opção inválida.\n");
				}

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
