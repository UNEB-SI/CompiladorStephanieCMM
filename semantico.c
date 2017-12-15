#include <stdio.h>
#include "gerenciador.h"
#include "semantico.h"

//DECLARAÇÕES

int verificarDeclaracaoVariavel(char *nome, int codigoTipo, int categoria, int zumbi){
    int i;
    if((codigoTipo == FUNCAO)){
        for(i = POSICAO-1; i>-1; i--){
            if((strcmp(tabSimbolo[i].nome,nome) == 0)){ //tem o nome igual
                printf("Redeclaracao de Funcaoo");
                return 0;
            } else{
                return 1;
            }
        }
    } else{
        for(i = POSICAO-1; i>-1 || codigoTipo != FUNCAO; i--){
            if((strcmp(tabSimbolo[i].nome,nome) == 0)){ // tem o nome igual
                printf("Redeclaracao de Variavel Local ou Parametro");
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
            printf("Variavel não declarada");
            return 0;
        }
    }
}

int temPrototipo(char *nome, int tipo, int qntdParam){
    int i;
    for(i = POSICAO-1; i>-1; i--){
        if(strcmp(tabSimbolo[i].nome,nome)==0){
           if((tabSimbolo[i].categoria == FUNCAO && tabSimbolo[i].codigoTipo == tipo && tabSimbolo[i].param.quantidade == qntdParam)){
               return 1;
            }
        } else if(tabSimbolo[i].categoria == FUNCAO && tabSimbolo[i].codigoTipo != tipo && tabSimbolo[i].param.quantidade == qntdParam){
            printf("Tipos incompativeis");
            return 0;
        }else{
            printf("Quantidades de parâmetros incompatíveis");
            return 0;
        }
    }
}

int verificarRepetePrototipo(char *nome){
    int i;
    for(i = POSICAO-1; i>-1; i--){
        if((tabSimbolo[i].categoria == PROTOT )){
            if(strcmp(tabSimbolo[i].nome,nome)==0){
                printf("Protótipo ja declarado");
                return 0;
            }else{
                return 1;
            }
        }
    }
}

int verificarRetorno(int codigoTipo){
    if(codigoTipo == 4){
        return 1;
    }else{
        printf("A função não pode ter um retorno");
        return 0;
    }
}

int verificarFuncaoPrincipal(){
    int i;
    for(i = POSICAO-1; i>-1; i--){
        if(strcmp(tabSimbolo[i].nome, "principal")){
            return 1;
        }
        printf("O programa não possui um programa principal");
        return 0;
    }

}


