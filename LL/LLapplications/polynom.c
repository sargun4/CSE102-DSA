#include <stdio.h>
#include <stdlib.h>

struct node {
    int coeff;
    int power;
    struct node* next;
};

void insert(struct node** head, int coeff, int power) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->coeff = coeff;
    temp->power = power;
    temp->next = *head;
    *head = temp;
}

void display(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) {
        printf("%dx^%d ", temp->coeff, temp->power);
        if (temp->next != NULL) {
            printf("+ ");
        }
        temp = temp->next;
    }
    printf("\n");
}

void addPolynomial(struct node* poly1, struct node* poly2, struct node** result) {
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->power > poly2->power) {
            insert(result, poly1->coeff, poly1->power);
            poly1 = poly1->next;
        } else if (poly1->power < poly2->power) {
            insert(result, poly2->coeff, poly2->power);
            poly2 = poly2->next;
        } else {
            insert(result, poly1->coeff + poly2->coeff, poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next; 
        }
    }
    while (poly1 != NULL) {
        insert(result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insert(result, poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }
}
void multiplyPolynomial(struct node* poly1, struct node* poly2, struct node** result) {
    struct node* temp = NULL;
    while (poly1 != NULL) {
        temp = poly2;
        while (temp != NULL) {
            int coeff = poly1->coeff * temp->coeff;
            int power = poly1->power + temp->power;
            insert(result, coeff, power);
            temp = temp->next;
        }
        poly1 = poly1->next;
    }
    simplify(result);
}
void subtractPolynomial(struct node* poly1, struct node* poly2, struct node** result) {
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->power > poly2->power) {
            insert(result, poly1->coeff, poly1->power);
            poly1 = poly1->next;
        } else if (poly1->power < poly2->power) {
            insert(result, -poly2->coeff, poly2->power);
            poly2 = poly2->next;
        } else {
            insert(result, poly1->coeff - poly2->coeff, poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        insert(result, poly1->coeff, poly1->power);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insert(result, -poly2->coeff, poly2->power);
        poly2 = poly2->next;
    }
    simplify(result);
}
void dividePolynomial(struct node* dividend, struct node* divisor, struct node** quotient, struct node** remainder) {
    *quotient = NULL;
    *remainder = NULL;
    struct node* temp = NULL;
    while (dividend != NULL && dividend->power >= divisor->power) {
        int coeff = dividend->coeff / divisor->coeff;
        int power = dividend->power - divisor->power;
        insert(quotient, coeff, power);
        temp = multiply(divisor, coeff, power);
        subtract(dividend, temp, &dividend);
        freeList(temp);
    }
    *remainder = dividend;
    simplify(quotient);
    simplify(remainder);
}
void differentiatePolynomial(struct node* poly, struct node** result) {
    while (poly != NULL) {
        if (poly->power > 0) {
            int coeff = poly->coeff * poly->power;
            int power = poly->power - 1;
            insert(result, coeff, power);
        }
        poly = poly->next;
    }
    simplify(result);
}
void integratePolynomial(struct node* poly, struct node** result) {
    while (poly != NULL) {
        int coeff = poly->coeff / (poly->power + 1);
        int power = poly->power + 1;
        insert(result, coeff, power);
        poly = poly->next;
    }
    simplify(result);
}

int evaluatePolynomial(struct node* poly, int x) {
    int result = 0;
    while (poly != NULL) {
        result += poly->coeff * pow(x, poly->power);
        poly = poly->next;
    }
    return result;
}

int degree(struct node* poly) {
    int maxPower = 0;
    while (poly != NULL) {
        if (poly->power > maxPower) {
            maxPower = poly->power;
        }
        poly = poly->next;
    }
    return maxPower;
}

int main() {
    struct node* poly1 = NULL;
    struct node* poly2 = NULL;
    struct node* result = NULL;

    insert(&poly1, 3, 2);
    insert(&poly1, 4, 1);
    insert(&poly1, 2, 0);

    insert(&poly2, 2, 2);
    insert(&poly2, 5, 1);
    insert(&poly2, 1, 0);

    printf("First polynomial: ");
    print(poly1);

    printf("Second polynomial: ");
    print(poly2);

    add(poly1, poly2, &result);
    printf("Sum: ");
    print(result);

    subtract(poly1, poly2, &result);
    printf("Difference: ");
    print(result);

    multiply(poly1, poly2, &result);
    printf("Product: ");
    print(result);

    return 0;
}

