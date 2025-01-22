/* COP 3502C Assignment 5
This program is written by: Kamilla Mamatova */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 25

typedef struct Node{
    // Array for the people
    char name[MAX_NAME_LENGTH + 1]; // + NULL terminator
    int fine;
    int depth;
    struct Node * left;
    struct Node * right;
} Node;

// Function to update the depth
void updateDepth(Node * root, int depth){
    if root{
        root->depth = depth;
        updateDepth(root->left, depth + 1);
        updateDepth(root->right, depth + 1);
    }
}

// Function to create a new node
Node * createNode(const char name[], int fine){
    Node * newNode = (Node *)malloc(sizeof(Node));
    // Base case
    if (newNode == NULL){
        return NULL;
    }

    strcpy(newNode->name, name);
    newNode->fine = fine;
    newNode->depth = depth;
    newNode->left = NULL;
    newNode->right = NULL;

    printf("%s %d %d", name, value, depth);

    return newNode;
}

// Adds a vehicle owner with a specified name to the tree.
Node * insert(Node * root, const char * name, int fine, int * depth){
    // Base case, if tree is empty
    if (root == NULL) {
        // Create a new node to fix the problem
        return createNode(name, fine, *depth);
    }

    // Guides where to insert a new node in the BST based on alphabetical order.
    int compare = strcmp(name, root->name);
    if(compare < 0){
        (*depth)++;
        /* In a BST, names that are lexicographically smaller than should go
        to the left of the root, so it recursively calls itself. */
        root->left = insert(root->left, name, fine);
    }
    else if(compare > 0){
        (*depth)++;
        root->right = insert(root->right, name, fine);
    }
    /* If the owner already exists in the system, the owner's fine will increase
    by the given amount. */
    else{
        root->fine += fine; // ?
    }

    return root; 
}

// Searches for a node and prints the fine and depth
void search(Node * root, const char * name, int depth){
    // Base case, if owner not found
    if (root == NULL){
        return;
    }

    int compare = strcmp(name, root->name);
    if(compare < 0){
        search(root->left, name, depth + 1);
    }
    else if(compare > 0){
        search(root->right, name, depth + 1);
    }
    else{
        printf("%s %d %d\n", root->name, root->fine, depth);
    }
}

/* Helper function for the delete function, 
finds the minimum node in the right subtree. */
Node * findMin(Node * root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

// Delete function to delete a node with a specific name
Node * deleteNode(Node * root, const char * name){
    // Base case
    if(root == NULL){
        return root;
    }
    
    // Need to compare root's name to name to decide which direction to traverse
    int compare = strcmp(name, root->name);
    if(compare < 0){
        // Go left if the name is smaller
        root->left = deleteNode(root->left, name);
    }
    else if(compare > 0){
        // Go right if the name is bigger
        root->right = deleteNode(root->right, name);
    }
    // Handles deletion after the correct node has been found
    else{
        // The node to delete
        // The node only has one right child or no child at all
        if(root->left == NULL){
            // Temporarily store its right child in tmp
            Node * tmp = root->right;
            // Free the node
            free(root);
            return tmp;
        }
        // The node only has one left child or no child at all
        else if(root->right == NULL){
            Node * tmp = root->left;
            free(root);
            // Lets the tmp 
            return tmp;
        }
        else{
            // The node has two children
            // Use the findMin function to find the minimum node in the right subtree
            Node * tmp = findMin(root->right);

            // Copy from in order to the current node
            strcpy(root->name, tmp->name);
            root->fine = tmp->fine;

            // Make one recursive call to delete the in-order successor
            root->right = deleteNode(root->right, tmp->name);
        }
    }
    return root;
}

/* A function that ensures that if a deduction exceeds the current fine,
the fine is set to 0 and the owner is removed from the system if they no
longer owe any fines. */
Node * deduct(Node * root, const char * name, int fine){
    // Base case
    if(root == NULL){
        return root;
    }
    Node * owner = root;

    // Find the owner
    while(owner != NULL && strcmp(owner->name, name) != 0){
        if(strcmp(name, owner->name) < 0){
            owner = owner->left;
        }
        else{
            owner = owner->right;
        }
    }

    if (owner != NULL){
        // Specified deduction
        owner->fine -= fine;
        /* If the fine after the deduction is less than or equal to 0, 
        delete the owner's name from the list. */
        if (owner->fine <= 0){
            printf("%s removed\n", owner->name);
            root = deleteNode(root, name);
        }
    }
    else{
        printf("%s not found\n", owner->name);
    }

    return root;
}

/* Parameters, total and count, are pointers because they are being used to
accumulate values across recursive calls in a BST traversal */
void calculateTotal(Node * root, int * total, int * count){
    // Base case
    if(root == NULL){
        return;
    }
    *total += root->fine;
    (*count)++;
    // Traverse and call recursion
    calculateTotal(root->left, total, count);
    calculateTotal(root->right, total, count);
}

// Calculate the average fine amount per owner in the system
void calculateAverage(Node * root){
    int total = 0;
    int count = 0;
    calculateTotal(root, &total, &count);

    if(count == 0){
        return;
    }
    else{
        float average = (float)total / count;
        printf("%.2f\n", average);
    }
}

// Calculate the height of a subtree
int height(Node * root){
    // Base case
    if(root == NULL){
        return 0;
    }

    // Calculate left subtree's height using recursion
    int leftHeight = height(root->left);

    // Calculate right subtree's height using recursion
    int rightHeight = height(root->right);

    // Compare the left and right height
    // Return the maximum height
    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }
    else{
        return rightHeight + 1;
    } 
}

// Determine the balance of the tree in terms of height
void balance(Node * root){
    // Base case
    if(root == NULL){
        return;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    // Balance factor
    int BF = leftHeight - rightHeight;

    // If balanced
    // |BF| < 1
    if(BF >= -1 && BF <= 1){
        printf("left height = %d right height = %d balanced\n", leftHeight, rightHeight);
    }
    else{
        printf("left height = %d right height = %d not balanced\n", leftHeight, rightHeight);      
    }
}

/* Calculate the total amount of fines for all vehicle owners whose names come
alphabetically before the specified name. */
void calculateBelowSum(Node * root, const char * name, int * sum){
    // Base case
    if(root == NULL){
        return;
    }

    // Compare names and find the one alphabetically before the specified name
    if(strcmp(root->name, name) <= 0){
        // Add fine to sum
        *sum += root->fine;
        // Recursive call
        calculateBelowSum(root->left, name, sum);
        calculateBelowSum(root->right, name, sum);
    }
    else{
        calculateBelowSum(root->left, name, sum);
    }
}

void calcBelow(Node * root, const char * name){
    int sum = 0;
    calculateBelowSum(root, name, &sum);
    printf("%d\n", sum);
}

// Main function
int main(){
    Node * root = NULL;
    char command[20];
    char name[MAX_NAME_LENGTH + 1];
    int fine;
    int numCommands;

    // Read in the number of commands
    scanf("%d", &numCommands);
    printf("\n");

    for(int i = 0; i < numCommands; i++){
        scanf("%s", command);

        if(strcmp(command, "add") == 0){
            scanf("%s %d", name, &fine);
            root = insert(root, name, fine);
            printf("%s %d %d\n", name, fine, depth);
        }
        else if(strcmp(command, "deduct") == 0){
            scanf("%s %d", name, &fine);
            printf("%s %s %d\n", command, name, fine);
            root = deduct(root, name, fine);
        }
        else if(strcmp(command, "search") == 0){
            scanf("%s", name);
            printf("%s %d %d\n", name, fine, depth);
            search(root, name, 0);
        }
        else if(strcmp(command, "average") == 0){
            //printf("%s\n", command);
            calculateAverage(root);
        }
        else if(strcmp(command, "balance") == 0){
            //printf("%s\n", command);
            printf("")
            balance(root);
        }
        else if(strcmp(command, "calcBelow") == 0){
            scanf("%s", name);
            calcBelow(root, name);
            printf("%d\n", sum);
        }
    }

    return 0;
}
