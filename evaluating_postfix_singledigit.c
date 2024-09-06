#include <stdio.h>
#include <ctype.h>  // For isdigit()
#include <stdlib.h> // For atoi()

#define MAX 100  // Maximum size for stack

// Stack structure and functions for evaluation
struct Stack {
    int top;
    int items[MAX];
};

void push(struct Stack* s, int value) {
    if (s->top < MAX - 1)
        s->items[++(s->top)] = value;
    else
        printf("Stack Overflow!\n");
}

int pop(struct Stack* s) {
    if (s->top != -1)
        return s->items[(s->top)--];
    else {
        printf("Stack Underflow!\n");
        return -1;
    }
}

// Function to perform the arithmetic operation
int operate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

// Function to evaluate a postfix expression with multi-digit numbers
int evaluatePostfix(char* postfix) {
    struct Stack s;
    s.top = -1;

    int i = 0;
    while (postfix[i] != '\0') {
        char token = postfix[i];

        // If the token is a digit, read the entire number (support multi-digit numbers)
        if (isdigit(token)) {
            int num = 0;

            // Keep reading digits to form the complete number
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            push(&s, num);  // Push the entire number to the stack
        }
        // If the token is an operator, pop two operands, perform the operation, and push the result
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            int result = operate(operand1, operand2, token);
            push(&s, result);
            i++;  // Move to the next character
        }
        // Skip any spaces between numbers and operators
        else {
            i++;
        }
    }

    // The final result will be at the top of the stack
    return pop(&s);
}

int main() {
    char postfix[MAX];

    printf("Enter postfix expression with spaces between numbers and operators: ");
    fgets(postfix, MAX, stdin);  // Get postfix expression input

    int result = evaluatePostfix(postfix);

    printf("Result of postfix evaluation: %d\n", result);

    return 0;
}
