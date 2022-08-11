#include "operations.h"

void initial(List *num) {
	num->size = 0;
	num->sign = 0;
	num->head = NULL;
    num->tail = NULL;
}

//length of list
int length(List num) {
    return num.size;
}


//sign changer
void neg(List *num) {
	//if negative
	if(num->sign)
		num->sign = 0;
	//if positive
	else
		num->sign = 1;
}


//removing zero from start of list
void remove_leading_zeros(List *num) {
    node* temp = num->head;
    node* follow;
    int count = 0;
    List new;
    initial(&new);

    while (temp && temp->data == 0) {
	follow = temp;
        temp = temp->next;
	free(follow);
	count++;
    }
    if(temp == NULL) {
	    *num = new;
	    return;
    }
    temp->prev = NULL;
    num->head = temp;
    num->size = num->size - count;
    return;
}


//detroying list
void destroy(List *num)  {
    node* temp = num->head;
    node* follow = NULL;
    List new;
    initial(&new);
    *num = new;
    while (temp) {
        follow = temp;
        temp = temp->next;
        free(follow);
    }
    return;
}


List changeBase(List num, int k) {
    int sign= 0;

    if (k == 10)
	    return num;

    List newbase, temp = num, dec, base, mod, tmpfree;
    initial(&newbase);
    initial(&dec);
    initial(&base);
    initial(&mod);
    initial(&tmpfree);

    /*if num is 0, return 0*/
    if (temp.size == 0)
	    return newbase;
    /*if num is neg, convert to positive and 
     * change output sign at last*/
    if (temp.sign == 1) {
	    temp.sign = 0;
	    sign= 1;
    }
    /*to store 10 which will be used in furthur 
     * arithematic operations*/
    insert_In_End(&dec, 1);
    insert_In_End(&dec, 0);

    /*if base is 2 digit no*/
    if(k > 9) {
	insert_In_End(&base, k / 10);
	insert_In_End(&base, k % 10);
    }
    /*if base is 1 digit no*/
    else
	insert_In_Front(&base, k);

    int count = 0;
    while (temp.size != 0) {
	    count++;
        mod = modulus(&temp, &base);
	int comp = compare(mod, dec);
	/*if mod value is greater or equal to 10,
	 * insert 2 digits*/
	if((comp == 0 || comp == 1)&& mod.head)
		insert_In_Front(&newbase, mod.head->data*10 + mod.head->next->data);
	/*else insert 1 digit*/
	else if(mod.head)
		insert_In_Front(&newbase, mod.head->data);
	else
		insert_In_Front(&newbase, 0);

        temp= division(&temp, &base);
	destroy(&tmpfree);
	tmpfree = temp;
	destroy(&mod);
    }
    
    destroy(&base);
    destroy(&dec);
    newbase.sign = sign;
    return newbase;
}

//displaying list
void display(List num) {
    node* temp = num.head;
    if(num.size == 0) {
	    printf("0\n");
	    return;
    }
    if(num.sign)
	    printf("-");
    while (temp)
        	printf("%c", temp->data + '0');
    printf("\n");
    return;
}


//inserting node at front
void insert_In_Front(List *num, int value) {
    node* temp = (node*)malloc(sizeof(node));
    temp->next = temp->prev = NULL;
	temp->data = value;
    
    if (num->head == NULL)
        num->head = num->tail = temp;
    else {
        num->head->prev = temp;
        temp->next = num->head;
        num->head = temp;
    }

    num->size = num->size+1;
}


//inserting node at back
void insert_In_End(List *num, int value) {
    node* temp = (node*)malloc(sizeof(node));
    temp->next = temp->prev = NULL;
    temp->data = value;

    if (num->tail == NULL)
        num->head = num->tail = temp;
    else {
        num->tail->next = temp;
        temp->prev = num->tail;
        num->tail = temp;
    }

    num->size = num->size+1;
}


//comparing length of two numbers
int compare(List L1, List L2) {

    remove_leading_zeros(&L1);
    remove_leading_zeros(&L2);

    List l1 = L1;
    List l2 = L2;

    int rev = 0;

    if(l1.sign != l2.sign) {
	    if(l2.sign)
		    return 1;
	    else
		    return 2;
    }

    else if(l1.sign)
	    rev = 1;


    if (l1.size != l2.size) {
	if(! rev)
        	return ((l1.size > l2.size) ? 1 : 2);
	else
		return ((l1.size > l2.size) ? 2 : 1);
    }

    else {
        while (l1.head != NULL && l2.head != NULL) {
            if (l1.head->data > l2.head->data) {
		if(! rev)
                	return 1;
	    	else
			return 2;
	    }
            else if (l1.head->data < l2.head->data) {
		if(! rev)
                	return 2;
		else
			return 1;
	    }
            else {
                l1.head = l1.head->next;
                l2.head = l2.head->next;
            }
        }

        return 0;
    }
}


//adding
List add(List *L1, List *L2) {
    remove_leading_zeros(L1);
    remove_leading_zeros(L2);

    List l1 = *L1;
    List l2 = *L2;
    int carry = 0, s;
    List addition;
    initial(&addition);

    if(l1.sign != l2.sign) {
            if(l1.sign == 0) {
                neg(&l2);
                return sub(&l1, &l2);
            }
            else {
                neg(&l1);
                return sub(&l2, &l1);
            }
    }
    else
        addition.sign = l1.sign;

    while (l1.tail != NULL || l2.tail != NULL) {
        if (l1.tail != NULL && l2.tail != NULL) {
            s = ((l1.tail->data) + (l2.tail->data) + carry) % 10;
            carry = ((l1.tail->data) + (l2.tail->data) + carry) / 10;
            l1.tail = l1.tail->prev;
            l2.tail = l2.tail->prev;
        }
        else if (l1.tail == NULL && l2.tail != NULL) {
            s = ((l2.tail->data) + carry) % 10;
            carry = ((l2.tail->data) + carry) / 10;
            l2.tail = l2.tail->prev;
        }
        else if (l1.tail != NULL && l2.tail == NULL) {
            s = ((l1.tail->data) + carry) % 10;
            carry = ((l1.tail->data) + carry) / 10;
            l1.tail = l1.tail->prev;
        }
        insert_In_Front(&addition, s);
    }
    if (carry != 0)
        insert_In_Front(&addition, carry);
    return addition;
}


//subtracting
List sub(List *L1, List *L2) {
    remove_leading_zeros(L1);
    remove_leading_zeros(L2);
    List l1 = *L1;
    List l2 = *L2;

    int carry = 0, s, ressign = 0;
    List subtraction, temp;
    initial(&subtraction);

    if(l1.sign != l2.sign) {
            if(l1.sign == 0) {
                neg(&l2);
                return add(&l1, &l2);
            }
            else {
                neg(&l2);
                return add(&l1, &l2);
            }
    }

    else if(l1.sign &&  l2.sign){
            neg(&l1);
            neg(&l2);
            ressign = 1;
    }

    int cmp = compare(l1, l2);

    if(! cmp)
            return subtraction;

    if(cmp == 2) {
	    neg(&subtraction);
            temp = l1;
            l1 = l2;
            l2 = temp;
    }

    while (l1.tail != NULL || l2.tail != NULL) {
        if (l1.tail != NULL && l2.tail != NULL) {
            if ((l1.tail->data) + carry >= (l2.tail->data)) {
                s = ((l1.tail->data) + carry - (l2.tail->data));
                carry = 0;
            }
            else {
                s = ((l1.tail->data) + carry + 10 - (l2.tail->data));
                carry = -1;
            }
            l1.tail = l1.tail->prev;
            l2.tail = l2.tail->prev;
        }
        else if (l1.tail != NULL && l2.tail == NULL) {
            if (l1.tail->data >= 1) {
                s = ((l1.tail->data) + carry);
                carry = 0;
            }
            else {
                if (carry != 0) {
                    s = ((l1.tail->data) + 10 + carry);
                    carry = -1;
                }
                else
                    s = l1.tail->data;
            }
            l1.tail = l1.tail->prev;
        }
        insert_In_Front(&subtraction, s);
    }
    remove_leading_zeros(&subtraction);
    if(ressign) {
        neg(&subtraction);
        return subtraction;
    }
    return subtraction;
}


//multiplying
List mult(List *l, List *m) {
    remove_leading_zeros(l);
    remove_leading_zeros(m);
    List l1 = *l;
    List l2 = *m;
    int sign = 0;

    if(l1.sign != l2.sign)
	    sign = 1;

    int k = 0, i, count = 0;
    List multiplican, temp, a, b;
    initial(&multiplican);
    initial(&temp);

    if(l1.size == 0 || l2.size == 0)
	   return multiplican;
    b = l2;
    while (b.tail != NULL) {
        int carry = 0, s = 0;
	a = l1;

        while (a.tail != NULL) {
            s = ((a.tail->data) * (b.tail->data) + carry) % 10;
            carry = ((a.tail->data) * (b.tail->data) + carry) / 10;

            insert_In_Front(&temp, s);
            a.tail = a.tail->prev;
        }
        if (carry != 0)
            insert_In_Front(&temp, carry);
        for (i = 0; i < k; i++)
            insert_In_End(&temp, 0);
        k++;
	        b.tail = b.tail->prev;
	destroy(&temp);
    }

    multiplican.sign = sign;
    return multiplican;
}


//dividing
List division(List *l, List *m) {
    remove_leading_zeros(l);
    remove_leading_zeros(m);
    List l1 = *l;
    List l2 = *m;
    List one;
    initial(&one);
    insert_In_End(&one, 1);

    int sign = 0;

    if(l1.sign != l2.sign)
	    sign = 1;

    List ex, mp, pr, a = l1, b = l2, b2, tmpfree, quotient;
    int cont;
    initial(&ex);
    initial(&mp);
    initial(&pr);
    initial(&quotient);

    if(l2.size == 0){
	printf("Can't divide with zero");
	cont = 1;
	return ex;
    }

    int cmp = compare(l1, l2);

    if(cmp == 2)
	    return quotient;

    else if(cmp == 0) {
	    one.sign = sign;
	    return one;
    }
    int i = 0;
    for (i = 0; i < l2.size && l1.head; i++) {
        insert_In_End(&ex, l1.head->data);
	l1.head = l1.head->next;
    }

    for (i = 1; i < 10; i++) {
        b2 = b;
        insert_In_End(&mp, i);
        pr = mult(&b2, &mp);
        if (compare(ex, pr) == 2)
            break;
        destroy(&mp);
	destroy(&pr);
    }
    int multiplier = i - 1;

    destroy(&mp);
    destroy(&pr);

    insert_In_End(&mp, multiplier);
    pr = mult(&l2, &mp);
    tmpfree = ex;
    ex = sub(&ex, &pr);
    destroy(&tmpfree);

    insert_In_End(&quotient, multiplier);
    remove_leading_zeros(&quotient);

    destroy(&mp);
    destroy(&pr);

    int count = 0;
    while(l1.head != NULL) {
        insert_In_End(&ex, l1.head->data);
	remove_leading_zeros(&ex);

        for (i = 1; i < 10; i++) {
            b2 = b;
            insert_In_End(&mp, i);
            pr = mult(&b2, &mp);
            if (compare(ex, pr) == 2)
                break;

	    destroy(&mp);
	    destroy(&pr);
        }
	multiplier = i - 1;

	destroy(&mp);
	destroy(&pr);

        insert_In_End(&mp, multiplier);
        pr = mult(&l2, &mp);
        tmpfree = ex;
    	ex = sub(&ex, &pr);
    	destroy(&tmpfree);

        insert_In_End(&quotient, multiplier);

	destroy(&mp);
	destroy(&pr);

        l1.head = l1.head->next;
    }

    if(a.sign != b.sign) {
    	quotient.sign = 1;
    }

    destroy(&ex);
    remove_leading_zeros(&quotient);
    quotient.sign = sign;
    return quotient;
}


//modulus
List modulus(List *l, List *m) {
    //a % b = a - (b * a/b)
    List divi, multipln;
    divi = division(l, m);
    multipln = mult(m, &divi);
    return sub(l, &multipln);
}


//power
List power(List base, List exp){
	List t, res, two, tmp_free, tfree, temp, frexp;
	initial(&res);
	initial(&two);
	initial(&tfree);
	initial(&frexp);

	insert_In_End(&two, 2);

	insert_In_End(&res, 1);
	t = base;
	while(exp.size > 0) {
		temp = modulus(&exp, &two);
		if(temp.size == 1){
			tmp_free = res;
			res = mult(&res, &t);
			destroy(&tmp_free);
		}
		destroy(&temp);

		exp = division(&exp, &two);
		destroy(&frexp);
		frexp = exp;

		if(exp.size)
			t = mult(&t, &t);
                destroy(&tfree);
                tfree = t;
	}

	destroy(&two);
	return res;
}

//factorial
List fact(List *num) {
	remove_leading_zeros(num);
	List res, a = *num, one, free_a;
	initial(&res);
	initial(&one);
	initial(&free_a);

	insert_In_End(&one, 1);
	insert_In_End(&res, 1);

	if(a.size == 0)
		return one;
	else if(a.sign == 1) {
		printf("negativ enumber factorial not possible");
	}

	while (a.size != 0) {
		res = mult(&res, &a);
		a = sub(&a, &one);
		destroy(&free_a);
		free_a = a;
	}

	destroy(&one);
	return res;
}