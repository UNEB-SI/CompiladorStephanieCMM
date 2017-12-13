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

#endif //SINTATICO_INCLUDED
