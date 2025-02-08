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

// Inserts a node in BST
Node *insert(Node *root, const char *name, int fine, int depth) {
    if (root == NULL) {
        return createNode(name, fine, depth);
    }

    int compare = strcmp(name, root->name);
    if (compare < 0) {
        root->left = insert(root->left, name, fine, depth + 1);
    } else if (compare > 0) {
        root->right = insert(root->right, name, fine, depth + 1);
    } else {
        root->fine += fine;
    }

    return root;
}

// Searches for a node
Node *search(Node *root, const char *name, int depth) {
    if (root == NULL) {
        return NULL;
    }

    int compare = strcmp(name, root->name);
    if (compare < 0) {
        return search(root->left, name, depth + 1);
    } else if (compare > 0) {
        return search(root->right, name, depth + 1);
    } else {
        printf("%s %d %d\n", root->name, root->fine, depth);
        return root;
    }
}

// Finds minimum node
Node *findMin(Node *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Deletes a node
Node *deleteNode(Node *root, const char *name) {
    if (root == NULL) {
        return NULL;
    }

    int compare = strcmp(name, root->name);
    if (compare < 0) {
        root->left = deleteNode(root->left, name);
    } else if (compare > 0) {
        root->right = deleteNode(root->right, name);
    } else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        Node *temp = findMin(root->right);
        strcpy(root->name, temp->name);
        root->fine = temp->fine;
        root->right = deleteNode(root->right, temp->name);
    }
    return root;
}

// Deduct fine and remove owner if fine is 0
Node *deduct(Node *root, const char *name, int fine) {
    Node *owner = search(root, name, 0);
    if (owner) {
        owner->fine -= fine;
        if (owner->fine <= 0) {
            printf("%s removed\n", owner->name);
            root = deleteNode(root, name);
        }
        else{
            printf("%s not found\n", name);
        }
        return root;
    }
}

// Calculate total fine
void calculateTotal(Node *root, int *total, int *count) {
    if (root == NULL) return;
    
    *total += root->fine;
    (*count)++;
    
    calculateTotal(root->left, total, count);
    calculateTotal(root->right, total, count);
}

// Calculate average fine
void calculateAverage(Node *root) {
    int total = 0, count = 0;
    calculateTotal(root, &total, &count);

    if (count > 0) {
        printf("%.2f\n", (float)total / count);
    }
}

// Main function
int main() {
    Node *root = NULL;
    char command[20], name[MAX_NAME_LENGTH + 1];
    int fine, numCommands;

    scanf("%d", &numCommands);

    for (int i = 0; i < numCommands; i++) {
        scanf("%s", command);
