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

int BuscaAlunoEmNotas(char ra[], _Nota nota[], int TLN) {
	int pos = 0;
	
	while(pos < TLN && strcmp(ra, nota[pos].ra)!=0)
		pos++;
		
	if(pos == TLN)
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

void ExcluiAluno(_Aluno aluno[], _Nota nota[], int &TL, int TLN) {
	char auxRa[10];
	int posNota, posAluno;
	
	system("cls");
	printf("\n### EXCLUSAO DE ALUNOS ###\n");
	printf("\nInsira o RA do aluno que deseja excluir: ");
	fflush(stdin);
	gets(auxRa);
	
	while(TL > 0 && strcmp(auxRa, "\0")!=0) {
		posNota = BuscaAlunoEmNotas(auxRa, nota, TLN);
		posAluno = BuscaAluno(aluno, auxRa, TL);
		
		if (posAluno >= 0) {
			if (posNota < 0) {
				system("cls");
				printf("Nome\t\t\tRA\n");
				printf("%s\t\t\t%s", aluno[posAluno].nome, aluno[posAluno].ra);
				printf("\nDeseja excluir este aluno? (S/N) ");
				int op = toupper(getche());
				
				if(op == 'S') {
					for(int i=posAluno; i < TL-1; i++)
						aluno[i] = aluno[i+1];
					TL--;
				
					system("cls");	
					printf("\n*** ALUNO EXCLUIDO COM SUCESSO ***\n");
					getch();	
				}
				else {
					printf("\nPressione qualquer tecla para voltar...");
					getch();
				}
			}
			else {
				system("cls");
				printf("\n*** ALUNO COM CADASTROS FEITOS EM NOTAS: ***\n");
				printf("\nPara excluir o aluno %s necessario a exclusao das notas!\n", aluno[posAluno].nome);
				printf("\nPressione qualquer tecla para voltar...");
				getch();
			}	
		}
		else {
			system("cls");
			printf("\n*** ALUNO NAO ENCONTRADO ***\n");
			getch();
		}
		
		system("cls");
		printf("\nInsira o RA do aluno que deseja excluir: ");
		fflush(stdin);
		gets(auxRa);	
	}
}

void AlteraAluno(_Aluno aluno[], _Nota nota[], int TL, int TLN) {
	char auxRa[10];
	int posAluno, posNota;
	
	system("cls");
	printf("\n### ALTERAR ALUNOS ###\n");
	printf("\nInsira o RA do aluno: ");
	fflush(stdin);
	gets(auxRa);
	
	while (strcmp(auxRa, "\0")!=0) {
		posAluno = BuscaAluno(aluno, auxRa, TL);
		posNota = BuscaAlunoEmNotas(auxRa, nota, TLN);
		
		if (posAluno >= 0) {
				system("cls");
				printf("\nNome: %s\tRA: %s\n", aluno[posAluno].nome, aluno[posAluno].ra);
				printf("%d", posNota);	
				printf("\nOque deseja alterar?\n A - RA\n B - Nome\n C - Voltar\n");
				int op = toupper(getche());
				
				switch(op) {
					case 'A':
						if (posNota < 0) {
							system("cls");
							printf("\nInsira o novo RA: ");
							fflush(stdin);
							gets(aluno[posAluno].ra);
							
							printf("\nNovo RA: %s", aluno[posAluno].ra);
							getch();
						}
						else {
							system("cls");
							printf("\n*** ALUNO COM CADASTROS FEITOS EM NOTAS: ***\n");
							printf("\nDeseja alterar o cadastro do aluno nas notas? (S/N) : \n", aluno[posAluno].nome);
							int opAlt = toupper(getche());
							
							if (opAlt == 'S') {
								char auxAltRa[10];
								system("cls");
								printf("\nInsira o novo RA: ");
								fflush(stdin);
								gets(auxAltRa);
								
								strcpy(aluno[posAluno].ra, auxAltRa);
								strcpy(nota[posNota].ra, auxAltRa);
								
								printf("\nNovo RA: %s\n", aluno[posAluno].ra);
							}
						}
						printf("\nPressione qualquer tecla para voltar...");
						getch();
						break;
					
					case'B':
						system("cls");
						printf("\nInsira o novo nome: ");
						fflush(stdin);
						gets(aluno[posAluno].nome);
						
						printf("\nNovo nome: %s", aluno[posAluno].nome);
						getch();
						break;
					
					case'C':
						system("cls");
						printf("\nPressione qualquer tecla para voltar...");
						getch();
						break;
				}
		}
		else {
			printf("\n### ALUNO NAO ENCONTRADO ###\n");
			getch();
		}
		
		system("cls");
		printf("\n### ALTERAR ALUNOS ###\n");
		printf("\nInsira o RA do aluno: ");
		fflush(stdin);
		gets(auxRa);
	}
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

int BuscaDisciplinaEmNotas(_Nota nota[], int auxCod, int TLN) {
	int pos = 0;
	
	while(pos < TLN && nota[pos].cod != auxCod)
		pos++;
		
	if (pos == TLN)
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

void ExcluiDisciplina(_Disc disc[], _Nota nota[], int &TL, int TLN) {
	int auxCod, posDisc, posNota;
	
	system("cls");
	printf("\n### EXCLUIR DISCIPLINA ###\n");
	printf("\nInsira o codigo da disciplina ou digite 0 para sair: ");
	scanf("%d", &auxCod);
	
	while(TL > 0 && auxCod != 0) {
		posDisc = BuscaDisciplina(disc, auxCod, TL);
		posNota = BuscaDisciplinaEmNotas(nota, auxCod, TLN);
		
		if (posDisc >= 0) {
			if(posNota < 0) {
				system("cls");
				printf("\nNome\t\t\tCodigo\n");
				printf("%s\t%d\n", disc[posDisc].nome, disc[posDisc].cod);
				printf("\nDeseja excluir essa disciplina? (S/N): ");
				int op = toupper(getche());
				
				if (op == 'S') {
					for (int i=posDisc; i<TL-1; i++)
						disc[i] = disc[i+1];
					TL--;
					
					system("cls");
					printf("\n*** DISCIPLINA EXCLUIDA COM SUCESSO ***\n");
					getch();
				}
			}
			else {
				system("cls");
				printf("\n*** DISCIPLINA COM CADASTROS FEITOS EM NOTAS: ***\n");
				printf("\nPara excluir a disciplina %s necessario a exclusao das notas!\n", disc[posDisc].nome);
				printf("\nPressione qualquer tecla para voltar...");
				getch();
			}
		}
		else {
			system("cls");
			printf("\n*** DISCIPLINA NAO ENCONTRADA ***");
			getch();
		}
		
		system("cls");
		printf("\n### EXCLUIR DISCIPLINA ###\n");
		printf("\nInsira o codigo da disciplina ou 0 para sair: ");
		scanf("%d", &auxCod);
	}
}

void AlteraDisciplina(_Disc disc[], _Nota nota[], int TL, int TLN) {
	int auxCod, posDisc, posNota;
	
	system("cls");
	printf("\n### ALTERAR DISCIPLINAS ###\n");
	printf("\nInsira o codigo da disciplina ou 0 para sair: ");
	scanf("%d", &auxCod);
	
	while(auxCod != 0) {
		posDisc = BuscaDisciplina(disc, auxCod, TL);
		posNota = BuscaDisciplinaEmNotas(nota, auxCod, TLN);
		
		if (posDisc >= 0) {
			system("cls");
			printf("\nNome da disciplina: %s\tCodigo: %d", disc[posDisc].nome, disc[posDisc].cod);
			printf("\nOque deseja alterar?\n A - Codigo\n B - Nome\n C - Voltar\n");
			int op = toupper(getche());
			
			switch(op) {
				case 'A':
					if (posNota < 0) {
						system("cls");
						printf("\nInsira o novo codigo: ");
						scanf("%d", &disc[posDisc].cod);
						
						printf("\nNovo codigo: %d", disc[posDisc].cod);
						getch();
					}
					else {
						system("cls");
						printf("\n*** ALUNO COM CADASTROS FEITOS EM NOTAS: ***\n");
						printf("\nDeseja alterar o cadastro do aluno nas notas? (S/N) : \n");
						int opAlt = toupper(getche());
						
						if (opAlt == 'S') {
							int auxAltCod;
							system("cls");
							printf("\nInsira o novo codigo: ");
							scanf("%d", &auxAltCod);
							
							disc[posDisc].cod = auxAltCod;
							nota[posNota].cod = auxAltCod;
							
							printf("\nNovo codigo: %d", disc[posDisc].cod);
						}
					}
					printf("\nPressione qualquer tecla para voltar...");
					getch();
					break;
					
				case 'B':
					system("cls");
					printf("\nInsira o novo nome: ");
					fflush(stdin);
					gets(disc[posDisc].nome);
					
					printf("\nNovo nome: %s", disc[posDisc].nome);
					getch();
					break;
					
				case 'C':
					system("cls");
					printf("\nPressione qualquer tecla para voltar...");
					getch();
					break;
			}
		}
		else {
			printf("\n*** DISCIPLINA NAO ENCONTRADA ***\n");
			getch();
		}
		system("cls");
		printf("\n### ALTERAR DISCIPLINAS ###\n");
		printf("\nInsira o codigo da disciplina ou 0 para sair: ");
		scanf("%d", &auxCod);
	}
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

void AlteraNota(_Nota nota[], int TL) {
	int auxCod, posNota;
	char auxRa[10];
	
	system("cls");
	printf("\n### ALTERAR NOTAS ###\n");
	printf("\nInsira o RA do aluno: ");
	fflush(stdin);
	gets(auxRa);
	
	while (strcmp(auxRa, "\0")!=0) {
		printf("\nInsira o codigo da disciplina: ");
		scanf("%d", &auxCod);
		posNota = BuscaNota(nota, auxRa, auxCod, TL);
		
		if(posNota >= 0) {
			system("cls");
			printf("\nRA\t\tCodigo Disciplina\tNota\n");
			printf("\n%s\t%d\t\t\t%.2f", nota[posNota].ra, nota[posNota].cod, nota[posNota].nota);
			printf("\nOque deseja alterar? \n\n A-Aluno\n B-Disciplina\n C-Nota do aluno\n D-Voltar\n");
			int op = toupper(getche());
			
			switch(op) {
				case 'A': 
					system("cls");
					printf("\nInsira o novo RA: ");
					fflush(stdin);
					gets(nota[posNota].ra);
					
					printf("\nNovo RA: %s\n", nota[posNota].ra);
					getch();
					break;
					
				case 'B':
					system("cls");
					printf("\nInsira o codigo da nova disciplina: ");
					scanf("%d", &nota[posNota].cod);
					
					printf("\nNovo codigo: %d\n", nota[posNota].cod);
					getch();
					break;
					
				case 'C':
					system("cls");
					printf("\nInsira a nova nota: ");
					scanf("%f", &nota[posNota].nota);
					
					printf("\nNova nota: %.2f\n", nota[posNota].nota);
					getch();
					break;
					
				case 'D':
					system("cls");
					printf("\nPressione qualquer tecla para voltar...");
					getch();
			}
		}
		else {
			printf("\n*** NOTA NAO ENCONTRADA ***\n");
			getch();
		}
		
		system("cls");
		printf("\n### ALTERAR NOTAS ###\n");
		printf("\nInsira o RA do aluno: ");
		fflush(stdin);
		gets(auxRa);
	}
}

//função que recebe valores de teste

void Teste(_Aluno aluno[], _Disc disc[], _Nota nota[], int &TLA, int &TLD, int &TLN) {
	printf("\nCASO TENHA CADASTRADO ALGO, O CADASTRO VAI SER AUTOMATICAMENTE APAGADO\n");
	printf("\nDeseja prosseguir (S/N)\n");
	char op = toupper(getche());
	
	if (op == 'S') {
		TLA = 0;
		TLD = 0;
		TLN = 0;
		
		//cadastro alunos
		strcpy(aluno[0].ra, "262411911");
		strcpy(aluno[0].nome, "Jose Carlos");
		
		strcpy(aluno[1].ra, "272411911");
		strcpy(aluno[1].nome, "Jubiscleusa");
		
		strcpy(aluno[2].ra, "281411911");
		strcpy(aluno[2].nome, "Perisvaldo");
		
		strcpy(aluno[3].ra, "292411911");
		strcpy(aluno[3].nome, "Will Smith");
	
		strcpy(aluno[4].ra, "302411911");
		strcpy(aluno[4].nome, "Fausto Silva");
		
		//cadastro disciplinas
		disc[0].cod = 123;
		strcpy(disc[0].nome, "Compressao de PDF");
		
		disc[1].cod = 456;
		strcpy(disc[1].nome, "Formatacao de Windows");
		
		disc[2].cod = 789;
		strcpy(disc[2].nome, "Arq. de roteadores");
		
		disc[3].cod = 987;
		strcpy(disc[3].nome, "Conserto de Impressoras");
	
		disc[4].cod = 654;
		strcpy(disc[4].nome, "League of Legends");
		
		//cadastro de notas
		strcpy(nota[0].ra, "262411911");
		nota[0].cod = 456;
		nota[0].nota = 7.8;
		
		strcpy(nota[1].ra, "262411911");
		nota[1].cod = 789;
		nota[1].nota = 6.5;
		
		strcpy(nota[2].ra, "272411911");
		nota[2].cod = 456;
		nota[2].nota = 7.8;
		
		strcpy(nota[3].ra, "302411911");
		nota[3].cod = 789;
		nota[3].nota = 0.2;
		
		strcpy(nota[4].ra, "282411911");
		nota[4].cod = 654;
		nota[4].nota = 8.1;
		
		TLA = 5;
		TLD = 5;
		TLN = 5;
		
		printf("\n### ALUNOS DISCIPLINAS E NOTAS CADASTRADAS ###\n");
		
		printf("\nAlunos: \n");
		printf("\nNome\t\t\tRA\n");
		for(int i=0;i < 5;i++)
			printf("%s\t\t%s\n", aluno[i].nome, aluno[i].ra);
			
		printf("\nDisciplinas: \n");
		printf("\nNome\t\t\t\t\tCodigo\n");
		for(int i=0;i < 5;i++)
			printf("%s\t\t\t%d\n", disc[i].nome, disc[i].cod);
			
		printf("\nNotas: \n");
		printf("\nRA\t\t\tCodigo Disc\t\t\tNota\n");
		for(int i=0;i < 5;i++)
			printf("%s\t\t\t%d\t\t\t%.2f\n", nota[i].ra, nota[i].cod, nota[i].nota);	
	}
	printf("\nPressione qualquer tecla para voltar...");
	getch();
}

//relatorios

int Split(char palavra[], char vetPalavras[TF][30]) {
	int TLVP = 0;
	char auxPalavra[30];
	int TLAP = 0;
	
	for (int i=0; palavra[i] != '\0';i++) {
		if (palavra[i] == ' ') {
			if (TLAP > 0) {
				auxPalavra[TLAP] = '\0';
				strcpy(vetPalavras[TLVP++], auxPalavra);
				TLAP = 0;
			}
		}
		else 
			auxPalavra[TLAP++] = palavra[i];
	}
	
	if (TLAP > 0) {
		auxPalavra[TLAP] = '\0';
		strcpy(vetPalavras[TLVP++], auxPalavra);
	}
	
	return TLVP;
}

int BuscaPalavraDisc(_Disc disc[], char palavra[], int TL, int vetPosDisc[]) {
	int TLVP, TLVPD = 0;
	char vetPalavras[TF][30];
		
	for (int i=0; i < TL;i++) {
		TLVP = Split(disc[i].nome, vetPalavras);
		for (int j=0; j < TLVP;j++) {
			if (stricmp(palavra, vetPalavras[j])==0)
				vetPosDisc[TLVPD++] = i;
		}
	}
	
	if (TLVPD == 0)
		return -1;
	else
		return TLVPD;
}

void RelatorioPalavraDisc(_Disc disc[], int TL) {
	char palavra[30];
	int vetPosDisc[TF];
		
	system("cls");
	printf("\n### PESQUISA POR PALAVRA ###\n");
	printf("\nInsira a palavra que deseja procurar em disciplinas: ");
	fflush(stdin);
	gets(palavra);
	
	while (strcmp(palavra, "\0")!=0) {
		printf("\n### DISCIPLINAS COM A PALAVRA: %s ###\n", palavra);
		int TLVPD = BuscaPalavraDisc(disc, palavra, TL, vetPosDisc);
		printf("%d", TLVPD);
		for (int i = 0; i < TLVPD; i++) {
			printf("\n%s", disc[vetPosDisc[i]].nome);
		}
		getch();
		
		system("cls");
		printf("\n### PESQUISA POR PALAVRA ###\n");
		printf("\nInsira a palavra que deseja procurar em disciplinas: ");
		fflush(stdin);
		gets(palavra);
	}
}

void RelatorioMedia(_Disc disc[], _Nota nota[], int TL, int TLN) {
	float media, soma;
	int cont;
	
	system("cls");
	printf("\n### DISCIPLINAS COM MEDIA ABAIXO DE 6 ###\n");
	for (int i = 0;i < TL;i++) {
		media = 0;
		soma = 0;
		cont = 0;
		for (int j = 0;j < TLN;j++) {
			if (disc[i].cod == nota[j].cod) {
				soma += nota[j].nota;
				cont++;
			}
		}
		media = soma/cont;
		
		if (media < 6) {
			printf("\nDisciplina: %s\tMedia: %.2f", disc[i].nome, media);
		}
	}
}

void RelatorioGeral(_Nota nota[], _Aluno aluno[], _Disc disc[], int TLN, int TLA, int TLD) {
	int posNota;
	printf("\n### RELATORIO GERAL ###\n");
	for (int i=0; i<TLA;i++) {
		printf("RA: %s\tNome: %s", aluno[i].ra, aluno[i].nome);
		for (int j=0; j<TLD;j++) {
			posNota = BuscaNota(nota, aluno[i].ra, disc[j].cod, TLN);
			if (posNota >= 0) {
				if (nota[posNota].nota < 6)
					printf("\nDisciplina: %d - %s\t\tNota: %.2f\tSituacao: Reprovado", disc[j].cod, disc[j].nome, nota[posNota].nota);
				else
					printf("\nDisciplina: %d - %s\t\tNota: %.2f\tSituacao: Aprovado", disc[j].cod, disc[j].nome, nota[posNota].nota);
			}
		}
		printf("\n\n");
	}
	
	getch();
}

int main(void) {
	_Aluno aluno[TF];
	_Disc disc[TF];
	_Nota nota[TF];
	int TLA=0, TLD=0, TLN=0;
	
	Teste(aluno, disc, nota, TLA, TLD, TLN);
//	
	//CadastroAluno(aluno, TLA);
//	CadastroDisciplina(disc, TLD);
//	CadastroNota(nota, aluno, disc, TLA, TLD, TLN);
//	
//	ExcluiNota(nota, aluno, disc, TLA, TLD, TLN);
//	ExcluiAluno(aluno, nota, TLA, TLN);
//	ExcluiDisciplina(disc, nota, TLD, TLN);

//	AlteraNota(nota, TLN);
//	AlteraAluno(aluno, nota, TLA, TLN);
//AlteraDisciplina(disc, nota, TLD, TLN);
//RelatorioPalavraDisc(disc, TLD);
//RelatorioMedia(disc, nota, TLD, TLN);
RelatorioGeral(nota, aluno, disc, TLN, TLA, TLD);
}
