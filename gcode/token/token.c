#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

tk_list * create_list(){
    tk_list *tk = (tk_list *) malloc(sizeof(tk_list));
    if(tk != NULL){
        tk->size = 0;
        tk->head = NULL;
    }
    return tk;
}

tk_node * create_node(token *tk){
    tk_node * tn = (tk_node *) malloc(sizeof(tk_node));
    if(tn != NULL){
        tn->elem = tk;
        tn->next = NULL; 
    }
    return tn;
}



int add(tk_list *tl, token *tk){
    tk_node *new = create_node(tk);

    if(tl->size == 0){
        tl->head = new;
    }else{
        tk_node *last = tl->head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = new;
    }
    tl->size++;
    return 0;
}

int add_pair(tk_list *tl, int begin, int end){
    token *tk = (token *)malloc(sizeof(token));
    if(tk == NULL) exit(EXIT_FAILURE);
    tk->begin = begin;
    tk->end = end;
    add(tl, tk);
    return 0;
}

int get_token(const char *line, const char *word, tk_list *tl){
	int len = strlen(line);
	int len_word = strlen(word);
	unsigned int begin = 0;
	for(unsigned int i = 0; i < len;i++){
		if(line[i] == word[0]){
			begin = 1;
			for(unsigned int j = 1; j < len_word; j++){
				if(word[j] != line[i+j]){
					begin = 0;
					break;
				}
			}
			if(begin == 1) add_pair(tl, i, i+len_word-1); 
                
				
		}
	}
	
	return 1;

}



