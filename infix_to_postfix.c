#include <stdio.h>
#include <ctype.h>
#include <string.h> 

#define MAX 100 

char stack[MAX];
int top = -1;


void push(char x) {
    if (top < MAX - 1) {
        stack[++top] = x;
    } else {
        printf("Stack overflow\n");
    }
}


char pop() {
    if (top != -1) {
        return stack[top--];
    }
    return -1;
}


char peek() {
    if (top != -1) {
        return stack[top];
    }
    return -1;
}


int precedence(char x) {
    if (x == '+' || x == '-') {
        return 1;
    } else if (x == '*' || x == '/') {
        return 2;
    }
    return 0;
}


int isOperator(char x) {
    return (x == '+' || x == '-' || x == '*' || x == '/');
}


void infixToPostfix(char *infix) {
    char postfix[MAX];
    int j = 0;

    for (int i = 0; i < strlen(infix); i++) {
        char token = infix[i];

        if (isalpha(token) || isdigit(token)) {

            postfix[j++] = token;
        } else if (token == '(') {

            push(token);
        } else if (token == ')') {

            while (top != -1 && peek() != '(') {
                postfix[j++] = pop();
            }
            pop();
        } else if (isOperator(token)) {

            while (top != -1 && precedence(peek()) >= precedence(token)) {
                postfix[j++] = pop();
            }
            push(token);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);
}

int main() {
    char infix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
