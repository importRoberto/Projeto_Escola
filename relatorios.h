#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "professores.h"
#include "alunos.h"
#include "utilitarios.h"
#include "disciplinas.h"




void MenuRelatoriosAlunos(Aluno alunos[], int qtdAlunos);

void MenuRelatoriosProfessores(Professor professores[], int qtdProfessores);

void MenuRelatoriosDisciplinas(Disciplina disciplinas[], int qtdDisciplinas, Aluno alunos[], int qtdAlunos);

void ExibirMenuRelatorios(Aluno alunos[], int qtdAlunos, Professor professores[], int qtdProfessores, Disciplina disciplinas[], int qtdDisciplinas);

#endif
