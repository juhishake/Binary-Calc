#include "list.h"

void init(list *l) {
    *l = NULL;
    return;
}


void traverse(list l){
    list_node *p;
    p = l;
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    return;
}

int get_next(list *l){ 
    list p = *l;
    if(!p)
        return INT_MAX;
    int k = p->data;
    *l = p->next;
    free(p);
    return k;
}

int touch(list l) {
    if(!l)
        return INT_MAX;
    return l->data;
}

void append(list *l, int d){
    list p, nn;
    nn = (list_node*)malloc(sizeof(list_node));
    if(nn){
        nn->data = d;
        nn->next = NULL;
    }
    else return;
    if(*l == NULL){
        *l = nn;
        return;
    }
    p = *l;
    while(p -> next) {
       p = p->next;
    }
    p->next = nn;
    return;
}

void insert_beg(list *l, int d){
    list nn;
    nn = (list_node*)malloc(sizeof(list_node));
    if(nn){
        nn->data = d;
        nn->next = NULL;
    }
    else return;
    nn->next = *l;
    *l = nn;
    return;
}

int isempty(list l){
    if(l == NULL)
        return 1;
    else
        return 0;
}

void destroy_list(list *l){
    list_node *p = *l;
    list_node * q;
    q = p;
    while(p){
        p = p->next;
        free(q);
    }
    *l = NULL;
    return;
}
