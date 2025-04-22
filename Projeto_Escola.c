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

void ListarAlunos(Aluno alunos[], int qtdAlunos);

//Função para converter para maiúsculos
void ToUpperStr(char destino[], const char origem[]) {
    int i = 0;
    while (origem[i] != '\0') {
        destino[i] = toupper(origem[i]);
        i++;
    }
    destino[i] = '\0';
}
//Limpeza de buffer após utilizar scanf
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// Função auxiliar para preencher dados comuns
void PreencherDadosComuns(char nome[], int *matricula, char dataNascimento[], char *sexo, char cpf[]) {
    printf("Nome: ");
    while (getchar() != '\n'); // consome qualquer coisa no buffer
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Matricula: ");
    scanf("%d", matricula);

    printf("Data de nascimento (DD/MM/AAAA): ");
    scanf("%s", dataNascimento);

    printf("Sexo (M/F): ");
    scanf(" %c", sexo); 

    printf("CPF (000.000.000-00): ");
    scanf("%s", cpf);
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

// Função para cadastrar professor
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

// Função para cadastrar disciplina
void CadastrarDisciplina(Disciplina disciplinas[], int *qtdDisciplinas) {
    if (*qtdDisciplinas >= MAX) {
        printf("Limite de disciplinas atingido.\n");
        return;
    }

    Disciplina nova;

    printf("Nome da disciplina: ");
    getchar(); 
    fgets(nova.nome, 100, stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0';

    printf("Código da disciplina: ");
    scanf("%s", nova.codigo);

    printf("Semestre: ");
    scanf("%d", &nova.semestre);

    printf("Nome do professor responsável: ");
    getchar(); 
    fgets(nova.professor, 100, stdin);
    nova.professor[strcspn(nova.professor, "\n")] = '\0';

    nova.qtdAlunos = 0;

    disciplinas[*qtdDisciplinas] = nova;
    (*qtdDisciplinas)++;

    printf("\nDisciplina cadastrada com sucesso!\n\n");
}

void MatricularAlunoEmDisciplina(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos) {
    char codigoBusca[10];
    int matriculaBusca;
    int encontrado = 0;

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

            // Verificar se aluno existe
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

            // Matricular aluno
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
//Função para remover aluno

void removerAluno(Aluno alunos[], int *qtdAlunos){
    if(*qtdAlunos ==0){
        printf("Não há alunos cadastrados.\n");
        return;
    }

    char busca[100];
    printf("Digte o nome(ou parte) para buscar o aluno:");
    limparBuffer();
    fgets(busca, sizeof(busca),stdin);
    busca[strcspn(busca, "\n")] = '\0';

    char buscaUpper[100];
    ToUpperStr(buscaUpper, busca);

    int encontrados[MAX];
    int qtdEnconstrados =0 ;
    
    for(int i =0; i<*qtdAlunos; i++){
        char nomeUpper[100];
        ToUpperStr(nomeUpper, alunos[i].nome);

        if(strstr(nomeUpper, buscaUpper) != NULL){
            printf("[%d]-Nome: %s | Matrícula: %d\n", qtdEnconstrados, alunos[i].nome, alunos[i].matricula);
            encontrados[qtdEnconstrados] = i ;
            qtdEnconstrados++;
        }
    }

    if(qtdEnconstrados == 0){
        printf("Nenhum aluno encontrado com o nome informado.\n");
        return;
    }

    int opcao;
    printf("Digite o índice do aluno que deseja remover:");
    scanf("%d", &opcao);
    limparBuffer();

    if(opcao<0 || opcao>=qtdEnconstrados){
        printf("Índice inválido.\n");
        return;
    }

    int indiceReal = enconstrados[indiceEscolhido];

    char confirmacao; 
    printf("Tem certeza que deseja remover o aluno %s? (S/N)");
    scanf(" %c", &confirmacao);
    limparBuffer();
    
    if(confirmacao == 'S' || confirmacao =='s'){
        for(int i = indiceReal; i < *qtdAlunos -1; i++){
            alunos[i]= alunos[i+1];
        }
        (*qtdAlunos)--;
        printf("Aluno removido com sucesso!\n");
    }else{
        printf("Remoção cancelada.\n");
    }
}
//Função para listar os alunos cadastrados
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

//Função para menu de relatorios
void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas) {
    int opcaoRelatorio;

    do {
        printf("\n--- Relatórios ---\n");
        printf("1 - Listar Alunos\n");
        printf("2 - Listar Professores\n");
        printf("3 - Listar Disciplinas (sem alunos)\n");
        printf("4 - Listar uma Disciplina (com alunos)\n");
        printf("5 - Listar Alunos por sexo\n");
        printf("6 - Listar Alunos ordenados por nome\n");
        printf("7 - Listar Alunos ordenados por data de nascimento\n");
        printf("8 - Listar Professores por sexo\n");
        printf("9 - Listar Professores ordenados por nome\n");
        printf("10 - Listar Professores ordenados por data de nascimento\n");
        printf("11 - Aniversariantes do mês\n");
        printf("12 - Buscar pessoa por substring no nome\n");
        printf("13 - Alunos com menos de 3 disciplinas\n");
        printf("14 - Disciplinas com mais de 40 alunos\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoRelatorio);
        getchar();

        switch(opcaoRelatorio) {
            case 1:
                ListarAlunos(alunos, qtdAlunos);
                break;
            case 2:
                // ListarProfessores(...);
                break;
            case 3:
                // ListarDisciplinas(...);
                break;
            case 4:
                // ListarDisciplinaComAlunos(...);
                break;
            case 5:
                // ListarAlunosPorSexo(...);
                break;
            // e assim por diante...
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while(opcaoRelatorio != 0);
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

            default:
                printf("Opcao Invalida\n");
                break;
        }
    }

    return 0;
}
