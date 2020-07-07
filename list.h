typedef struct Nod {

    Country country;
    struct Nod *next;
    struct Nod *prev;
} Nod;

Nod *Lista();

void addCountry(Nod *head, Country country);

void removeCountry(Nod *head, char *name);

void removeNodes(Nod *head);

float initialScore(Nod *nod);