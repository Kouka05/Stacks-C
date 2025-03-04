#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int items[SIZE];
    int top;
} Stack;

Stack* initialize() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s != NULL) {
        s->top = -1;
    }
    return s;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == SIZE - 1;
}

void push(Stack* s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = x;
}

int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Empty\n");
        return -1;
    }
    return s->items[s->top];
}

int main() {
    Stack* s = initialize();

    push(s, 10);
    push(s, 20);
    push(s, 30);

    printf("Top element: %d\n", peek(s));

    printf("Popped: %d\n", pop(s));
    printf("Popped: %d\n", pop(s));

    printf("\nisEmpty:%d\n", isEmpty(s));

    free(s);
    return 0;
}
