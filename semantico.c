#include <stdio.h>
#include "gerenciador.h"
#include "semantico.h"

//DECLARAÇÕES

int verificarDeclaracaoVariavel(char *nome, int codigoTipo, int categoria, int zumbi){
    int i;
    if((tabSimbolo[POSICAO].categoria == FUNCAO) && (tabSimbolo[POSICAO].escopo == 0) && (tabSimbolo[POSICAO].zumbi == 1)){
        for(i = POSICAO-1; i>-1; i--){
            if((strcmp(tabSimbolo[i].nome,nome) == 0)){ //tem o nome igual
                printf("Redeclaracao de Função");
                return 0;
            } else{
                return 1;
            }
        }
    } else{
        for(i = POSICAO-1; i>-1 || tabSimbolo[i].categoria != FUNCAO; i--){
            if((strcmp(tabSimbolo[i].nome,nome) == 0)){ // tem o nome igual
                printf("Redeclaracao de Variável Local ou Parametro");
                return 0;
            } else{
                return 1;
            }
        }

    }
}

int verificarDeclaracao(char * lexema, int escopo){
    int i;
    for(i = POSICAO-1; i>-1; i--){
        if((strcmp(tabSimbolo[i].nome,lexema) == 0)){
            if(tabSimbolo[i].escopo == 0){
                return 1;
            } else if(tabSimbolo[i].escopo == 1){
                return 1;
            }
        } else{
            printf("Variavel não declarado");
            return 0;
        }
    }
}

int verificarPrototipo(){
    int i;
    for(i = POSICAO-1; i>-1; i--){
        if((tabSimbolo[POSICAO].categoria == PROTOT )){
        }
    }
}

