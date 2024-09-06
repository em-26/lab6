#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure for operators
struct Stack {
    int top;
    char arr[MAX];
};

void push(struct Stack* stack, char op) {
    stack->arr[++(stack->top)] = op;
}

char pop(struct Stack* stack) {
    if (stack->top == -1) {
        return -1;
    }
    return stack->arr[(stack->top)--];
}

char peek(struct Stack* stack) {
    return stack->arr[stack->top];
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack stack;
    stack.top = -1;
    int k = 0;  // index for postfix

    for (int i = 0; infix[i]; i++) {
        if (isspace(infix[i])) continue;  // Ignore spaces

        // If the character is a digit, add it to the output
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';  // Add a space after the number
            i--;  // Correct for the last increment
        }
        // If the character is '(', push it onto the stack
        else if (infix[i] == '(') {
            push(&stack, '(');
        }
        // If the character is ')', pop and output from the stack until '(' is found
        else if (infix[i] == ')') {
            while (stack.top != -1 && peek(&stack) != '(') {
                postfix[k++] = pop(&stack);
                postfix[k++] = ' ';
            }
            pop(&stack);  // Pop '(' from stack
        }
        // If the character is an operator
        else if (isOperator(infix[i])) {
            while (stack.top != -1 && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[k++] = pop(&stack);
                postfix[k++] = ' ';
            }
            push(&stack, infix[i]);
        }
    }

    // Pop all the remaining operators from the stack
    while (stack.top != -1) {
        postfix[k++] = pop(&stack);
        postfix[k++] = ' ';
    }

    postfix[k - 1] = '\0';  // Null terminate the string
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strlen(infix) - 1] = '\0';  // Remove the newline character

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
