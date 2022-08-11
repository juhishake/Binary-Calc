#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include "stack.h"

void init_Big_stack(Big_stack *s) {
	*s = NULL;
}
void init_char_stack(char_stack *s) {
    *s = NULL;
}


void push_List(Big_stack *head, List num) {
    Big_stack nn;
    nn = (Big_node*)malloc(sizeof(Big_node));
    if(nn) {
        nn->num = num;
        nn->next = NULL;
	}
    else return;

    if(*head == NULL) {
        *head = nn;
        return;
	}
    nn->next = *head;
    *head = nn;
    return;
}
void push_char(char_stack *head, char num) {
    char_stack nn;
    nn = (char_node*)malloc(sizeof(char_node));
    if(nn) {
        nn->num = num;
        nn->next = NULL;
    }
    else return;

    if(*head == NULL) {
        *head = nn;
        return;
    }
    nn->next = *head;
    *head = nn;
    return;
}


List pop_List(Big_stack *head) {
    List empty, num;
    Big_stack temp;
        /*To indicate stack is empty*/
    empty.sign = -1;
    if (*head == NULL)
            /*current token*/
        return empty;
    temp = *head;
    num = (*head)->num;
    *head = (*head)->next;
    free(temp);
    return num;
}
char pop_char(char_stack *head) {
	char empty, num;
	char_stack temp;
	/*To indicate stack is empty*/
	empty = 255;
	if (*head == NULL)
		return empty;
	temp = *head;
	num = (*head)->num;
	*head = (*head)->next;
	free(temp);
	return num;
}


List peek_List(Big_stack st) {
	if(st)
		return st->num;
	else{
		List tmp;
		tmp.sign = -128;
		return tmp;
	}
}
char peek_char(char_stack st) {
    if(st)
         return st->num;
	else return -128;
}



int isEmpty_List(Big_stack st) {
    if(peek_List(st).sign == -128)
        return 1;
	else return 0;
}
int isEmpty_char(char_stack st) {
	if(peek_char(st) == -128){
		return 1;}
	else return 0;
}