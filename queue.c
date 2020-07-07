#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tasks.h"
#include "queue.h"

int isEmptyQueue(Queue *q) {
    if (q->front == NULL) {
        return 1;
    }
    return 0;
}

//functie pentru creare coada

Queue * createQueue() {
    Queue *q;

    q = malloc(sizeof(Queue));
    
    if (q == NULL) {
        return NULL;
    }

    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue * q, Player p) { 
//functie care adauga elemente de tip jucator in coada
    queueNode * newNode = malloc(sizeof(queueNode));
    newNode->q = p;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Player deQueue(Queue *queue) { 
//functie care extrage elemente de tip jucator din coada
    queueNode *aux;
    Player p;

    aux = queue->front;
    queue->front = queue->front->next;
    p = aux->q;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(aux);
    aux = NULL;
    return p;
}
