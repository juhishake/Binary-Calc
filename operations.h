#ifndef OPERATIONS_H
#define OPERATIONs_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// DLL structure
typedef struct node {
    char data;
    struct node* next;
    struct node* prev;
} node;

// SLL structure
typedef struct List {
        int size;
        char sign;
        node *head;
        node *tail;
} List;

extern int cont;


List changeBase(List num, int k);
void initial(List *num);
int length(List num);
void neg(List *num);
void remove_leading_zeros(List *num);
void destroy(List *num);
void display(List num);
void insert_In_Front(List *num, int value);
void insert_In_End(List *num, int value);
int compare(List L1, List L2);
List add(List *L1, List *L2);
List sub(List *L1, List *L2);
List mult(List *L1, List *L2);
List division(List *l, List *m);
List modulus(List *l, List *m);
List power(List base, List exp);
List fact(List *a);

#endif