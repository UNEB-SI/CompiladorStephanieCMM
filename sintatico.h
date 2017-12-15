#ifndef SINTATICO_INCLUDED
#define SINTATICO_INCLUDED
#include "lexico.h"

void sintatico();
void prog();
void tipo();
void tipos_param();
void func();
void cmd();
int atrib();
void expr();
void expr_simp();
void termo();
void fator();
int op_rel();
void tipos_p_opc();
void erro();
void abrir_gerador_codigo();
void fechar_gerador_codigo();
char adiciona_Label();

#endif //SINTATICO_INCLUDED
