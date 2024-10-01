#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define TF 100

struct _Aluno {
	char ra[10];
	char nome[30];
};

struct _Disc {
	int cod;
	char nome[30];
};

struct _Nota {
	char ra[10];
	int cod;
	float nota;
};

//busca, cadastro, exclusão e alteração de alunos

int BuscaAluno(_Aluno aluno[], char auxRa[10], int TL) {
	int pos=0;
	
	while(pos<TL && strcmp(aluno[pos].ra, auxRa)!=0)
		pos++;
		
	if(pos==TL)
		return -1;
	else
		return pos;
}

void CadastroAluno(_Aluno aluno[], int &TL) {
	char auxRa[30];
	
	system("cls");
	printf("\n### CADASTRO DE ALUNOS ###\n");
	printf("\nInsira o RA do aluno: ");
	fflush(stdin);
	gets(auxRa);
	
	while(TL<TF && strcmp(auxRa, "\0")!=0) {
		if (BuscaAluno(aluno, auxRa, TL) < 0) {
			strcpy(aluno[TL].ra, auxRa);
			printf("\nInsira o nome do aluno: ");
			fflush(stdin);
			gets(aluno[TL].nome);
			
			printf("\n Aluno: %s CADASTRADO COM SUCESSO!\n", aluno[TL++].nome);
			getch();
		}
		else {
			printf("\n*** ALUNO JA CADASTRADO ***\n");
			getch();
		}
		
		system("cls");
		printf("\nInsira o RA do aluno: ");
		fflush(stdin);
		gets(auxRa);
	}
	
	printf("\n### CADASTRO FINALIZADO ###\n");
	getch();
}

//busca, cadastro, exclusão e alteração de disciplinas

int BuscaDisciplina(_Disc disc[], int auxCodDisc, int TL) {
	int pos = 0;
	
	while (pos<TL && disc[pos].cod != auxCodDisc)
		pos++;
	
	if (pos == TL)
		return -1;
	else
		return pos;
}

void CadastroDisciplina(_Disc disc[], int &TL) {
	int auxCodDisc;
	
	system("cls");
	printf("\n### CADASTRO DE DISCIPLINAS ###\n");
	printf("\nInsira o codigo da disciplina ou 0 para sair: ");
	scanf("%d", &auxCodDisc);
	
	while (TL<TF && auxCodDisc != 0) {
		if (BuscaDisciplina(disc, auxCodDisc, TL) < 0) {
			disc[TL].cod = auxCodDisc;
			printf("\nInsira o nome da disciplina: ");
			fflush(stdin);
			gets(disc[TL].nome);
			
			printf("\nDisciplina %s cadastrada com sucesso!\n", disc[TL++].nome);
			getch();
		}
		else {
			printf("\n*** DISCIPLINA JA CADASTRADA ***\n");
			getch();
		}
		
		system("cls");
		printf("\nInsira o codigo da disciplina ou 0 para sair: ");
		scanf("%d", &auxCodDisc);
	}
	
	printf("\n### CADASTRO FINALIZADO ###\n");
	getch();
}

//busca, cadastro, exclusão e alteração de notas

int BuscaNota(_Nota nota[], char auxRa[10], int auxCodDisc, int TL) {
	int pos=0;
	
	while (pos<TL && (strcmp(nota[pos].ra, auxRa)!=0 || nota[pos].cod != auxCodDisc))
		pos++;
		
	if(pos == TL)
		return -1;
	else
		return pos;
}

void CadastroNota(_Nota nota[], _Aluno aluno[], _Disc disc[], int TLA, int TLD, int &TL) {
	int auxCodDisc, posAluno, posDisc;
	char auxRa[10];
	
	system("cls");
	printf("\n### CADASTRO DE NOTAS ###\n");
	printf("\nInsira o RA do aluno: ");
	fflush(stdin);
	gets(auxRa);
	
	while (TL<TF && strcmp(auxRa, "\0")!=0) {
		posAluno = BuscaAluno(aluno, auxRa, TLA);
		
		if (posAluno >= 0) {
			printf("\nInsira o codigo da disciplina: ");
			scanf("%d", &auxCodDisc);
			posDisc = BuscaDisciplina(disc, auxCodDisc, TLD);
			
			if(posDisc >= 0) {
				if (BuscaNota(nota, auxRa, auxCodDisc, TL) < 0) {
					strcpy(nota[TL].ra, auxRa);
					nota[TL].cod = auxCodDisc;
					printf("\nInsira a nota do aluno: ");
					scanf("%f", &nota[TL].nota);
					
					printf("\nAluno \t Disciplina \t Nota\n %s \t %s \t\t %.2f\n", aluno[posAluno].nome, disc[posDisc].nome, nota[TL++].nota);
					getch();
				}
				else {
					printf("\n*** NOTA JA CADASTRADA ***");
					getch();
				}
			}
			else {
				printf("\n*** CODIGO DA DISCIPLINA NAO ECONTRADO ***");
				getch();
			}
		}
		else {
			printf("\n*** RA NAO ENCONTRADO ***\n");
			getch();
		}
		
		system("cls");
		printf("\nInsira o RA do aluno: ");
		fflush(stdin);
		gets(auxRa);
	}
	
	printf("\n### CADASTRO FINALIZADO ###\n");
	getch();
}

void ExcluiNota(_Nota nota[], _Aluno aluno[], _Disc disc[], int TLA, int TLD, int &TL) {
	char auxRa[10], op;
	int auxCodDisc, posAluno, posDisc, posNota;
	
	system("cls");
	printf("\n### EXCLUIR NOTA ###\n");
	printf("\nInsira o RA do aluno: ");
	fflush(stdin);
	gets(auxRa);
	
	while(TL > 0 && strcmp(auxRa, "\0")!=0) {
		posAluno = BuscaAluno(aluno, auxRa, TLA);
		
		if(posAluno >= 0) {
			printf("\nInsira o codigo da disciplina: ");
			scanf("%d", &auxCodDisc);
			posDisc = BuscaDisciplina(disc, auxCodDisc, TLD);
			
			if (posDisc >= 0) {
				posNota = BuscaNota(nota, auxRa, auxCodDisc, TL);
				
				if(posNota >= 0) {
					printf("\nAluno \t Disciplina \t Nota\n %s \t %s \t\t %.2f\n", aluno[posAluno].nome, disc[posDisc].nome, nota[posNota].nota);
					printf("\nDeseja Excluir? ( S/N )\n");
					op = toupper(getche());
										
					if (op == 'S') {
						for (int i = posNota; i < TL-1;i++) {
							nota[i] = nota[i+1];
						}
						TL--;
						
						printf("\n### NOTA EXCLUIDA COM SUCESSO! ###");
						getch();
					}
					else
						if(op == 'N') {
							printf("\nPressione qualquer tecla para voltar...");
							getch();
					}
				}
				else {
					printf("\n*** NOTA NAO ENCONTRADA ***\n");
					getch();	
				}
			}
			else {
				printf("\n*** DISCIPLINA NAO ENCONTRADA ***\n");
				getch();
			}
		}
		else {
			printf("\n*** RA NAO ENCONTRADO ***\n");
			getch();	
		}
		
		system("cls");
		printf("\nInsira o RA do aluno: ");
		fflush(stdin);
		gets(auxRa);
	}
}

int main(void) {
	_Aluno aluno[TF];
	_Disc disc[TF];
	_Nota nota[TF];
	int TLA=0, TLD=0, TLN=0;
	
	CadastroAluno(aluno, TLA);
	CadastroDisciplina(disc, TLD);
	CadastroNota(nota, aluno, disc, TLA, TLD, TLN);
	
	ExcluiNota(nota, aluno, disc, TLA, TLD, TLN);
	
	return 0;
}
