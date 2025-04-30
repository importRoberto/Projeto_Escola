#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX 100
#define MAX_ALUNOS 100

#define prefixo_Professor "2025117"
#define prefixo_Aluno "2025106"


void gerarMatriculaAluno(char* matricula);
void gerarMatriculaProfessor(char* matricula);

// Estrutura de Aluno
typedef struct {
    char nome[100];
    char matricula[15];
    char dataNascimento[11]; // DD/MM/AAAA
    char sexo;
    char cpf[15]; // 000.000.000-00
} Aluno;

// Estrutura de Professor
typedef struct {
    char nome[100];
    char matricula[15];
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
    char matriculasAlunos[MAX_ALUNOS][10]; // Armazena as matrículas dos alunos matriculados
    int capacidadeMaxima; 
    int qtdAlunos; // Quantidade atual de alunos matriculados
} Disciplina;


/*---------------------------------------------------------
  BLOCO DE FUNÇÕES UTILITÁRIAS
  Funções genéricas usadas em múltiplos módulos do sistema
-----------------------------------------------------------*/
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


void imprimirProfessor(Professor p) {
    printf("Nome: %s\n", p.nome);
    printf("Matrícula: %s\n", p.matricula);
    printf("Data de Nascimento: %s\n", p.dataNascimento);
    printf("Sexo: %c\n", p.sexo);
    printf("CPF: %s\n", p.cpf);
    printf("-----------------------------\n");
}

void imprimirAluno(Aluno a) {
    printf("Nome: %s\n", a.nome);
    printf("Matrícula: %s\n", a.matricula);
    printf("Data de Nascimento: %s\n", a.dataNascimento);
    printf("Sexo: %c\n", a.sexo);
    printf("CPF: %s\n", a.cpf);
    printf("-----------------------------\n");
}

int contadorAluno = 0;
int contadorProfessor = 0;

void gerarMatriculaAluno(char matricula[]) {
    if (contadorAluno >= 9999) {
        printf("Erro: Limite de matrículas atingido para alunos.\n");
        return;
    }
    // Formato: prefixo (7 caracteres) + 4 dígitos = 11 caracteres + '\0'
    snprintf(matricula, 15, "%s%04d", prefixo_Aluno, contadorAluno + 1);
    contadorAluno++;
}
  
  // Função para gerar a matrícula para professor
  void gerarMatriculaProfessor(char matricula[]) {
    if (contadorProfessor >= 9999) {
      printf("Erro: Limite de matrículas atingido para professores.\n");
      return;
    }

    snprintf(matricula, 15, "%s%04d", prefixo_Professor, contadorProfessor + 1);
    contadorProfessor++;
  }


void PreencherDadosComuns(char nome[], char matricula[], char dataNascimento[], char *sexo, char cpf[],int tipo) {
    char nomeOriginal[100];
    printf("Nome: ");
    fgets(nomeOriginal, 100, stdin);
    nomeOriginal[strcspn(nomeOriginal, "\n")] = '\0';
    ToUpperStr(nome, nomeOriginal);

    if(tipo==1){
        gerarMatriculaAluno(matricula);
    }else if(tipo==2){
        gerarMatriculaProfessor(matricula);
    }

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

// Fim do bloco de funções utilitárias.

/*---------------------------------------------------------
  BLOCO DE FUNÇÕES DE ALUNO
  Operações CRUD (Criar, Ler, Atualizar, Excluir) para alunos
  Inclui listagens especiais e validações
-----------------------------------------------------------*/

// Função para cadastrar aluno
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

/*---------------------------------------------------------
  BLOCO DE FUNÇÕES DE DISCIPLINA
  Gerencia disciplinas com controle de capacidade
  Valida relações com professores e alunos matriculados
-----------------------------------------------------------*/
//Bloco funções disciplina
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
    scanf("%d", &nova.semestre);
    limparBuffer();

    printf("Capacidade máxima de alunos: ");
    scanf("%d", &nova.capacidadeMaxima);
    limparBuffer();

    // Validação do professor (com case-insensitive)
    do {
        printf("Nome do professor responsável: ");
        fgets(nomeProfessor, 100, stdin);
        nomeProfessor[strcspn(nomeProfessor, "\n")] = '\0';

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
            printf("\nProfessor não cadastrado! Professores disponíveis:\n");
            
            if(qtdProfessores == 0) {
                printf("Nenhum professor cadastrado!\n");
                printf("Disciplina não pode ser cadastrada sem professor válido.\n");
                return;
            }
            
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
    printf("Novo semestre (ENTER para manter %d): ", d->semestre);
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[0] != '\n') {
        sscanf(buffer, "%d", &d->semestre);
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
            printf("Semestre: %d\n", disciplinas[i].semestre);
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
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: listarTodasDisciplinas(disciplinas, qtdDisciplinas); break;
            case 2: listarDisciplinasMais40(disciplinas, qtdDisciplinas); break;
            case 3: ListarUmaDisciplina(disciplinas, qtdDisciplinas, alunos, qtdAlunos); break;
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
