/* This code manages vehicle owners and their fines. 
The system keeps track of owner names, their fines, 
and their position in the tree. It provides functionalities 
for adding, searching, deducting, deleting, calculating, 
and balancing nodes (representing owners). */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 25

typedef struct Node{
    char name[MAX_NAME_LENGTH + 1];
    int fine;
    int depth;
    struct Node *left;
    struct Node *right;
} Node;

// Function to update the depth
void updateDepth(Node *root, int depth){
    if (root){
        root->depth = depth;
        updateDepth(root->left, depth + 1);
        updateDepth(root->right, depth + 1);
    }
}

// Function to create a new node
Node *createNode(const char name[], int fine, int depth){
    // Allocate memory for the new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    // If memory allocation fails
    if (newNode == NULL){
        return NULL;
    }

    // Initialize node values
    strcpy(newNode->name, name);
    newNode->fine = fine;
    newNode->depth = depth;
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

// Inserts a node in BST
Node *insert(Node *root, const char *name, int fine, int depth){
    // Create and return new node if BST is empty
    if (root == NULL){
        return createNode(name, fine, depth);
    }

    // Compare names for BST ordering
    int compare = strcmp(name, root->name);
    // Insert into left subtree if name is lexicographically smaller
    if (compare < 0){
        root->left = insert(root->left, name, fine, depth + 1);
    } 
    // Insert into right subtree if name is lexicographically greater
    else if (compare > 0){
        root->right = insert(root->right, name, fine, depth + 1);
    } 
    // If owner already exists, add fine to their current fine
    else{
        root->fine += fine;
    }

    return root;
}

// Searches for a node
Node *search(Node *root, const char *name, int depth){
    // Owner not found
    if (root == NULL){
        return NULL;
    }

    int compare = strcmp(name, root->name);
    if (compare < 0){
        return search(root->left, name, depth + 1);
    } 
    else if (compare > 0){
        return search(root->right, name, depth + 1);
    } 
    // Print owner's name, fine, and depth if found
    else{
        printf("%s %d %d\n", root->name, root->fine, depth);
        return root;
    }
}

// Finds minimum node
Node *findMin(Node *root){
    while (root->left != NULL){
        root = root->left;
    }
    return root;
}

// Deletes a node
Node *deleteNode(Node *root, const char *name){
    // Owner not found
    if (root == NULL){
        return NULL;
    }

    int compare = strcmp(name, root->name);
    if (compare < 0){
        root->left = deleteNode(root->left, name);
    } 
    else if (compare > 0){
        root->right = deleteNode(root->right, name);
    } 
    // Node has no left child
    else{
        if (root->left == NULL){
            Node *temp = root->right;
            free(root);
            return temp;
        } 
        // Node has no right child
        else if (root->right == NULL){
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node has two children, find the in-order successor (smallest in right subtree)
        Node *temp = findMin(root->right);
        strcpy(root->name, temp->name);
        root->fine = temp->fine;
        root->right = deleteNode(root->right, temp->name);
    }
    return root;
}

// Deduct fine and remove owner if fine is 0
Node *deduct(Node *root, const char *name, int fine){
    Node *owner = search(root, name, 0);
    if (owner){
        owner->fine -= fine;
        if (owner->fine <= 0){
            printf("%s removed\n", owner->name);
            // Remove owner if fine reaches zero
            root = deleteNode(root, name);
        }
        // Print if owner does not exist
        else{
            printf("%s not found\n", name);
        }
        return root;
    }
}

// Calculate total fine
void calculateTotal(Node *root, int *total, int *count){
    // Base case
    if (root == NULL) return;

    // Add current node's fine to total
    *total += root->fine;
    (*count)++;
    
    calculateTotal(root->left, total, count);
    calculateTotal(root->right, total, count);
}

// Calculate average fine
void calculateAverage(Node *root){
    int total = 0, count = 0;
    calculateTotal(root, &total, &count);

    if (count > 0){
        printf("%.2f\n", (float)total / count);
    }
}

// Main function
int main(){
    Node *root = NULL;
    char command[20], name[MAX_NAME_LENGTH + 1];
    int fine, numCommands;

    scanf("%d", &numCommands);

    for (int i = 0; i < numCommands; i++) {
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s %d", name, &fine);
            root = insert(root, name, fine, 0);
        }
    }

    // Exit program
    return 0;
}
