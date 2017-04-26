#include <stdlib.h>
#include <stdio.h>
#include "token.h"

int test_get_digits_after_token(){
    const char line[] = "G01 X50 ";
	const char word[] = "X";
	printf("Teste get_digit_after_token\n");
	token *tk = get_digits_after_token(line, word);
    if(tk == NULL){
        printf("Get digits after token return NULL\n");
        return 0;
    }
    printf("Begin: %d, end: %d\n", tk->begin, tk->end);
    return 0;
}


int main(int argv, char *argc[]){
 	const char line[] = "Esse e G01 um teste para descobrir o G01 aqui";
	const char word[] = "G01";
	printf("Teste\n");
    token *t = (token *)malloc(sizeof(token));
    t->begin = 10;
    t->end = 5;
    free(t);
    if(t == NULL) printf("OK");
    tk_list *tl = create_list_tk();
	get_token(line, word, tl);
	printf("Size %d\n", tl->size);
    for(tk_node *tk = tl->head; tk != NULL; tk = tk->next){
        token *t = tk->elem;
        printf("Begin: %d, end: %d\n", t->begin, t->end);
    }
    free_tk_list(tl);
    
    test_get_digits_after_token();
    printf("Free deu certo uhuuuumm\n");
	return 0;
}
