#ifndef UTILITARIOS_H
#define UTILITARIOS_H

#include "professores.h"  // Adicione esta linha
#include "alunos.h"

void ToUpperStr(char destino[], const char origem[]);

void limparBuffer();

void imprimirProfessor(Professor p);

void imprimirAluno(Aluno a);

void gerarMatriculaAluno(char matricula[]);

void gerarMatriculaProfessor(char matricula[]);

void PreencherDadosComuns(char nome[], char matricula[], char dataNascimento[], char *sexo, char cpf[], int tipo);

int CompararDatas(const char *data1, const char *data2);

void ListarAniversariantesDoMes(Aluno alunos[], int qtdAlunos);

void BuscarPessoaPorNome(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, const char *termoBusca);

#endif