#include <string.h>
#include "sintatico.h"
#include "gerenciador.h"
#include "semantico.h"

 POSICAO = 0;
 int topo;

void inserirTabela(char *nome, int codigoTipo, int categoria, int zumbi){

    strcpy(tabSimbolo[POSICAO].nome,nome);
    tabSimbolo[POSICAO].codigoTipo = codigoTipo;
    tabSimbolo[POSICAO].escopo = escopo;
    tabSimbolo[POSICAO].categoria = categoria;
    tabSimbolo[POSICAO].zumbi = zumbi;
    tabSimbolo[POSICAO].param.quantidade = qntdParam;


    printf("\n\n\n");
    printf("\n\t =======================  TABELA DE SIMBOLOS =======================");
    printf("\n\t Nome do Identificador: %s | Codigo do Tipo do Identificador : %d |Escopo (Global = 0; Local = 1): %d | Categoria (FUNC, VARIAV, PARAM,PROTOT): %d | Zumbi: %d\n, QntdParam : %d",tabSimbolo[POSICAO].nome,
          tabSimbolo[POSICAO].codigoTipo, tabSimbolo[POSICAO].escopo,tabSimbolo[POSICAO].categoria, tabSimbolo[POSICAO].zumbi, tabSimbolo[POSICAO].param.quantidade);
    POSICAO +=1;
}

void imprimirTabelaSimbolos(){
    int i;
    printf("\n\n\n\n\n\n");
    printf("\t =======================  TABELA DE SIMBOLOS =======================");
    printf("\n\n\n\n");
   for(i = POSICAO-1; i>-1; i--){
   	  if(tabSimbolo[i].escopo >=0){
	 	    printf("\n\t Nome do Identificador: %s | Codigo do Tipo do Identificador : %d |Escopo (Global = 0;Local = 1): %d | Categoria %d | Zumbi: %d\n",tabSimbolo[i].nome,
              tabSimbolo[i].codigoTipo, tabSimbolo[i].escopo,tabSimbolo[i].categoria, tabSimbolo[i].zumbi);
   	  }else{
	   	printf("Não deu...");
   	  }
   }
	getchar();
}



void removerItemTabSimbolos(){
    while(1){
        if((tabSimbolo[POSICAO].zumbi == 0) && (tabSimbolo[POSICAO].escopo == 1) && (!(tabSimbolo[POSICAO].categoria == PARAMETRO))){
            POSICAO = POSICAO - 1;
        }
        else{
            break;
        }
        imprimirTabelaSimbolos();
    }
}

void gerenciadorTabSimbolos(char *nome, int codigoTipo, int categoria, int zumbi){
    int i, auxiliar;

    if(codigoTipo == FUNCAO || codigoTipo == PARAMETRO || codigoTipo == VARIAVEL){
       auxiliar = verificarDeclaracaoVariavel(nome, codigoTipo, categoria, zumbi);
       if(auxiliar == 1){
            inserirTabela(nome, codigoTipo, categoria,zumbi);
       } else{
            removerItemTabSimbolos(); //remoção somente em funções
       }
    }
}


