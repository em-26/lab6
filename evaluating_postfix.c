#include <stdio.h>
#include <ctype.h>  // For isdigit()

#define MAX 100  // Maximum size of stack

int stack[MAX];
int top = -1;

// Function to push a value to the stack
void push(int x) {
    if (top < MAX - 1) {
        stack[++top] = x;
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop a value from the stack
int pop() {
    if (top != -1) {
        return stack[top--];
    }
    printf("Stack underflow\n");
    return -1;  // Error value
}

// Function to evaluate a postfix expression
int evaluatePostfix(char *postfix) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        if (isdigit(token)) {
            // If the token is an operand (digit), push it to the stack
            push(token - '0');  // Convert char to int
        } else {
            // If the token is an operator, pop two operands from the stack
            int operand2 = pop();
            int operand1 = pop();
            int result;

            switch (token) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator encountered: %c\n", token);
                    return -1;
            }

            // Push the result back onto the stack
            push(result);
        }
    }

    // The final result will be the only value left on the stack
    return pop();
}

int main() {
    char postfix[MAX];

    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}
