#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tasks.h"
#include "list.h"

Nod *Lista() {
    Nod *head = (Nod *)malloc(sizeof(Nod));
    head->prev = head;
    head->next = head;

    return head;
}

void addCountry(Nod *head, Country country) {
    //head->prev  ---->  newNode  ---->  head
    //head este santinela
    Nod *newNode = malloc(sizeof(Nod));
    newNode->country = country;
    // pt ca se adauga la final si pt ca lista e circulara,
    // deci ultimul va pointa la primul
    newNode->next = head; 
    newNode->prev = head->prev;

    head->prev->next = newNode;

    head->prev = newNode;   
}

void removeCountry(Nod *head, char *name) {
    while (head->next->country.name != NULL) {
        head = head->next;
        if (strcmp(head->country.name, name) == 0) {
            for (int i = 0; i < head->country.nr_players; i++) {
                free(head->country.players[i].last_name);
                free(head->country.players[i].first_name);
            }
            free(head->country.name);
            free(head->country.players);
            head->prev->next = head->next;
            head->next->prev = head->prev;
            break;
        }
    }
    free(head);
}

void removeNodes(Nod *head) {
    Nod *aux = head->next;
    char temp[15];
    strcpy(temp, aux->country.name);
    float min = (float)initialScore(aux);

    while(aux != head) {

        if ((float)(initialScore(aux)) < min) {

            min = (float)initialScore(aux);
            strcpy(temp, aux->country.name);
        }

        aux = aux->next;
    }

    removeCountry(aux, temp); //eliminare nod dupa nume    
}

// media aritmetică a scorurilor personale 
// ale jucătorilor din lotul țării = scor initial
float initialScore(Nod *nod) {
    int i = 0;
    float sum = 0.0;
    float medie = 0.0;
    
    for (i = 0; i < nod->country.nr_players; i++) {
        sum = sum + nod->country.players[i].score;
    }

    medie = sum/(nod->country.nr_players);

    return medie;
}