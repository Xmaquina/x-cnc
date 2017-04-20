#ifndef TOKEN_H
#define TOKEN_H


struct token_{
    unsigned int begin;
    unsigned int end;
 
};

typedef struct token_ token; 

token * get_token(const char *line, const char *word);

#endif
