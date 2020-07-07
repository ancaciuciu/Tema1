#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tasks.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "bst.h"

#define maxlen 15
#define numar_cerinte 5

int main(int argc, char * argv[]) {

	int i = 0, j = 0, nr = 0, nr_tari = 0, cerinta[numar_cerinte];
	FILE *cerin, *fin;
	FILE *fout;
	Nod *head = NULL;

	cerin = fopen(argv[1], "rt");
	if (cerin == NULL) {
		puts("Fisierul cerin nu poate fi deschis.\n");
		exit(1);
	}
	
	for (i = 0; i < 5; i++) {
		fscanf(cerin, "%d", &nr);
		cerinta[i] = nr;
	}

	if (cerinta[0] == 1) { //rezolvare cerinta 1
		fin = fopen(argv[2], "rt");
		if (fin == NULL) {
			puts("Fisierul fin nu poate fi deschis.\n");
			exit(1);
		}

		head = Lista();
		fscanf(fin, "%d", &nr_tari); // citire numar tari 
		char buff[maxlen];

		for (i = 0; i < nr_tari; i++) {
			Country c;
			fscanf(fin, "%d", &c.nr_players); // citire numar jucatori
			c.players = malloc(c.nr_players * sizeof(Player));
			
			fscanf(fin, "%s", buff); // citire nume tara
			c.name = malloc((strlen(buff) + 1) * sizeof(char));
			strcpy(c.name, buff);
			
			c.global_score = 0; // toate tarile pornesc de la scor global 

			for (j = 0; j < c.nr_players; j++) {

				fscanf(fin, "%s", buff); // citire nume jucator
				c.players[j].last_name = malloc((strlen(buff) + 1) * 
				sizeof(char));
				strcpy(c.players[j].last_name, buff);

				fscanf(fin, "%s", buff); // citire prenume jucator
				c.players[j].first_name = malloc((strlen(buff) + 1) * 
				sizeof(char));
				strcpy(c.players[j].first_name, buff);
				// citire scor jucator
				fscanf(fin, "%d", &c.players[j].score); 
			}
			addCountry(head, c);
		}
	}

	int nr_deletes = 0; 
	
	if (cerinta[1] == 1) {  // rezolvare cerinta 2.
		nr_deletes = nr_tari - closestPow2(nr_tari);
		for (i = 0; i < nr_deletes; i++) {
			removeNodes(head); // eliminarea tarilor
		}
	}
	
	fout = fopen(argv[3], "wt");
	if (fout == NULL) {
		puts("Fisierul nu poate fi deschis.");
		exit(1);
	}

	Nod *auxi = head;

	while (auxi->next != head) {
		auxi = auxi->next;
		fprintf(fout, "%s\n", auxi->country.name);
	}
	
	Stack *stackTop = NULL;
	Stack *winnerStack = NULL;
	Stack *winnerStack4 = NULL;

	if (cerinta[2] == 1) {  // rezolvare cerinta 3.
		auxi = head; 
		while (auxi->next != head) {
			auxi = auxi->next;
			// adaugarea in stiva stackTop a tarilor ramase
			pushCountry(&stackTop, auxi->country); 
		}

		Country country_aux;
		int numRounds = log2n(closestPow2(nr_tari));

		for (i = 0; i < numRounds; i++) {
			fprintf (fout, "\n====== ETAPA %d ======\n", i + 1);
			winnerStack = task3(stackTop, fout);
			deleteStack(&stackTop);
			stackTop = NULL;

			if (i == (numRounds - 3)) {
				// se face o copie pt winnerStack
				winnerStack4 = winnerStack;
			}
			Stack *winner_copy = winnerStack;
			// se actualizeaza scorurile jucatorilor
			updatePersonalScore(winner_copy, winnerStack4);
			displayStack(winnerStack, fout);

			while (!isEmptyStack(winnerStack)) {
				country_aux = popCountry(&winnerStack);
				pushCountry(&stackTop, country_aux);
			}
			deleteStack(&winnerStack);
			winnerStack = NULL;
		}
	}

	Player root_player;
	Stack *copy = winnerStack4;
	BST *root = NULL;

	if (cerinta[3] == 1) {  // rezolvare cerinta 4.
		//se va folosi stackul winnerStack4 folosit la cerinta anterioara
		while (copy != NULL) {
			for (i = 0; i < copy->st.nr_players; i++) {
				root = insert(root, copy->st.players[i]);
			}
			copy = copy->next;
		}
		fprintf(fout, "\n====== CLASAMENT JUCATORI ======\n");
		printBST(root, fout);
	}

	Player p1, p2;
	if(cerinta[4] == 1) {
		

		p1.first_name = malloc(maxlen * sizeof(char));
		p1.last_name = malloc(maxlen * sizeof(char));
		p2.first_name = malloc(maxlen * sizeof(char));
		p2.last_name = malloc(maxlen * sizeof(char));
		fscanf(cerin, "%s %s %d", p1.last_name, p1.first_name, &p1.score);
		fscanf(cerin, "%s %s %d", p2.last_name, p2.first_name, &p2.score);
		int rc = 0;
		
		if (p1.score > p2.score) {
			Player aux = p1;
			p1 = p2;
			p2 = aux;
		}

		if (exists(root, p1) == 0) {
	        rc = -1;
	    } else if (exists(root, p2) == 0) {
	        rc = -2;
	    } else {
	    	rc = task5(root, p1, p2);
	    }
	

		if (rc < 0) {
			if (rc == -1) {
				fprintf(fout, "\n%s %s nu poate fi identificat!\n", 
				p1.last_name, p1.first_name);
			} else {
				fprintf(fout, "\n%s %s nu poate fi identificat!\n",
				p2.last_name, p2.first_name);
			}
		} else {
			fprintf(fout, "\n%d\n", rc);
		}
	}
	
	fclose(cerin);
	fclose(fin);
	fclose(fout);

	// eliberarea spatiului de memorie alocat

	if (cerinta[0] == 1) {
		Nod *freeAux1 = head; // este folosit pentru oprire
		head = head->next;
		while (head != freeAux1) {
			free(head->country.name);
			for (int i = 0; i < head->country.nr_players; i++) {
				free(head->country.players[i].first_name);
				free(head->country.players[i].first_name);
			}
			free(head->country.players);
			Nod *freeAux2 = head;
			free(head);
			head = freeAux2->next;
		}
		free(freeAux1);
	}

	if (cerinta[2] == 1) {
		deleteStack(&winnerStack4);
		deleteStack(&stackTop);
	}
	if (cerinta[3] == 1) {
		deleteStack(&copy);
	}
	if (cerinta[4] == 1) {
		free(p1.first_name);
		free(p1.last_name);
		free(p2.first_name);
		free(p2.last_name);	
	}

	return 0;
}