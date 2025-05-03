#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "alunos.h"
#include "utilitarios.h"
#include "professores.h"

/*---------------------------------------------------------
  BLOCO DE FUNÇÕES UTILITÁRIAS
  Funções genéricas usadas em múltiplos módulos do sistema
-----------------------------------------------------------*/




#define prefixo_Professor "2025117"
#define prefixo_Aluno "2025106"

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


void PreencherDadosComuns(char nome[], char matricula[], char dataNascimento[], char *sexo, char cpf[], int tipo) {
    char nomeOriginal[100];
    
    // Validação do nome
    while (1) {
        printf("Nome: ");
        fgets(nomeOriginal, sizeof(nomeOriginal), stdin);
        nomeOriginal[strcspn(nomeOriginal, "\n")] = '\0'; // Remove o '\n'

        int valido = 1;
        for (int i = 0; nomeOriginal[i] != '\0'; i++) {
            if (!isalpha(nomeOriginal[i]) && nomeOriginal[i] != ' ' && nomeOriginal[i] != '\'') {
                valido = 0;
                break;
            }
        }

        if (valido && strlen(nomeOriginal) > 0) { // Verifica se o nome não está vazio
            ToUpperStr(nome, nomeOriginal); // Converte para maiúsculas
            break;
        } else {
            printf("Nome inválido. Use apenas letras, espaços ou apóstrofos.\n");
        }
    }

    if (tipo == 1) {
        gerarMatriculaAluno(matricula);
    } else if (tipo == 2) {
        gerarMatriculaProfessor(matricula);
    }

    // Data de nascimento
    while (1) {
        printf("Data de nascimento (DD/MM/AAAA): ");
        scanf("%s", dataNascimento);
        limparBuffer();

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