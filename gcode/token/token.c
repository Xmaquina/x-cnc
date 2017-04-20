#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

token * get_token(const char *line, const char word){
	int len = strlen(line);
	int len_word = strlen(word);
	unsigned int begin = 0;
	token *t = (token *)malloc(sizeof(token));
	if(t != NULL) exit(EXIT_FAILURE);
	for(unsigned int i = 0; i < len;i++){
		if(line[i] == word[0] && i + len_word < len){
			for(unsigned int j = 1; j < len_word; j++){
				if(word[j] != line[i+j]){
					break;
				}
			}
				
		}else{
			break;
		}
	}
	
	return t;

}



