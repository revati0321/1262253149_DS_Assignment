#include <stdio.h>
#include <stdlib.h>

struct node
{
    int reg_no;
    char name[100];
    struct node *next;
};

void display(struct node *head)
{
    struct node *temp;
    temp = head->next;
    if (temp == NULL)
    {
        printf("List is empty\n");
        return;
    }
    while (temp != NULL)
    {
        printf("\nRegistration Number: %d", temp->reg_no);
        printf("\nName: %s\n", temp->name);
        temp = temp->next;
    }
}

int count(struct node *head)
{
    struct node *temp;
    temp = head->next;
    int c = 0;
    while (temp != NULL)
    {
        c++;
        temp = temp->next;
    }
    return c;
}

void insertpos(struct node *head)
{
    struct node *temp, *newnode;
    int pos, i;

    printf("Enter position to insert: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > count(head) + 1)
    {
        printf("Invalid position\n");
        return;
    }

    newnode = (struct node *)malloc(sizeof(struct node));

    printf("Enter registration number: ");
    scanf("%d", &newnode->reg_no);

    printf("Enter student name: ");
    scanf(" %s", newnode->name);

    temp = head;

    for (i = 1; i < pos; i++)
        temp = temp->next;

    newnode->next = temp->next;
    temp->next = newnode;

    printf("Student inserted\n");
}

void deletepos(struct node *head)
{
    struct node *temp, *prev;
    int pos, i;

    printf("Enter position to delete: ");
    scanf("%d", &pos);

    if (pos < 1 || pos > count(head))
    {
        printf("Invalid position\n");
        return;
    }

    prev = head;
    temp = head->next;

    for (i = 1; i < pos; i++)
    {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;
    free(temp);

    printf("Student deleted\n");
}

void sort(struct node *head)
{
    struct node *prev, *curr, *nextnode;
    int i, j, n = count(head);

    for (i = 0; i < n - 1; i++)
    {
        prev = head;
        curr = head->next;

        for (j = 0; j < n - i - 1; j++)
        {
            nextnode = curr->next;

            if (curr->reg_no > nextnode->reg_no)
            {
                prev->next = nextnode;
                curr->next = nextnode->next;
                nextnode->next = curr;

                prev = nextnode;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    printf("List sorted\n");
}

void reverse(struct node *head)
{
    struct node *prev, *curr, *nextnode;
    prev = NULL;
    curr = head->next;
    while (curr != NULL)
    {
        nextnode = curr->next;
        curr->next = prev;

        prev = curr;
        curr = nextnode;
    }
    head->next = prev;
    printf("List reversed\n");
}

int main()
{
    struct node *head;
    int choice;

    head = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;

    do
    {
        printf("\n1. Display Students");
        printf("\n2. Count Students");
        printf("\n3. Insert by Position");
        printf("\n4. Delete by Position");
        printf("\n5. Sort Students");
        printf("\n6. Reverse List");
        printf("\n7. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                display(head);
                break;

            case 2:
                printf("Total students: %d\n", count(head));
                break;

            
            case 3:
                insertpos(head);
                break;

            case 4:
                deletepos(head);
                break;

            case 5:
                sort(head);
                break;

            case 6:
                reverse(head);
                break;

            case 7:
                printf("Exiting\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (choice != 7);

    free(head);

    return 0;
}