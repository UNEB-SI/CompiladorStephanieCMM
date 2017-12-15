#ifndef GERENCIADOR_H_INCLUDED
#define GERENCIADOR_H_INCLUDED

int escopo, zumbi, codigoTipo, POSICAO, contParam, qntdParam;
char *nomeIdentificador;

typedef enum{
    FUNCAO =1,VARIAVEL,PARAMETRO, PROTOT
}CTG;

typedef struct p{
    int quantidade;
    int tipo[1000];
}PARAMETROS;

typedef struct tabelaSimbolo{
    char nome[1000];
    int codigoTipo;
    int escopo;
    int linha;
    int zumbi;
    //int label;
    PARAMETROS param;
    CTG categoria;
}TABELA;

void inserirTabela(char *,int, int, int);
//void verificarTabelaSimbolos(char *,int, int, int);
void gerenciadorTabSimbolos(char *,int, int, int);
void imprimirTabelaSimbolos();
void removerItemTabSimbolos();

PARAMETROS param[1000];
TABELA tabSimbolo[1000];

#endif // GERENCIADOR_H_INCLUDED
