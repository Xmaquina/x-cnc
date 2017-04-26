#ifndef TOKEN_H
#define TOKEN_H


struct token_{
    unsigned int begin;
    unsigned int end;
 
};

typedef struct token_ token; 

struct tk_node_{
    token *elem;
    struct tk_node_ *next;
};

typedef struct tk_node_ tk_node;

struct tk_list_{
    tk_node *head;
    tk_node *tail;
    unsigned int size;
};

typedef struct tk_list_ tk_list;

tk_list * create_list_tk();
int add_tk(tk_list *tl, token *tk);
int add_pair(tk_list *tl, int begin, int end);
int get_token(const char *line, const char *word, tk_list *tl);
token * get_digits_after_token(const char *line, const char *word );
int free_tk_list(tk_list *tl);
#endif
