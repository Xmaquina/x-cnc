#include <stdlib.h>
#include <stdio.h>
#include "token.h"


int main(int argv, char *argc[]){
 	const char line[] = "Esse e um teste para descobrir o G01 aqui";
	const char word[] = "G01";
	printf("Teste\n");
	token * t = get_token(line, word);
	printf("Begin %d, %d\n", t->begin, t->end);
	return 0;
}
