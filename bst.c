#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tasks.h"
#include "bst.h"

BST * newNode(Player p) {
    BST *root = malloc (sizeof(BST));
    root->player = p;
    root->left = root->right = NULL;
    return root;
}

BST * insert(BST * root, Player p) {
    // daca (sub)arborele e gol – se creaza si adauga un nod
    if (root == NULL) return newNode(p);

    //altfel se coboara la stanga sau dreapta in arbore
    if (p.score < root->player.score) {
        root->left = insert(root->left, p);
    } else {
        if (p.score > root->player.score){
            root->right = insert(root->right, p);
        } else {
            if (strcmp(p.last_name, root->player.last_name) < 0) {
                root->player = p;
            }
        }
    }   
    //pointerul node se intoarce nemodificat pe acest return
    return root;
}

void printBST(BST *root, FILE *fout) {
    if (root == NULL) {
        return;
    }

    printBST(root->right, fout);
    fprintf(fout, "%s %s %d\n", 
        root->player.last_name, root->player.first_name, root->player.score);
    printBST(root->left, fout);

}

int exists(BST *root, Player p) {
    if (root == NULL) {
        return 0;
    }
    if (root->player.score == p.score) {
        if (strcmp(root->player.last_name, p.last_name) == 0) {
            return 1;
        } else {
            return 0;
        }
    } else if (root->player.score > p.score) {
        return exists(root->left, p);
    } else {
        return exists(root->right, p); 
    }
}

int task5(BST *root, Player p1, Player p2) {
    static int result;

    if (root == NULL) {
        return result;
    }

    task5(root->left, p1, p2);
    if (root->player.score > p1.score && root->player.score < p2.score) {
        result++;
    }
    task5(root->right, p1, p2);
    return result;
}
