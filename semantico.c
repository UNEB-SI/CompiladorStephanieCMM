#include <stdio.h>
#include "gerenciador.h"
#include "semantico.h"

//DECLARA��ES

int verificarDeclaracaoVariavel(char *nome, int codigoTipo, int categoria, int zumbi){
    int i;
    if((codigoTipo == FUNCAO)){
        for(i = POSICAO-1; i>-1; i--){
            if((strcmp(tabSimbolo[i].nome,nome) == 0)){ //tem o nome igual
                printf("Redeclaracao de Fun��o");
                return 0;
            } else{
                printf("azul!");
                return 1;
            }
        }
    } else{
        for(i = POSICAO-1; i>-1 || codigoTipo != FUNCAO; i--){
            if((strcmp(tabSimbolo[i].nome,nome) == 0)){ // tem o nome igual
                printf("Redeclaracao de Vari�vel Local ou Parametro");
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
            printf("Variavel n�o declarada");
            return 0;
        }
    }
}

int verificarRepetePrototipo(char *nome){
    int i;
    for(i = POSICAO-1; i>-1; i--){
        if((tabSimbolo[i].categoria == PROTOT )){
            if(strcmp(tabSimbolo[i].nome,nome)==0){
                printf("Prot�tipo ja declarado");
                return 0;
            }else{
                return 1;
            }
        }
    }
}

int verificarRetorno(int codigoTipo){
    if(codigoTipo == SEMRETORNO){
        return;
    }else{
        printf("A fun��o n�o pode ter um retorno");
    }
}




