
#ifndef LIST_H
#define LIST_H

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct list_node{
    int data;
    struct list_node *next;
}list_node;

typedef list_node* list;

void init(list *l);
void traverse(list l);
int get_next(list *l);
int touch(list l);
void append(list *l, int d);
void insert_beg(list *l,int d);
int isempty(list l);
void destroy_list(list *l);

#endif