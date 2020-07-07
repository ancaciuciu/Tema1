typedef struct Stack {

    Country st;
    struct Stack *next;
} Stack;

int isEmptyStack(Stack * top);

void displayStack(Stack *top, FILE *fout);

void deleteStack(Stack **top);

void pushCountry(Stack **top, Country c);

Country popCountry(Stack **top);

Stack *task3(Stack *countryStack, FILE *fout);

void updatePersonalScore(Stack * winnerStack, Stack * winnerStack4);

