#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "operations.h"
#include "stack.h"
#include "list.h"

typedef struct get_info {
        char inp_base;
        char out_base;
        char unary_neg;
        char r_ass;
        char prev_token;
        char token;
        char next_token;
} get_info;

extern int cont;
void init_info(get_info *info);
int precedence(char c);
void error(char prev, char next);
int isOperator(char c);
List eval(List *op1, List *op2, char operan);
int get_token(get_info *info, list *inp);

void handle_tokens(get_info *info, list *inp, Big_stack *val);
