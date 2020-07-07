typedef struct queueNode {

    Player q; //cu ajutorul acesteia se vor pune cele 2 tari care vor concura
    struct queueNode *next; //legatura catre nodul urmator
} queueNode;


typedef struct Queue {

    queueNode *front, *rear;
} Queue;

int isEmptyQueue(Queue *q);

Queue * createQueue();

void enQueue(Queue * q, Player p);

Player deQueue(Queue *queue);
