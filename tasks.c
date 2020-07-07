#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tasks.h"
//am adaugat un comentariu
int log2n(int n) {
    int res = -1;
    while (n) {
        n = n / 2;
        res ++;
    }
    return res;
}

int closestPow2(int n) {
    int res = 1;
    while(res < n) {
        res = res * 2;
    }
    return res/2;
}

//functie pentru aflarea celui mai mare scor personal dintr-o tara
int bestPersonalScore(Country c) {
    int i = 0;
    int best = c.players[0].score;
    // algoritm de aflare a maximului
    for(i = 1; i < c.nr_players; i++) {
        if (c.players[i].score > best) {
            best = c.players[i].score;
        }
    }

    return best;
}

//functie care compara scorurile personale a doi jucatori
int playGame(Player p1, Player p2, Country t1, Country t2, FILE *fout) {
    for (int i = 0; i < t1.nr_players; i++) {
        // se va cauta dupa nume jucatorul in tara din care provine
        if (strcmp(p1.last_name, t1.players[i].last_name) == 0 &&
            strcmp(p1.first_name, t1.players[i].first_name) == 0) {
            p1.score = t1.players[i].score;
            break;
        }
    }

    for (int i = 0; i < t1.nr_players; i++) {
        // se va cauta dupa nume jucatorul in tara din care provine
        if (strcmp(p2.last_name, t2.players[i].last_name) == 0 &&
            strcmp(p2.first_name, t2.players[i].first_name) == 0) {
            p2.score = t2.players[i].score;
            break;
        }
    }

    fprintf(fout, "%s %s %d vs %s %s %d\n", 
    p1.last_name, p1.first_name, p1.score,
    p2.last_name, p2.first_name, p2.score);
    //ex: Metreveli Aleksandre 28 vs Kubot Lukasz 24

    if (p1.score > p2.score) {
        return 1;
    } else 
    if (p1.score < p2.score) {
        return 2;
    } else
    if (p1.score == p2.score) {
        return 0;
    }
}
