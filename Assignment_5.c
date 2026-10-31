#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node
{
    int coef, exp;
    struct node *next;
};

void create(struct node *head, int deg)
{
    struct node *temp = head, *nnode;
    int i;

    for (i = deg; i >= 0; i--)
    {
        nnode = (struct node *)malloc(sizeof(struct node));

        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &nnode->coef, &nnode->exp);

        temp->next = nnode;
        nnode->next = head;
        temp = temp->next;
    }
}

void display(struct node *head)
{
    struct node *temp = head->next;

    while (temp != head)
    {
        printf("%dx^%d", temp->coef, temp->exp);

        temp = temp->next;

        if (temp != head)
            printf(" + ");
    }

    printf("\n");
}

void poly_add(struct node *head1, struct node *head2,
              struct node *head3)
{
    struct node *t1 = head1->next;
    struct node *t2 = head2->next;
    struct node *t3 = head3;
    struct node *ptr;

    while (t1 != head1 && t2 != head2)
    {
        ptr = (struct node *)malloc(sizeof(struct node));
        if (t1->exp == t2->exp)
        {
            ptr->exp = t1->exp;
            ptr->coef = t1->coef + t2->coef;

            t1 = t1->next;
            t2 = t2->next;
        }
        else if (t1->exp > t2->exp)
        {
            ptr->exp = t1->exp;
            ptr->coef = t1->coef;

            t1 = t1->next;
        }
        else
        {
            ptr->exp = t2->exp;
            ptr->coef = t2->coef;

            t2 = t2->next;
        }

        t3->next = ptr;
        ptr->next = head3;
        t3 = t3->next;
    }

    while (t1 != head1)
    {
        ptr = (struct node *)malloc(sizeof(struct node));
        ptr->coef = t1->coef;
        ptr->exp = t1->exp;

        t3->next = ptr;
        ptr->next = head3;
        t3 = t3->next;

        t1 = t1->next;
    }

    while (t2 != head2)
    {
        ptr = (struct node *)malloc(sizeof(struct node));
        ptr->coef = t2->coef;
        ptr->exp = t2->exp;

        t3->next = ptr;
        ptr->next = head3;
        t3 = t3->next;

        t2 = t2->next;
    }
}

void evaluate(struct node *head, int x)
{
    struct node *current = head->next;
    int result = 0;

    while (current != head)
    {
        result += current->coef * (int)pow(x, current->exp);
        current = current->next;
    }

    printf("Result at %d = %d\n", x, result);
}

int main()
{
    struct node *head1, *head2, *head3;
    int deg, x;

    head1 = (struct node *)malloc(sizeof(struct node));
    head2 = (struct node *)malloc(sizeof(struct node));
    head3 = (struct node *)malloc(sizeof(struct node));

    head1->next = head1;
    head2->next = head2;
    head3->next = head3;

    printf("Enter degree of first polynomial: ");
    scanf("%d", &deg);
    create(head1, deg);

    printf("\nEnter degree of second polynomial: ");
    scanf("%d", &deg);
    create(head2, deg);

    printf("\nFirst Polynomial: ");
    display(head1);

    printf("Second Polynomial: ");
    display(head2);

    poly_add(head1, head2, head3);

    printf("Sum of Polynomials: ");
    display(head3);

    printf("\nEnter x to evaluate first polynomial: ");
    scanf("%d", &x);
    evaluate(head1, x);

    printf("\nEnter x to evaluate second polynomial: ");
    scanf("%d", &x);
    evaluate(head2, x);

    printf("\nEnter x to evaluate resultant polynomial: ");
    scanf("%d", &x);
    evaluate(head3, x);

    return 0;
}