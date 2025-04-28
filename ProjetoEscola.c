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

    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", dataNascimento);
    limparBuffer();

    printf("Sexo (M/F): ");
    scanf(" %c", sexo); 
    limparBuffer();
    for (int i = 0; nome[i] != '\0'; i++) {
    nome[i] = toupper(nome[i]);
}
   while ((*sexo != 'F') && (*sexo != 'M')) {
    printf("Entrada inválida. Digite 'M' para masculino ou 'F' para feminino: ");
    scanf(" %c", sexo); // CORRETO: sem o &
    limparBuffer();
    *sexo = toupper(*sexo); // CORRETO: altera o conteúdo apontado
}



    printf("CPF (000.000.000-00): ");
    scanf("%s", cpf);
    limparBuffer();
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

// Bloco de funções de Professor

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
    for(int i = 0; i < qtdDisciplinas; i++){  // Desreferenciar qtdDisciplinas com *
        printf("[%d] Nome: %s | Código: %s | Professor: %s\n", i+1, disciplinas[i].nome, disciplinas[i].codigo, disciplinas[i].professor);
    }
    printf("--------------------------------\n");
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

void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas) {
    int escolha;
    do {
        printf("\n===== MENU DE RELATÓRIOS =====\n");
        printf("1. Listar Alunos\n");
        printf("2. Listar Professores\n");
        printf("3. Listar Disciplinas\n");
        printf("4. Listar Disciplinas com Alunos\n");
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
                // ListarAlunos(alunos, qtdAlunos);
                break;
            case 2:
                // ListarProfessores(professores, qtdProfessores);
                break;
            case 3:
                // ListarDisciplinas(disciplinas, qtdDisciplinas);
                break;
            case 4:
                // ListarDisciplinaComAlunos(disciplinas, qtdDisciplinas);
                break;
            case 5:
                // ListarAlunosPorSexo(alunos, qtdAlunos);
                break;
            case 6:
                // ListarAlunosOrdenadosPorNome(alunos, qtdAlunos);
                break;
            case 7:
                // ListarAlunosOrdenadosPorDataNascimento(alunos, qtdAlunos);
                break;
            case 8:
                // ListarProfessoresPorSexo(professores, qtdProfessores);
                break;
            case 9:
                // ListarProfessoresOrdenadosPorNome(professores, qtdProfessores);
                break;
            case 10:
                // ListarProfessoresOrdenadosPorDataNascimento(professores, qtdProfessores);
                break;
            case 11: {
                int mes;
                printf("Digite o mês para ver os aniversariantes: ");
                scanf("%d", &mes);
                // AniversariantesDoMes(alunos, qtdAlunos, mes);
                break;
            }
            case 12: {
                char substring[100];
                printf("Digite a substring a ser buscada no nome: ");
                scanf(" %99[^\n]", substring);  // Lê até 99 caracteres
                // BuscarPessoaPorSubstringNoNome(alunos, qtdAlunos, professores, qtdProfessores, substring);
                break;
            }
            case 13:
                // ListarAlunosComMenosDe3Disciplinas(disciplinas, qtdDisciplinas, alunos, qtdAlunos);
                break;
            case 14:
                // ListarDisciplinasComMaisDe40Alunos(disciplinas, qtdDisciplinas);
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
                CadastrarAluno(alunos, &qtdAlunos);
                break;

            case 2:
                printf("\n--- Modulo Professor ---\n");
                CadastrarProfessor(professores, &qtdProfessores);
                break;

            case 3:
                printf("\n--- Modulo Disciplina ---\n");
                CadastrarDisciplina(disciplinas, &qtdDisciplinas);
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
