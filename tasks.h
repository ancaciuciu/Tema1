typedef struct Player {

    char *last_name;
    char *first_name;
    int score;
} Player;

typedef struct Country {

    char *name;
    int nr_players;
    int global_score;
    Player *players;
} Country;

int log2n(int n);

int closestPow2(int n);

int bestPersonalScore(Country c);

int playGame(Player p1, Player p2, Country t1, Country t2, FILE *fout);
