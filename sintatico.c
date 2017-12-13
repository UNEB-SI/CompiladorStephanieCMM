#include <string.h>
#include "sintatico.h"
#include "gerenciador.h"

FILE *arquivo;
int contLinha;
TOKEN Estrutura, nextEstrutura;

void erro(){
    printf("Erro sintatico na linha %d\n",contLinha);
    system("pause");
    exit(1);
}

void sintatico(){
    analisadorLexico(arquivo);
    analisadorLexico(arquivo);
    prog();
}

//\umbi somente para parametro, zumbi == 0, inativo, zumbi == 1 ativo
//escopo == 0 = Global e escopo == 1 = Local
void prog(){

while(!feof(arquivo)){
    if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO || Estrutura.codigo == REAL
        || Estrutura.codigo == BOOLEANO){
         codigoTipo = Estrutura.codigo;
         analisadorLexico(arquivo);
         if(Estrutura.cat == ID){
            nomeIdentificador = Estrutura.tipo.lexema;
            //escopo = 0;
            //zumbi = C:\Documentos\CompiladorStephanieCMM\gerenciador.h1;
            //gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
            //imprimirTabelaSimbolos();
            //analisadorLexico(arquivo);
            if(nextEstrutura.cat == SN && nextEstrutura.codigo == PONTO_VIRGULA){
                escopo = 0;
                zumbi = 1;

                gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
                analisadorLexico(arquivo);
            }else if(nextEstrutura.cat == SN && nextEstrutura.codigo == VIRGULA){
                while(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                    analisadorLexico(arquivo);
                    if(Estrutura.cat == ID){
                       escopo = 0;//global
                       zumbi = 1; //ativo
                       //verificarTabelaSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
                       gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
                       //verificarTabelaSimbolos();
                       analisadorLexico(arquivo);
                    }
                }
                 if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                    analisadorLexico(arquivo);
                } else{
                    printf("ERRO!!Esta faltando um PONTO_VIRGULA");
                    erro();
                }
            }else if(nextEstrutura.cat == SN && nextEstrutura.codigo == ABRE_PARENTESE){
                escopo = 0;
                zumbi = 1;
                gerenciadorTabSimbolos(nomeIdentificador,codigoTipo,FUNCAO,zumbi);
                analisadorLexico(arquivo);
                tipos_param();
                verificarPrototipo(nomeIdentificador, qntdParam);
                if((Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE)){
                    analisadorLexico(arquivo);
                    if((Estrutura.cat == SN && Estrutura.codigo == ABRE_CHAVES)){
                        analisadorLexico(arquivo);
                        if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                            || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                            while(Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                                || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                                codigoTipo = Estrutura.codigo;
                                analisadorLexico(arquivo);
                                if(Estrutura.cat == ID){
                                    escopo = 1;
                                    zumbi = 0;
                                    gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
                                    analisadorLexico(arquivo);
                                    if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                                        analisadorLexico(arquivo);
                                    }else if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                                        while(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                                            analisadorLexico(arquivo);
                                            if(Estrutura.cat == ID){
                                               zumbi = 1;
                                               escopo =0;
                                               gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
                                               analisadorLexico(arquivo);
                                            }
                                        }
                                        if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                                            analisadorLexico(arquivo);

                                        } else{
                                            printf("ERRO!! Esta faltando PONTO_VIRGULA no fim da declaracao da variavel!!!\n");
                                            erro();
                                        }
                                    }
                                } else{
                                    printf("ERRO!! Esta faltando um IDENTIFICADOR!!\n");
                                    erro();
                                }
                            }
                        }
                        if(!(Estrutura.codigo == FECHA_CHAVES)){
                            while(!(Estrutura.codigo == FECHA_CHAVES)){
                                cmd();
                            }
                        }
                        removerItemTabSimbolos();
                        analisadorLexico(arquivo);
                    }else{
                        printf("ERRO!!! Esta faltando abrir CHAVES\n");
                        erro();
                    }
                }else{
                    printf("ERRO!!! Esta faltando fechar o PARENTESES!\n");
                    erro();
                }
            }
         }
    }else if(Estrutura.cat == PR && Estrutura.codigo == PROTOTIPO){
        analisadorLexico(arquivo);
        if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
            || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
            codigoTipo = Estrutura.codigo;
            analisadorLexico(arquivo);
            if(Estrutura.cat == ID){
                zumbi = 1;
                escopo =0;
                gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,PROTOT,zumbi);
                //verificarTabelaSimbolos();
                analisadorLexico(arquivo);
                if(Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE){
                    //escopo = 1;
                    //gerenciadorTabSimbolos(codigoTipo, PROTOT, zumbi);
                    //analisadorLexico(arquivo);
                    tipos_p_opc();
                }
                if(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE){
                    analisadorLexico(arquivo);
                }else{
                    printf("ERRO!!! Esta faltando fechar o PARENTESES!\n");
                    erro();
                }
            } else{
                printf("ERRO!! Esta faltando um IDENTIFICADOR para a FUNCAO!!\n");
                erro();
            }
            if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                while((Estrutura.cat == SN) && (Estrutura.codigo == VIRGULA)){
                    analisadorLexico(arquivo);
                    if(Estrutura.cat == ID){
                        zumbi = 1;
                        escopo =0;
                        gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,PROTOT,zumbi);
                        analisadorLexico(arquivo);
                        if((Estrutura.cat == SN) && (Estrutura.codigo == ABRE_PARENTESE)){
                            //gerenciadorTabSimbolos(codigoTipo, PROTOT, zumbi);
                            //analisadorLexico(arquivo);
                            tipos_p_opc();
                        }
                        if((Estrutura.cat == SN) && (Estrutura.codigo == FECHA_PARENTESE)){
                            analisadorLexico(arquivo);
                        }else{
                            printf("ERRO!!! Esta faltando fechar o PARENTESES!\n");
                            erro();
                        }
                    }
                }
                    if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                        analisadorLexico(arquivo);
                    } else{
                        printf("ERRO!! Esta faltando PONTO_VIRGULA!!\n");
                        erro();
                    }
                } else if((Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA)){
                    analisadorLexico(arquivo);
                } else {
                    printf("ERRO!! Esta faltando PONTO_VIRGULA!!\n");
                    erro();
                }
            }else if(Estrutura.cat == PR && Estrutura.codigo == SEMRETORNO){
                analisadorLexico(arquivo);
                if(Estrutura.cat == ID){
                    codigoTipo = SEMRETORNO;
                    zumbi = 1;
                    escopo =0;
                    gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,PROTOT,zumbi);

                    analisadorLexico(arquivo);
                    if((Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE)){
                        //gerenciadorTabSimbolos(SEMRETORNO, PROTOT, zumbi);
                        //analisadorLexico(arquivo);
                        tipos_p_opc();
                    }
                    if((Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE)){
                        analisadorLexico(arquivo);
                    }else{
                        printf("ERRO!!! Esta faltando fechar o PARENTESES");
                        erro();
                    }
                } else{
                    printf("ERRO!! Esta faltando um IDENTIFICADOR para a FUNCAO!!\n");
                    erro();
                }
                if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                    while((Estrutura.cat == SN) && (Estrutura.codigo == VIRGULA)){
                        analisadorLexico(arquivo);
                        if(Estrutura.cat == ID){
                            zumbi = 1;
                            escopo =0;
                            gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,PROTOT,zumbi);
                            analisadorLexico(arquivo);
                            if((Estrutura.cat == SN) && (Estrutura.codigo == ABRE_PARENTESE)){
                                //gerenciadorTabSimbolos(codigoTipo, PROTOT, zumbi);
                                //analisadorLexico(arquivo);
                                tipos_p_opc();
                            }
                            if((Estrutura.cat == SN) && (Estrutura.codigo == FECHA_PARENTESE)){
                                analisadorLexico(arquivo);
                            }else{
                                printf("ERRO!!! Esta faltando fechar o PARENTESES");
                                erro();
                            }
                        }
                    }
                    if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                        analisadorLexico(arquivo);
                    } else{
                        printf("ERRO!! Esta faltando PONTO_VIRGULA!!\n");
                        erro();
                    }
                } else if((Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA)){
                    analisadorLexico(arquivo);
                } else {
                    printf("ERRO!! Esta faltando PONTO_VIRGULA!!\n");
                    erro();
                }
            }
        }else if((Estrutura.cat == PR && Estrutura.codigo == SEMRETORNO)){
              codigoTipo = SEMRETORNO;
              analisadorLexico(arquivo);
              if(Estrutura.cat == ID){
                nomeIdentificador = Estrutura.tipo.lexema;
                escopo = 0;
                zumbi = 1;
                gerenciadorTabSimbolos(nomeIdentificador,codigoTipo,FUNCAO,zumbi);
                //verificarTabelaSimbolos();
                analisadorLexico(arquivo);
                if((Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE)){
                    tipos_param();
                        if((Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE)){
                            analisadorLexico(arquivo);
                            if((Estrutura.cat == SN && Estrutura.codigo == ABRE_CHAVES)){
                                analisadorLexico(arquivo);
                                if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                                    || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                                    while(Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                                    || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                                        codigoTipo = Estrutura.codigo;
                                        analisadorLexico(arquivo);
                                        if(Estrutura.cat == ID){
                                            escopo = 1;
                                            zumbi = 0;
                                            gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
                                            analisadorLexico(arquivo);
                                            if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                                                analisadorLexico(arquivo);
                                            }else if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                                                while(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                                                    analisadorLexico(arquivo);
                                                    if(Estrutura.cat == ID){
                                                        escopo = 1;
                                                        zumbi = 0;

                                                        gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,VARIAVEL,zumbi);
                                                        analisadorLexico(arquivo);
                                                    }
                                                }
                                                if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                                                    analisadorLexico(arquivo);
                                                } else{
                                                    printf("ERRO!! Esta faltando PONTO_VIRGULA no fim da declaracao da variavel!!!\n");
                                                    erro();
                                                }
                                            }
                                        }
                                    }
                                }
                                if(!(Estrutura.codigo == FECHA_CHAVES)){
                                    while(!(Estrutura.codigo == FECHA_CHAVES)){
                                    cmd();
                                    //printf("Categoria = %2d\t Codigo = %2d\t Token = %s\n",Estrutura.cat,Estrutura.codigo,Estrutura.tipo.lexema);
                                }
                            }
                            removerItemTabSimbolos();
                            analisadorLexico(arquivo);
                        } else{
                            printf("ERRO!!! Esta faltando abrir CHAVES\n");
                            erro();
                        }
                    }else{
                        printf("ERRO!!! Esta faltando fechar o PARENTESES!\n");
                        erro();
                    }
                }
            }
        }
    }
}

void tipos_param(){
    analisadorLexico(arquivo);
    if((Estrutura.cat == PR && Estrutura.codigo == SEMPARAM)){
        analisadorLexico(arquivo);
    } else if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
        || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
        codigoTipo = Estrutura.codigo;
        analisadorLexico(arquivo);
        if(Estrutura.cat == ID){
            escopo = 1;
            zumbi = 0;
            gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,PARAMETRO,zumbi);
            qntdParam +=1;
            printf("%d", qntdParam);
            //imprimirTabelaSimbolos();
            analisadorLexico(arquivo);
            if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                while(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                    analisadorLexico(arquivo);
                    if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                        || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                         codigoTipo = Estrutura.codigo;
                         escopo = 1;
                         zumbi = 0;
                        analisadorLexico(arquivo);
                        if(Estrutura.cat == ID){
                            gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo,PARAMETRO,zumbi);
                            analisadorLexico(arquivo);
                        }
                    }
                }
            }
        }
    }
}

void tipos_p_opc(){
    analisadorLexico(arquivo);
    if((Estrutura.cat == PR && Estrutura.codigo == SEMPARAM)){
        analisadorLexico(arquivo);
    } else if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
        || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
        codigoTipo = Estrutura.codigo;
        analisadorLexico(arquivo);
        if(Estrutura.cat == ID){
            escopo = 1;
            zumbi = 0;
            gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo, PARAMETRO, zumbi);
            analisadorLexico(arquivo);
            if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                while(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                    analisadorLexico(arquivo);
                    if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                        || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                        codigoTipo = Estrutura.codigo;
                        escopo = 1;
                        zumbi = 0;
                        analisadorLexico(arquivo);
                        if(Estrutura.cat == ID){
                            gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo, PARAMETRO, zumbi);
                            analisadorLexico(arquivo);
                        } else{
                            gerenciadorTabSimbolos("Sem identificador",codigoTipo, PARAMETRO, zumbi);
                            analisadorLexico(arquivo);
                        }
                    }
                }
            }
        }else{
            gerenciadorTabSimbolos("Sem identificador",codigoTipo, PARAMETRO, zumbi);
        }
        if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
            analisadorLexico(arquivo);
            if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                codigoTipo = Estrutura.codigo;
                analisadorLexico(arquivo);
                if(Estrutura.cat == ID){
                    escopo = 1;
                    zumbi = 0;
                    gerenciadorTabSimbolos(Estrutura.tipo.lexema,codigoTipo, PARAMETRO, zumbi);
                    analisadorLexico(arquivo);
                    if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                        while(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                            analisadorLexico(arquivo);
                            if(Estrutura.cat == PR && Estrutura.codigo == CARACTER || Estrutura.codigo == INTEIRO
                                || Estrutura.codigo == REAL || Estrutura.codigo == BOOLEANO){
                                analisadorLexico(arquivo);
                            }
                        }
                    }
                } else{
                    gerenciadorTabSimbolos("Sem identificador",codigoTipo, PARAMETRO, zumbi);
                }
            }
        }
    }
}

void cmd(){
    if(Estrutura.cat == PR && Estrutura.codigo == SE){
        analisadorLexico(arquivo);
        if(Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE){
            expr();
            if(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE){
                analisadorLexico(arquivo);
                if(nextEstrutura.cat == PR && nextEstrutura.codigo == RETORNE){
                    analisadorLexico(arquivo);
                }
                cmd();
                if(Estrutura.cat == PR && Estrutura.codigo == SENAO){
                    analisadorLexico(arquivo);
                    cmd();
                }
            } else {
                printf("ERRO!! Esta faltando um FECHA_PARENTESE!");
                erro();
            }

        } else{
            printf("ERRO!! Esta faltando um ABRE_PARENTESE!");
            erro();
        }

    } else if(Estrutura.cat == PR && Estrutura.codigo == ENQUANTO){
        analisadorLexico(arquivo);
        if(Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE){
            analisadorLexico(arquivo);
            expr();
            if(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE){
                analisadorLexico(arquivo);
                cmd();

            } else {
                printf("ERRO!! Esta faltando um FECHA_PARENTESE!");
                erro();
            }
        }else{
            printf("ERRO!! Esta faltando um ABRE_PARENTESE!");
            erro();
        }
    }else if(Estrutura.cat == PR && Estrutura.codigo == PARA){
        analisadorLexico(arquivo);
        if(Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE){
            analisadorLexico(arquivo);
            if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                analisadorLexico(arquivo);
             }else{
                analisadorLexico(arquivo);
                atrib();
            }
            if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                analisadorLexico(arquivo);
                if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                    analisadorLexico(arquivo);
                } else{
                    expr();
                }
             }else{
                printf("ERRO!! Esta faltando um PONTO_VIRGULA");
                erro();
            }
            if(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA){
                analisadorLexico(arquivo);
            }else{
                printf("ERRO!! Esta faltando um PONTO_VIRGULA");
                erro();
            }
            if(Estrutura.cat != SN && Estrutura.codigo != FECHA_PARENTESE){
                analisadorLexico(arquivo);
                atrib();
            }
            if(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE){
                analisadorLexico(arquivo);
            }
            cmd();
        }else{
            printf("ERRO!! Esta faltando um ABRE_PARENTESE no PARA!");
            erro();
        }
    } else if(Estrutura.cat == PR && Estrutura.codigo == RETORNE){
        analisadorLexico(arquivo);
        if(!(Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA)){
            expr();
        }
        if(nextEstrutura.cat == SN && nextEstrutura.codigo == PONTO_VIRGULA){
            analisadorLexico(arquivo);
        }
        if((Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA)){
            analisadorLexico(arquivo);
        } else{
            printf("ERRO!! Esta faltando um PONTO_VIRGULA!");
            erro();
        }
    } else if(Estrutura.cat == ID){
        if(nextEstrutura.cat == SN && nextEstrutura.codigo == ATRIBUICAO){
            analisadorLexico(arquivo);
            atrib();
            if((Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA)){
                analisadorLexico(arquivo);
            } else{
                printf("ERRO!! Esta faltando um PONTO_VIRGULA!");
                erro();
            }
        } else if((nextEstrutura.cat == SN && nextEstrutura.codigo == ABRE_PARENTESE)){
            analisadorLexico(arquivo);
            if(!(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE)){
                expr();
                if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                    analisadorLexico(arquivo);
                    expr();
                     while((Estrutura.cat == SN && Estrutura.codigo == VIRGULA)){
                        analisadorLexico(arquivo);
                        expr();
                    }
                }
            } else{
                analisadorLexico(arquivo);
            }
            if(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE){
                analisadorLexico(arquivo);
            } else{
                printf("ERRO!! Esta faltando um FECHA_PARENTESES");
                erro();
            }
            if((Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA)){
                analisadorLexico(arquivo);
            }else{
                printf("ERRO!! Esta faltando um PONTO_VIRGULA aqui\n");
                erro();
            }
        }

    } else if((Estrutura.cat == SN && Estrutura.codigo == ABRE_CHAVES)){
        analisadorLexico(arquivo);
        while((Estrutura.cat == SN && Estrutura.codigo != FECHA_CHAVES)){
            cmd();
        }
        if(Estrutura.cat == SN && Estrutura.codigo == FECHA_CHAVES){
            analisadorLexico(arquivo);
        }else{
            printf("ERRO!! Esta faltando um FECHA_CHAVES\n");
            erro();
        }
    }else if((Estrutura.cat == SN && Estrutura.codigo == PONTO_VIRGULA)){
        analisadorLexico(arquivo);
    }
}


int atrib(){
    if((Estrutura.cat == SN && Estrutura.codigo == ATRIBUICAO)){
        //analisadorLexico(arquivo);
        expr();
        return 1;
    }
    printf("ERRO!! Esta faltando o sinal de ATRIBUICAO\n");
    return 0;
}

void expr(){
     expr_simp();
    if(Estrutura.cat == SN && op_rel()){
        expr_simp();
    }
}


void expr_simp(){
    if((Estrutura.cat == SN && Estrutura.codigo == ADICAO)){
        analisadorLexico(arquivo);
    } else if((Estrutura.cat == SN && Estrutura.codigo == SUBTRACAO)){
        analisadorLexico(arquivo);
    }
    termo();
    if(Estrutura.codigo == ADICAO || Estrutura.codigo == SUBTRACAO || Estrutura.codigo == OR){
        while(Estrutura.codigo == ADICAO || Estrutura.codigo == SUBTRACAO || Estrutura.codigo == OR){
            analisadorLexico(arquivo);
            termo();
        }
    }
}

void termo(){
    fator();
    if(Estrutura.codigo == MULTIPLICACAO || Estrutura.codigo == DIVISAO || Estrutura.codigo == AND){
        while(Estrutura.codigo == MULTIPLICACAO || Estrutura.codigo == DIVISAO || Estrutura.codigo == AND){
            analisadorLexico(arquivo);
            fator();
        }
    }
}

void fator(){
   analisadorLexico(arquivo);
   if(Estrutura.cat == ID){
        verificarDeclaracao(Estrutura.tipo.lexema, 1);
        analisadorLexico(arquivo);
        if((Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE)){
            analisadorLexico(arquivo);
            if(!(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE)){
                expr();
                if(Estrutura.cat == SN && Estrutura.codigo == VIRGULA){
                    analisadorLexico(arquivo);
                    expr();
                    while((Estrutura.cat == SN && Estrutura.codigo == VIRGULA)){
                        analisadorLexico(arquivo);
                        expr();
                    }
                }
            } else{
                analisadorLexico(arquivo);
            }
            if(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE){
                analisadorLexico(arquivo);
            } else{
                printf("ERRO!! Esta faltando um FECHA_PARENTESES");
                erro();
            }
        }

    } else if(Estrutura.cat == CTI || Estrutura.cat == CTR || Estrutura.cat == CTC || Estrutura.cat == LT){
        analisadorLexico(arquivo);
    } else if(Estrutura.cat == SN && Estrutura.codigo == ABRE_PARENTESE){
        analisadorLexico(arquivo);
        expr();
        if(Estrutura.cat == SN && Estrutura.codigo == FECHA_PARENTESE){
            analisadorLexico(arquivo);
        } else {
            printf("ERRO!! Esta faltando 1 um FECHA_PARENTESE!\n");
            erro();
        }
    } else if((Estrutura.cat == SN && Estrutura.codigo == NOT)){
        analisadorLexico(arquivo);
        fator();
    }
}

int op_rel(){
    //analisadorLexico(arquivo);
    if(Estrutura.cat == SN && Estrutura.codigo == IGUALDADE || Estrutura.codigo == DIFERENTE
        || Estrutura.codigo == MENOR_IGUAL || Estrutura.codigo == MENOR_QUE || Estrutura.codigo == MAIOR_IGUAL
        || Estrutura.codigo == MAIOR_QUE){
        analisadorLexico(arquivo);
        return 1;
    }
    return 0;
}


