#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

token * get_token(const char *line, const char *word){
	int len = strlen(line);
	int len_word = strlen(word);
	unsigned int begin = 0;
	unsigned int *places = (unsigned int *)malloc(sizeof(unsigned int)*len);
	token *t = (token *)malloc(sizeof(token));
	if(t != NULL) exit(EXIT_FAILURE);
	for(unsigned int i = 0; i < len;i++){
		if(line[i] == word[0] && i + len_word < len){
			begin = 1;
			t->begin = i;
			for(unsigned int j = 1; j < len_word; j++){
				if(word[j] != line[i+j]){
					begin = 0;
					break;
				}
			}
			if(begin == 1) t->end = i + len_word;
				
		}else{
			break;
		}
	}
	
	return t;

}



