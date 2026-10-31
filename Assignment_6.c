#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define size 20

int top = -1;
char stk[size];

int isfull()
{
    if (top == size - 1)
        return 1;
    else
        return 0;
}

int isempty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

void push(char elem)
{
    top++;
    stk[top] = elem;
}

char pop()
{
    char ch;
    ch = stk[top];
    top--;
    return ch;
}

void display()
{
    printf("Stack Elements:\n");
    for (int i = top; i >= 0; i--)
        printf("%c\n", stk[i]);
}

// Incoming Priority Function (ICP)
int icp(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '^')
        return 3;
    if (ch == '(')
        return 5;
    return 0;
}

// In-Stack Priority Function (ISP)
int isp(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '^')
        return 4;
    if (ch == '(')
        return 0;
    return 0;
}

void infixtopostfix(char infix[], char postfix[])
{
    int i = 0, k = 0;
    char tkn;

    top = -1;

    while (infix[i] != '\0')
    {
        tkn = infix[i];

        if (isalnum((unsigned char)tkn))
        {
            postfix[k++] = tkn;
        }
        else if (tkn == '(')
        {
            push(tkn);
        }
        else if (tkn == ')')
        {
            while (!isempty() && stk[top] != '(')
            {
                postfix[k++] = pop();
            }

            if (!isempty())
                pop();
        }
        else
        {
            while (!isempty() && stk[top] != '(' &&
                   (isp(stk[top]) > icp(tkn) ||
                   (isp(stk[top]) == icp(tkn) && tkn != '^')))
            {
                postfix[k++] = pop();
            }

            push(tkn);
        }

        i++;
    }

    while (!isempty())
    {
        postfix[k++] = pop();
    }

    postfix[k] = '\0';
}

void infixtoprefix(char infix[], char prefix[])
{
    char rev[20], temp[20];
    int i, len;

    len = strlen(infix);

    for (i = 0; i < len; i++)
    {
        if (infix[len - 1 - i] == '(')
            rev[i] = ')';
        else if (infix[len - 1 - i] == ')')
            rev[i] = '(';
        else
            rev[i] = infix[len - 1 - i];
    }

    rev[len] = '\0';

    top = -1;
    int k = 0;

    for (i = 0; rev[i] != '\0'; i++)
    {
        char ch = rev[i];

        if (isalnum((unsigned char)ch))
            temp[k++] = ch;
        else if (ch == '(')
            push(ch);
        else if (ch == ')')
        {
            while (!isempty() && stk[top] != '(')
                temp[k++] = pop();

            if (!isempty())
                pop();
        }
        else
        {
            while (!isempty() && stk[top] != '(' &&
                   (isp(stk[top]) > icp(ch) ||
                   (isp(stk[top]) == icp(ch) && ch == '^')))
                temp[k++] = pop();

            push(ch);
        }
    }

    while (!isempty())
        temp[k++] = pop();

    temp[k] = '\0';

    len = strlen(temp);

    for (i = 0; i < len; i++)
        prefix[i] = temp[len - 1 - i];

    prefix[len] = '\0';
}

void prefixtopostfix(char prefix[], char postfix[])
{
    char stack[20][100];
    char op1[100], op2[100];
    int t = -1;
    int i;

    for (i = strlen(prefix) - 1; i >= 0; i--)
    {
        char ch = prefix[i];

        if (isalnum((unsigned char)ch))
        {
            stack[++t][0] = ch;
            stack[t][1] = '\0';
        }
        else
        {
            strcpy(op1, stack[t--]);
            strcpy(op2, stack[t--]);

            sprintf(stack[++t], "%s%s%c", op1, op2, ch);
        }
    }

    strcpy(postfix, stack[t]);
}

void postfixtoprefix(char postfix[], char prefix[])
{
    char stack[20][100];
    char op1[100], op2[100];
    int t = -1;
    int i;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];

        if (isalnum((unsigned char)ch))
        {
            stack[++t][0] = ch;
            stack[t][1] = '\0';
        }
        else
        {
            strcpy(op2, stack[t--]);
            strcpy(op1, stack[t--]);

            sprintf(stack[++t], "%c%s%s", ch, op1, op2);
        }
    }

    strcpy(prefix, stack[t]);
}

void prefixtoinfix(char prefix[], char infix[])
{
    char stack[20][100];
    char op1[100], op2[100];
    int t = -1;
    int i;

    for (i = strlen(prefix) - 1; i >= 0; i--)
    {
        char ch = prefix[i];

        if (isalnum((unsigned char)ch))
        {
            stack[++t][0] = ch;
            stack[t][1] = '\0';
        }
        else
        {
            strcpy(op1, stack[t--]);
            strcpy(op2, stack[t--]);

            sprintf(stack[++t], "(%s%c%s)", op1, ch, op2);
        }
    }

    strcpy(infix, stack[t]);
}

void postfixtoinfix(char postfix[], char infix[])
{
    char stack[20][100];
    char ch, op1[100], op2[100];
    int t = -1, i;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if (isalnum((unsigned char)ch))
        {
            stack[++t][0] = ch;
            stack[t][1] = '\0';
        }
        else
        {
            strcpy(op2, stack[t--]);
            strcpy(op1, stack[t--]);

            sprintf(stack[++t], "(%s%c%s)", op1, ch, op2);
        }
    }

    strcpy(infix, stack[t]);
}

int main()
{
    int choice;
    char c;
    char infix[100], postfix[100], prefix[100];

    do
    {
        printf("\n1. Push");
        printf("\n2. Pop");
        printf("\n3. Display");
        printf("\n4. Infix to Postfix");
        printf("\n5. Infix to Prefix");
        printf("\n6. Postfix to Infix");
        printf("\n7. Prefix to Infix");
        printf("\n8. Postfix to Prefix");
        printf("\n9. Prefix to Postfix");
        printf("\n10. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (isfull())
                    printf("Stack is full\n");
                else
                {
                    printf("Enter character: ");
                    scanf(" %c", &c);
                    push(c);
                }
                break;

            case 2:
                if (isempty())
                    printf("Stack is empty\n");
                else
                    printf("Popped element = %c\n", pop());
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Enter Infix expression: ");
                scanf("%99s", infix);
                infixtopostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 5:
                printf("Enter Infix expression: ");
                scanf("%99s", infix);
                infixtoprefix(infix, prefix);
                printf("Prefix Expression: %s\n", prefix);
                break;

            case 6:
                printf("Enter Postfix expression: ");
                scanf("%99s", postfix);
                postfixtoinfix(postfix, infix);
                printf("Infix Expression: %s\n", infix);
                break;

            case 7:
                printf("Enter Prefix expression: ");
                scanf("%99s", prefix);
                prefixtoinfix(prefix, infix);
                printf("Infix Expression: %s\n", infix);
                break;

            case 8:
                printf("Enter Postfix expression: ");
                scanf("%99s", postfix);
                postfixtoprefix(postfix, prefix);
                printf("Prefix Expression: %s\n", prefix);
                break;

            case 9:
                printf("Enter Prefix expression: ");
                scanf("%99s", prefix);
                prefixtopostfix(prefix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 10:
                printf("Thank you\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while (choice != 10);

    return 0;
}