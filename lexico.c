#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

char tabelaPR[12][12] = {"caracter", "inteiro", "real", "booleano", "semretorno", "semparam", "se", "senao", "enquanto", "para", "retorne", "prototipo"};
contLinha = 1;

FILE * abrir_Arquivo(char nomeArquivo[]){
    FILE *arquivo;
    if((arquivo = fopen(nomeArquivo,"r")) != NULL ){
        return arquivo;
    }
    else{
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }
}

int verificarPR(char palavra[]){
    int i;

    for(i=0; i<12; i++){
      if(!strcmp(palavra, tabelaPR[i])){
        return i;
      }
    }
    return -1;
}

void erro_Lexico(){
     printf("Erro lexico na linha %d\n",contLinha);
     system("PAUSE");
     exit(1);
}

void inicializaEstrutura(TOKEN *estrutura){
    estrutura->cat = -1;
    estrutura->codigo = 0;
    strcpy(estrutura->tipo.lexema,"");
}

TOKEN analisadorLexico(FILE * arquivo){

    Estrutura = nextEstrutura;

    int estado = 0, contador,pr, converte, converte2;
    char token[TAM];
    char caracter;
    strcpy(token,"");
    //inicializaEstrutura(&Estrutura);
        while(estado >=0 ){
            switch (estado){
                case 0:{
                    contador = 0;
                    caracter = fgetc(arquivo);
                    if(caracter == ' '){ // ESPAÇO EM BRANCO
                       estado = 0;
                    }else if(caracter == '\n'){ //ENTER
                       estado = 0;
                       contLinha++;
                    }else if(caracter == '\t'){ //TABULAR
                       estado = 0;
                    }else if(caracter == '>'){ //MAIOR QUE
                        estado = 48;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '<'){ //MENOR QUE
                        estado = 45;
                        token[contador] = caracter;
                        contador++;
                    }else if(isalpha(caracter)){ //letra
                        estado = 1;
                        token[contador] = caracter;
                        contador++;
                    }else if(isdigit(caracter)){ //digito
                        estado = 3;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '*'){ //MULTIPLICAÇÃO
                        estado = 54;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '+'){ //ADIÇÃO
                        estado = 51;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '-'){ //SUBTRAÇÃO
                        estado = 52;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '('){ //ABRE PARESENTESES
                        estado = 38;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == ')'){ //FECHA PARENTESES
                        estado = 60;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == ','){ //VIRGULA
                        estado = 37;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == ';'){ //PONTO E VIRGULA
                        estado = 36;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '{'){ //ABRE CHAVES
                        estado = 39;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '}'){ //FCHA CHAVES
                        estado = 61;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '='){ //ATRIBUIÇÃO
                        estado = 40;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '!'){ //not
                        estado = 43;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '&'){ //and
                        estado = 56;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '|'){ //or
                        estado = 58;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '/'){ //comentario
                        estado = 31;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '\''){ //ch
                        estado = 8;
                         token[contador++] = caracter;
                    }else if(caracter == '\"'){ //comentatio
                        estado = 23;
                        token[contador++] = caracter;
                    } else if(caracter == EOF){
                        printf("\n\nFIM DE ARQUIVO");
                        exit(1);
                    }
                    break;
                }

                /* -1:{
                    printf("Fim de arquivo");
                    exit(1);
                }*/

                case 1:{ //letra
                    caracter = getc(arquivo);
                    if(isalpha(caracter) || isdigit(caracter) || caracter =='_'){
                        estado = 1;
                        token[contador] = caracter;
                        contador++;
                    }
                    else{
                        estado = 2;
                    }

                    break;
                }

                case 2:{
                    token[contador] = '\0';
                    pr = verificarPR(token);
                    strcpy(nextEstrutura.tipo.lexema,token);
                    estado = 0;

                    if(pr != -1){
                        nextEstrutura.cat = PR;
                        nextEstrutura.codigo = pr;
                    }else{
                        nextEstrutura.cat = ID;
                    }

                    ungetc(caracter, arquivo);
                    return nextEstrutura;
                }

                case 3:{
                    caracter = getc(arquivo);
                    if(isdigit(caracter)){
                        estado = 3;
                        token[contador] = caracter;
                        contador++;
                    }else if(caracter == '.'){
                        estado = 5;
                        token[contador] = caracter;
                        contador++;
                    }else{
                        estado = 4;
                    }
                   break;
                }

                case 4:{
                    token[contador] = '\0';
                    converte = atoi(token);
                    nextEstrutura.cat = CTI;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = converte;
                    estado = 0;

                    ungetc(caracter, arquivo);
                    return nextEstrutura;
                }

                case 5:{
                    caracter = getc(arquivo);
                    if(isdigit(caracter)){
                        estado = 6;
                        token[contador] = caracter;
                        contador++;
                    }
                    else{
                        erro_Lexico();
                    }
                    break;
                }

                 case 6:{
                    caracter = getc(arquivo);
                    if(isdigit(caracter)){
                        estado = 6;
                        token[contador] = caracter;
                        contador++;
                    }
                    else{
                        estado = 7;
                    }
                    break;
                }

                case 7:{

                    token[contador] = '\0';
                    converte2 = atoi(token);
                    nextEstrutura.cat = CTR;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = converte2;
                    estado = 0;

                    ungetc(caracter, arquivo);
                    return nextEstrutura;

                    break;
                }

                case 8:{
                    caracter = getc(arquivo);
                    if(caracter != '\\' && caracter != '\'' ){
                        if(isprint(caracter)){
                            estado = 9;
                            token[contador] = caracter;
                            contador++;
                        }else if(caracter == '\\'){
                            estado = 11;
                            token[contador] = caracter;
                            contador++;
                        }else{
                            erro_Lexico();
                        }
                    }
                    break;
                }

                case 9:{ // caracon
                    caracter= getc(arquivo);
                    if(caracter == '\''){
                        estado = 10;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        erro_Lexico();
                    }
                    break;
                }

                case 10:{
                    token[contador] = '\0';
                    nextEstrutura.cat = CTC;
                    strcpy(nextEstrutura.tipo.lexema,token);

                    return nextEstrutura;
                    break;
                }

                 case 11:{
                     if(caracter == 'n'){
                        estado = 12;
                        token[contador] = caracter;
                        contador++;
                    } else if (caracter == '0'){
                        estado = 15;
                        token[contador] = caracter;
                        contador++;
                    }else{
                        erro_Lexico();
                    }
                    break;

                 }

                case 12:{
                    caracter = getc(arquivo);
                    if(caracter == '\''){
                        estado = 14;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        erro_Lexico();
                    }
                    break;
                }

                case 13:{
                    caracter = getc(arquivo);
                    if(caracter == '\''){
                        estado = 14;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        estado = 18;
                    }
                    break;
                }


                 case 14:{
                    token[contador] = '\0';
                    nextEstrutura.cat = CTC;
                    strcpy(nextEstrutura.tipo.lexema,token);

                    return nextEstrutura;

                    break;
                }

                case 15:{
                    caracter = getc(arquivo);
                    if(caracter == '\''){
                        estado = 16;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        erro_Lexico();
                    }
                    break;
                }

                case 16:{
                    token[contador] = '\0';
                    nextEstrutura.cat = CTC;
                    strcpy(nextEstrutura.tipo.lexema,token);

                    return nextEstrutura;
                    break;
                }

                case 23:{
                   caracter = getc(arquivo);
                    if(caracter != '\"' && caracter != '\n' && isprint(caracter)){
                        estado = 23;
                        token[contador] = caracter;
                        contador++;
                    } else if(caracter == '\"'){
                        estado = 25;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        erro_Lexico();
                    }

                    break;
                }

                case 25:{
                    token[contador] = '\0';
                    nextEstrutura.cat = LT;
                    strcpy(nextEstrutura.tipo.lexema,token);

                    return nextEstrutura;
                    break;
                }

                case 30:{
                    caracter = getc(arquivo);
                    if(caracter == '='){
                        estado = 50;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        estado = 49;
                    }

                    break;
                }

                case 31:{
                    caracter = getc(arquivo);
                    if(caracter == '*'){
                        estado = 32;

                    } else{
                        estado = 53;
                        token[contador] = caracter;
                        contador++;
                    }

                    break;
                }

                case 32:{
                    caracter = getc(arquivo);
                    if(caracter == '*'){
                        estado = 34;
                    }else if(caracter == '\n'){
                        contLinha++;
                    }else if(isprint(caracter) && caracter != '*' && caracter != '\n'){
                        estado = 32;
                    }else if(caracter == EOF){
                         printf("\n\n\tERRO!!! Comentario aberto nao foi fechado!\n\n");
                         exit(1);
                    }
                    break;
                }

                case 34:{
                    caracter = getc(arquivo);
                    if(caracter == '*'){
                        estado = 34;
                    } else if(caracter == '/'){
                        //printf("entrei aqui");
                        estado = 0;
                        strcpy(token,"");
                        inicializaEstrutura(&nextEstrutura);
                    } else if(caracter == EOF){
                         printf("\n\n\tERRO!!! Comentario aberto nao foi fechado!\n\n");
                         exit(1);
                    }else{
                        estado = 32;
                    }
                    break;
                }

                case 53:{
                    token[contador] = '\0';
                    Estrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = DIVISAO;

                    return nextEstrutura;
                    break;
                }

                case 48:{
                    caracter = getc(arquivo);
                    if(caracter == '='){
                        estado = 50;
                        token[contador] = caracter;
                        contador++;
                    } else {
                        estado = 49;
                        token[contador] = caracter;
                        contador++;
                    }

                    break;
                }

                 case 50:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = MAIOR_IGUAL;

                    estado = 0;
                    return nextEstrutura;

                  break;
                }

                case 49:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = MAIOR_QUE;
                    estado = 0;

                    ungetc(caracter, arquivo);
                    return nextEstrutura;

                  break;
                }

                case 45:{
                    caracter = getc(arquivo);
                    if(caracter == '='){
                        estado = 46;
                        token[contador] = caracter;
                        contador++;
                    } else {
                        estado = 47;
                        token[contador] = caracter;
                        contador++;
                    }

                    break;
                }

                case 46:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = MENOR_IGUAL;
                    estado = 0;

                    //ungetc(caracter, arquivo);
                    return nextEstrutura;

                    break;
                }

                case 47:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = MENOR_QUE;
                    estado = 0;

                    ungetc(caracter, arquivo);
                    return nextEstrutura;

                    break;
                }


                case 54:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = MULTIPLICACAO;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }
                case 51:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = ADICAO;
                    estado = 0;
                    return nextEstrutura;

                 break;
                }

                case 52:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = SUBTRACAO;
                    estado = 0;
                    return nextEstrutura;

                    break;

                }
                case 36:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = PONTO_VIRGULA;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }

                case 37:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = VIRGULA;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }

                case 38:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = ABRE_PARENTESE;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }

                case 60:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = FECHA_PARENTESE;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }

                 case 39:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = ABRE_CHAVES;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }

                case 61:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = FECHA_CHAVES;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }

                case 40:{
                    caracter = getc(arquivo);
                    if(caracter == '='){
                        estado = 41;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        estado = 42;
                        token[contador] = caracter;
                        contador++;
                    }
                    break;
                }

                 case 41:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = IGUALDADE;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }

                case 42:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = ATRIBUICAO;
                    estado = 0;

                    ungetc(caracter, arquivo);
                    return nextEstrutura;

                    break;
                }

                case 43:{
                    caracter = getc(arquivo);
                    if(caracter == '='){
                        estado = 44;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        estado = 55;
                        token[contador] = caracter;
                        contador++;
                    }

                    break;
                }

                case 44:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = DIFERENTE;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }
                case 55:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = NOT;
                    estado = 0;
                    ungetc(caracter, arquivo);
                    return nextEstrutura;

                    break;
                }
                case 56:{
                    caracter = getc(arquivo);
                    if(caracter == '&'){
                        estado = 57;
                        token[contador] = caracter;
                        contador++;
                    }
                   break;
                }

                case 57:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = AND;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }
                case 58:{
                    caracter = getc(arquivo);
                    if(caracter == '|'){
                        estado = 59;
                        token[contador] = caracter;
                        contador++;
                    } else{
                        erro_Lexico();
                    }
                   break;
                }

                case 59:{
                    token[contador] = '\0';
                    nextEstrutura.cat = SN;
                    strcpy(nextEstrutura.tipo.lexema,token);
                    nextEstrutura.codigo = OR;
                    estado = 0;
                    return nextEstrutura;

                    break;
                }
        }
    }
}




