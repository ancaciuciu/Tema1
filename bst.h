typedef struct BST {

    Player player;
    struct BST *left, *right;
} BST;

BST * newNode(Player p);

BST * insert (BST * root, Player p);

void printBST(BST *root, FILE *fout);

int exists(BST *root, Player p);

int task5(BST *root, Player p1, Player p2);
