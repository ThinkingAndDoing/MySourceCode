#include <stdio.h>
#include <string.h>

#define MAX 1000
#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct Queues{
    int data[MAX];
    int front;
    int rear;
}Queue;

Queue queue;

void CreatQueue(void){
    queue.front = queue.rear = 0;
}

BOOL IsQueueEmpty(void){
    if (queue.front == queue.rear)
        return TRUE;
    else
        return FALSE;
}

void PushQueue(int value){
    if ((queue.rear + 1) % MAX != queue.front){
        queue.data[queue.rear] = value;
        queue.rear = (queue.rear + 1) % MAX;
    }
}

int PopQueue(void){
    if (queue.front != queue.rear){
        int value = queue.data[queue.front];
        queue.front = (queue.front + 1) % MAX;
        return value;
    }
    return 0;
}

int main()
{
    int i;
    CreatQueue();
    for (i = 1; i <= 5; i++){
        PushQueue(i);
    }
    for (i = 1; i <= 5; i++){
        printf("%d", PopQueue());
    }

    return 0;
}