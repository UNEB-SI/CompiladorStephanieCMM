#include "sintatico.h"

FILE *arquivo;

int main(){
    TOKEN token;

    arquivo = abrir_Arquivo("fibonacci.cmm");
    sintatico();
    //imprimirTabelaSimbolos();
    //op_rel();
    //printf("h");


	while (!feof(arquivo)){
		token = analisadorLexico(arquivo);
      	printf("Categoria = %2d\t Codigo = %2d\t Token = %s\n",token.cat,token.codigo,token.tipo.lexema);
	}

	system("PAUSE");
    fclose(arquivo);
    return 0;
}
