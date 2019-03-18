#include "stdio.h"
#include "stdlib.h"

typedef struct queue {
    int size;
    int *storage;
    int tail;
    int head;
} Queue;

Queue * create(int max_size) {
    Queue * queue = (Queue *) malloc(sizeof(Queue));
    queue->storage = (int *) malloc(sizeof(int) * max_size);

    queue->tail = -1;
    queue->head = -1;
    queue->size = max_size;

    return queue;
}

int is_full(Queue *q) {
    return (q->tail + 1 == q->head) || (q->head == 0 && q->tail == q->size - 1);
}

int is_empty(Queue *q) {
    return q->head == -1;
}

void enqueue(Queue *q, int value) {
    if (is_full(q)) {
        printf("Queue is full. Value %d is rejected.\n", value);
        return;
    }
    
    if (q->head == -1) {
        q->head = 0;
    }

    printf("Value %d is queued.\n", value);
    q->storage[++q->tail] = value;
}

int dequeue(Queue *q) {

    if (is_empty) {

    }

    int value = q->storage[q->head];

    printf("Value %d dequeued.\n", value);
    return value;
}

int main() {

    Queue * q = create(3);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    return 0;
}