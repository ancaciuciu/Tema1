#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tasks.h"
#include "queue.h"
#include "stack.h"

int isEmptyStack(Stack * top) {
  return top == NULL;
}

void displayStack(Stack *top, FILE *fout) {
    fprintf(fout, "\n=== WINNER ===\n");
    if (isEmptyStack (top)) {
        return;
    }
    else {
        Stack *tmp = top;

        while ( tmp != NULL) {
            fprintf(fout, "%s --- %d\n", 
                tmp->st.name, tmp->st.global_score);
            tmp = tmp->next;
        }
    }
}

void deleteStack(Stack **top) {
    Stack *temp;

    while ((*top) != NULL) { 
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void pushCountry(Stack **top, Country c) {
    if (*top == NULL) {
        *top = malloc(sizeof(Stack));
        (*top)->st = c;
        (*top)->next = NULL;
        return;
    }
    Stack *newNode = (Stack*)malloc (sizeof(Stack));

    newNode->st = c;
    newNode->next = *top;
    *top = newNode;
}

Country popCountry(Stack **top) {
 // se returneaza informatia stocata in varf si se stege acest nod
    if (isEmptyStack(*top)) {
        printf("S-a terminat stiva.");
    }
    Stack *temp = (*top); //stochez adresa varful in temp
    Country aux = temp->st; //stochez valoarea din varf in aux
    *top = (*top)->next; //sterg elementul din varf
    return aux; //returneaza fiecare tara scoasa
}

Stack *task3(Stack *countryStack, FILE *fout) {
    Country tara1;
    Country tara2;

    Player jucator1;
    Player jucator2;

    // scorul local al primei tari care concureaza
    int scor_local1 = 0; 
    // scorul local pentru a doua tara care concureaza
    int scor_local2 = 0; 
    int i = 0, j = 0, k = 0;

    int winner = 0;
    //1 = jucator1 e castigator; 2 = jucator2 e castigator; 0 = remiza 
    Queue * matchesQ;
    matchesQ = createQueue();
    Stack *winnerStack = NULL;

    while (!isEmptyStack(countryStack)) {
        // se scot tarile din stiva de tari 2 cate 2
        tara1 = popCountry(&countryStack); 
        tara2 = popCountry(&countryStack);

        fprintf(fout, "\n%s %d ----- %s %d\n", 
        tara1.name, tara1.global_score, tara2.name, tara2.global_score);
        // ex : Georgia 0 ----- Polonia 0

        scor_local1 = 0; 
        scor_local2 = 0;

        // se vor pune jucatorii din tara1 si tara2 in coada, alternat
        // exemplu de alternare pentru 2 tari a cate 3 jucatori fiecare:
        // [jucator1(tara1) VS jucator1(tara2)] , 
        //[jucator1(tara1) VS jucator2(tara2)] , 
        // [jucator1(tara1) VS jucator3(tara2)]
        // dupa care urmeaza ca jucatorul 2 de la tara 1 
        //sa joace cu toti jucatorii de la tara 2
        // etc
        for (i = 0; i < tara1.nr_players; i++) {
            for (j = 0; j < tara2.nr_players; j++) {
                enQueue(matchesQ, tara1.players[i]);
                enQueue(matchesQ, tara2.players[j]);
            }
        }

        // simularea meciurilor in coada
        // se extrag din coada de meciuri cate 2 jucatori 
        //pana cand nu mai exista niciun element
        while (!isEmptyQueue(matchesQ)) {
            jucator1 = deQueue(matchesQ);
            jucator2 = deQueue(matchesQ);

            winner = playGame(jucator1, jucator2, tara1, tara2, fout);
            if (winner == 1) { // a castigat jucator1
                for (k = 0; k < tara1.nr_players; k++) {
                    //se cauta dupa nume jucatorul in tara din care provine
                    if ((strcmp(tara1.players[k].last_name, 
                               jucator1.last_name) == 0) &&
                        (strcmp(tara1.players[k].first_name, 
                                jucator1.first_name) == 0)) {
                        // se actualizeaza scorurile
                        tara1.players[k].score += 5;
                        scor_local1 += 3;
                    }
                }
            } 
            else if (winner == 2) { // a castigat jucator2
                for (k = 0; k < tara2.nr_players; k++) {
                    //se cauta dupa nume jucatorul in tara din care provine
                    if ((strcmp(tara2.players[k].last_name, 
                               jucator2.last_name) == 0) &&
                        (strcmp(tara2.players[k].first_name, 
                               jucator2.first_name) == 0)) {
                        // se actualizeaza scorurile
                        tara2.players[k].score += 5;
                        scor_local2 += 3;
                    }
                }
            }
            else if (winner == 0) { // este egalitate intre cei doi jucatori
                for (k = 0; k < tara1.nr_players; k++) {
                    //se cauta dupa nume jucatorul in tara din care provine
                    if ((strcmp(tara1.players[k].last_name, 
                               jucator1.last_name) == 0) &&
                        (strcmp(tara1.players[k].first_name, 
                               jucator1.first_name) == 0)) {
                        // se actualizeaza scorurile
                        tara1.players[k].score += 2;
                        scor_local1 += 1;
                    }

                    if ((strcmp(tara2.players[k].last_name, 
                               jucator2.last_name) == 0) &&
                        (strcmp(tara2.players[k].first_name, 
                               jucator2.first_name) == 0)) {
                        tara2.players[k].score += 2;
                        scor_local2 += 1;
                    }
                }
            }
        }
        tara1.global_score += scor_local1; //actualizare scorului global
        tara2.global_score += scor_local2;

        if (scor_local1 > scor_local2) {
            pushCountry(&winnerStack, tara1);
        }
        else if (scor_local1 < scor_local2) {
            pushCountry(&winnerStack, tara2);
        }
        else if (scor_local1 == scor_local2) {
            if (bestPersonalScore(tara1) >= 
                bestPersonalScore(tara2)) {
                pushCountry (&winnerStack, tara1);
            } 
            else {                
                pushCountry(&winnerStack, tara2);
            }
        }
    }
    return winnerStack;
}

void updatePersonalScore(Stack * winnerStack, Stack * winnerStack4) {
    int i = 0, j = 0;
    Stack *temp = winnerStack;
    Stack *temp4 = winnerStack4;
  
    while (temp4 != NULL) {
        while (temp != NULL) {
            if (strcmp(temp->st.name, winnerStack4->st.name) == 0) {
                for (j = 0; j < temp->st.nr_players; j++) {
                    winnerStack4->st.players[j].score = 
                    temp->st.players[j].score;
                }
            }
            temp = temp->next;
        }
        temp4 = temp4->next;
        temp = winnerStack;
    }
}