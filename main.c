#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

typedef struct {
    int items[SIZE];
    int top;
} Stack;

Stack* initialize();
int isEmpty(Stack* s);
int isFull(Stack* s);
void push(Stack* s, int x);
int pop(Stack* s);
int peek(Stack* s);
void reverseString(char* str);
int isSorted(Stack* s);
int isPrime(int num);
void deletePrimes(Stack* s);
Stack* mergeSortedStacks(Stack* s1, Stack* s2);
int isBalanced(char* expression);
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                char str[SIZE];
                printf("Enter a string to reverse: ");
                fgets(str, SIZE, stdin);
                str[strcspn(str, "\n")] = '\0';
                reverseString(str);
                printf("Reversed string: %s\n", str);
                break;
            }
            case 2: {
                Stack* s = initialize();
                int n, val;
                printf("Enter number of elements: ");
                scanf("%d", &n);
                printf("Enter stack elements (min on top): ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &val);
                    push(s, val);
                }
                if(isSorted(s))
                printf("The stack is sorted.\n");
                else printf("The stack not sorted.\n");
                free(s);
                break;
            }
            case 3: {
                Stack* s = initialize();
                int n, val;
                printf("Enter number of elements: ");
                scanf("%d", &n);
                printf("Enter stack elements: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &val);
                    push(s, val);
                }
                deletePrimes(s);
                printf("Stack after removing primes: ");
                while (!isEmpty(s)) {
                    printf("%d ", pop(s));
                }
                printf("\n");
                free(s);
                break;
            }
            case 4: {
                Stack* s1 = initialize();
                Stack* s2 = initialize();
                int n1, n2, val;
                printf("Enter number of elements for first stack: ");
                scanf("%d", &n1);
                printf("Enter elements for first stack: ");
                for (int i = 0; i < n1; i++) {
                    scanf("%d", &val);
                    push(s1, val);
                }
                printf("Enter number of elements for second stack: ");
                scanf("%d", &n2);
                printf("Enter elements for second stack: ");
                for (int i = 0; i < n2; i++) {
                    scanf("%d", &val);
                    push(s2, val);
                }
                Stack* temp = mergeSortedStacks(s1, s2);
                printf("Merged sorted stack: ");
                while (!isEmpty(temp)) {
                    printf("%d ", pop(temp));
                }
                printf("\n");
                free(s1);
                free(s2);
                free(temp);
                break;
            }
            case 5: {
                char expression[SIZE];
                printf("Enter an expression: ");
                fgets(expression, SIZE, stdin);
                expression[strcspn(expression, "\n")] = '\0';
                if(isBalanced(expression))
                    printf("Balanced Expression.\n");
                else printf("Unbalanced Expression\n");
                break;
            }
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}

Stack* initialize() {
    Stack* s = malloc(sizeof(Stack));
    s->top = -1;
    return s;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == SIZE - 1;
}

void push(Stack* s, int x) {
    if (!isFull(s)) {
        s->items[++(s->top)] = x;
    }
}

int pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return -1;
}

int peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return -1;
}

void reverseString(char* str) {
    Stack* s = initialize();
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        push(s, str[i]);
    }
    for (int i = 0; i < len; i++) {
        str[i] = pop(s);
    }
    free(s);
}

int isSorted(Stack* s) {
    if (isEmpty(s) || s->top == 0) return 1;

    Stack* temp = initialize();
    int sorted = 1;
    int prev = pop(s);

    push(temp, prev);

    while (!isEmpty(s)) {
        int x = pop(s);

        if (x > prev) {
            sorted = 0;
        }

        push(temp, x);
        prev = x;
    }

    while (!isEmpty(temp)) {
        push(s, pop(temp));
    }

    free(temp);
    return sorted;
}

int isPrime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

void deletePrimes(Stack* s) {
    Stack* temp = initialize();
    while (!isEmpty(s)) {
        int val = pop(s);
        if (!isPrime(val)) {
            push(temp, val);
        }
    }
    while (!isEmpty(temp)) {
        push(s, pop(temp));
    }
    free(temp);
}

Stack* mergeSortedStacks(Stack* s1, Stack* s2) {
    Stack* merged = initialize();
    Stack* temp = initialize();

    while (!isEmpty(s1) || !isEmpty(s2)) {
        if (isEmpty(s1)) push(temp, pop(s2));
        else if (isEmpty(s2)) push(temp, pop(s1));
        else if (peek(s1) < peek(s2)) push(temp, pop(s1));
        else push(temp, pop(s2));
    }

    while (!isEmpty(temp)) {
        push(merged, pop(temp));
    }

    free(temp);
    return merged;
}

int isBalanced(char* expression) {
    Stack* s = initialize();
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(') {
            push(s, '(');
        } else if (expression[i] == ')') {
            if (isEmpty(s)) {
                free(s);
                return 0;
            }
            pop(s);
        }
    }
    int balanced = isEmpty(s);
    free(s);
    return balanced;
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Reverse a string\n");
    printf("2. Check if stack is sorted\n");
    printf("3. Delete prime numbers from stack\n");
    printf("4. Merge two sorted stacks\n");
    printf("5. Check for balanced parentheses\n");
    printf("6. Exit\n");
}
