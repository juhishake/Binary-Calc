typedef struct Big_node{
        List num;
        struct Big_node* next;
} Big_node;
typedef Big_node* Big_stack;

typedef struct char_node{
        char num;
        struct char_node* next;
} char_node;
typedef char_node* char_stack;


void init_Big_stack(Big_stack *s);
void init_char_stack(char_stack *s);

void push_List(Big_stack *head, List num);
void push_char(char_stack *head, char num);

List pop_List(Big_stack *head);
char pop_char(char_stack *head);

List peek_List(Big_stack st);
char peek_char(char_stack st);

int isEmpty_List(Big_stack st);
int isEmpty_char(char_stack st);
