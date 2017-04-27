#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "../xcncmacros.h"

tk_list * create_list_tk(){
    tk_list *tk = (tk_list *) malloc(sizeof(tk_list));
    if(tk != NULL){
        tk->size = 0;
        tk->head = NULL;
    }
    return tk;
}

int free_tk_list(tk_list *tl){
    if(tl != NULL){
        tk_node *temp;
        while(tl->head != NULL){
            temp = tl->head;
            tl->head = tl->head->next;
            free(temp->elem);
            free(temp);
        }
        free(tl); 
    }
    return 0; 
}

tk_node * create_node_tk(token *tk){
    tk_node * tn = (tk_node *) malloc(sizeof(tk_node));
    if(tn != NULL){
        tn->elem = tk;
        tn->next = NULL; 
    }
    return tn;
}



int add_tk(tk_list *tl, token *tk){
    tk_node *new = create_node_tk(tk);

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
    add_tk(tl, tk);
    return 0;
}

int get_token(const char *line, const char *word, tk_list *tl){
	int len = strlen(line);
	int len_word = strlen(word);
    if(len_word == 0 || len == 0){
        fprintf(stderr, "Len word %d or len line %d\n", len_word, len); 
        return 1;
    }
//printf("workd %s\n", word);
	unsigned int begin = 0;
	for(unsigned int i = 0; i < len;i++){
//printf("Line i %c %c\n",line[i], word[0]); 
		if(line[i] == word[0]){
//printf("Aqui\n");
			begin = 1;
			for(unsigned int j = 1; j < len_word; j++){
//printf("word j %c %c\n",line[i+j], word[j]); 
				if(word[j] != line[i+j]){
					begin = 0;
					break;
				}
			}
			if(begin == 1) add_pair(tl, i, i+len_word-1); 
                
				
		}
	}
	
	return 0;

}


int int_after_token(const char *text, const char *word, int space, int *num){
    token * tk =  get_digits_after_token(text, word, space);
    if(tk != NULL){
        int size_num = tk->end - tk->begin + 1;
        char *c = malloc(sizeof(char) * size_num);
        memset(c,'\0', size_num);
        strncpy(c, text+tk->begin, size_num);
//printf("c: %s\n", c);
        *(num) = atoi(c);
        return 0;
    }
    return 1;

}

token * get_digits_after_token(const char *line, const char *word, int space ){
    tk_list *tl = create_list_tk();
    get_token(line, word, tl);
	int len = strlen(line);
    if(tl->size == 1){
        int begin = tl->head->elem->end; 
        if(space == 1){
            begin += 2;
        }else{
            begin += 1;
        }
        int i = begin;
//printf("i %d\n", i);
        for(; i < len; i++){
            if(!isdigit(line[i])){
                break;
            }
        }
//printf("len line %d\n", len);
        token *tk = malloc(sizeof(token));
        if(tk == NULL) return NULL;
        tk->begin = begin;
        tk->end = i - 1;
//printf("Value of %d\n", i);
        free_tk_list(tl);
        return tk; 
    }
	return NULL;

}
