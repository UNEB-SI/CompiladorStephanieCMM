#ifndef SEMANTICO_H_INCLUDED
#define SEMANTICO_H_INCLUDED

void erro_Semantico(int codigoErro);
int verificarDeclaracaoVariavel(char *, int , int , int );
int verificarDeclaracao(char *, int);
int temPrototipo(char *, int, int);
int verificarRepetePrototipo(char *);
int verificarRetorno(int);
int verificarFuncaoPrincipal();

#endif // SEMANTICO_H_INCLUDED
