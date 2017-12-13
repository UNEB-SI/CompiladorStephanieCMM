#ifndef LEXICO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 1000

typedef enum{
    OR,AND,NOT,
	MULTIPLICACAO,DIVISAO,ADICAO,SUBTRACAO,DIFERENTE,
	MENOR_QUE,MENOR_IGUAL,MAIOR_QUE,MAIOR_IGUAL,
	IGUALDADE,ATRIBUICAO,
    VIRGULA,PONTO_VIRGULA,
	ABRE_PARENTESE, FECHA_PARENTESE, ABRE_CHAVES, FECHA_CHAVES
}Sinais;

typedef enum{
	CARACTER, INTEIRO, REAL, BOOLEANO, SEMRETORNO, SEMPARAM, SE, SENAO, ENQUANTO, PARA, RETORNE, PROTOTIPO
}PalavraReservada;


typedef enum{
    ID,PR,SN,CTI,
	CTR,CTC,LT
}Categoria;

typedef struct token{
    Categoria cat;
    int codigo;
    union {
        char lexema[TAM];
        int valor_inteiro;
        float valor_real;
    }tipo;
}TOKEN;

extern TOKEN Estrutura;
extern TOKEN nextEstrutura;
extern FILE *arquivo;
extern int contLinha;


FILE * abrir_Arquivo(char nomeArquivo[]);
int verificarPR(char token[]);
void erro_Lexico();
TOKEN analisadorLexico(FILE *);
void inicializaEstrutura(TOKEN *);

#endif

