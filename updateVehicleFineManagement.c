// Updated version
/* COP 3502C Assignment 5
This program is written by: Kamilla Mamatova */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 25

typedef struct Node {
    char name[MAX_NAME_LENGTH + 1];
    int fine;
    int depth;
    struct Node *left;
    struct Node *right;
} Node;

// Function to update the depth
void updateDepth(Node *root, int depth) {
    if (root) {
        root->depth = depth;
        updateDepth(root->left, depth + 1);
        updateDepth(root->right, depth + 1);
    }
}

// Function to create a new node
Node *createNode(const char name[], int fine, int depth) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }

    strcpy(newNode->name, name);
    newNode->fine = fine;
    newNode->depth = depth;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}
