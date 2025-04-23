/* COP 3502C Assignment 5
This program is written by: Aaron Burgess */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NLEN 30
#define CLEN 100

typedef struct tree_node {
    char name[NLEN];
    int tickets;
    int depth;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

//function prototypes
tree_node* create_node(char name[], int numTix, tree_node *root); //new node / update existing node
tree_node* insert(tree_node *root, tree_node *newNode); //add to tree
tree_node* findNode(tree_node *root, char name[]); //find node with the customer's name
tree_node* parent(tree_node *root, tree_node *node); //finds parent of node
tree_node* maxVal(tree_node *root); //finds maxVal of the subtree with root "root"
int isLeaf(tree_node *node); //finds if this node is a leaf node
int hasOnlyLeftChild(tree_node *node); //determines if this node has only left children
int hasOnlyRightChild(tree_node *node); //determines if this node has only right children
void depthChange(tree_node *root); //change the depth of everything in the tree (including the root) to itself -1
tree_node* delete(tree_node *root, char name[], int numTix); //deletes a specific number of tickets from customer with name "name"
int count(tree_node *root); //count up the total number of nodes in the tree
double add(tree_node *root); //adds up the total number of tickets held by all the people in the tree
int height(tree_node *root); //calculates the height of each subtree
int countBefore(tree_node *root, char name[]); //count the number of tickets of everyone in the tree before name alphabetically
void bye_tree(tree_node *root); //post order traversal to free the tree

int main(void) {
    int C;
    tree_node *root = NULL;
    scanf("%d", &C);

    for (int i = 0; i < C; i++) { //for each command
        char command[CLEN];
        scanf("%s", command);
        if (strcmp(command, "buy") == 0) { //either create a customer or add numTix to tickets of existing customer
            char name[NLEN];
            int numTix;
            scanf("%s %d", name, &numTix); //name and number of tickets they want to buy
            tree_node *temp = create_node(name, numTix, root);
            if (findNode(root, temp->name) == NULL) {
                root = insert(root, temp); //actually add them to the tree
            }
            printf("%s %d %d\n", temp->name, temp->tickets, temp->depth);
        }
        else if (strcmp(command, "use") == 0) { //deletes a specific number of tickets from a customer, fully deletes if tickets is <=0
            char name[NLEN];
            int numTix;
            scanf("%s %d", name, &numTix); //name and number of tickets to use
            if (findNode(root, name) == NULL) {
                printf("%s not found\n", name);
                continue; //next command
            }
            root = delete(root, name, numTix); //delete from tree
            tree_node *temp = findNode(root, name);
            if (temp != NULL) {
                printf("%s %d %d\n", temp->name, temp->tickets, temp->depth);
            } else {
                printf("%s deleted\n", name);
            }
        }
        else if (strcmp(command, "find") == 0) { //find the node indicated by the name
            char name[NLEN];
            scanf("%s", name);
            tree_node *temp = findNode(root, name);
            if (temp == NULL) {
                printf("%s not found\n", name);
            }
            else {
                printf("%s %d %d\n", temp->name, temp->tickets, temp->depth);
            }
        }
        else if (strcmp(command, "mean_tickets") == 0) { //find the average number of tickets of everyone in the tree
            double average = add(root)/count(root);
            printf("%.2f\n", average);
        }
        else if (strcmp(command, "height_balance") == 0) { //find the height of the left and right subtree and compare
            if (root!=NULL) {
                int left = height(root->left);
                int right = height(root->right);
                if (left == right) {
                    printf("left height = %d right height = %d balanced\n", left, right);
                }
                else {
                    printf("left height = %d right height = %d not balanced\n", left, right);
                }
            }
        }
        else if (strcmp(command, "count_before") == 0) { //go through the whole tree and add number of tickets of people before and at the name specified
            char name[NLEN];
            scanf("%s", name);
            int total = countBefore(root, name);
            printf("%d\n", total);
        }
    }

    if (root != NULL) { //POST ORDER TRAVERSAL TO FREE ALL NODES
        bye_tree(root);
    }
}

tree_node* create_node(char name[], int numTix, tree_node *root){ //new node / update existing node
    tree_node *temp = findNode(root, name);
    if (temp == NULL) { //temp isn't in the tree, so make a tree_node for it
        temp = (tree_node*)malloc(sizeof(tree_node));
        strcpy(temp->name, name);
        temp->tickets = numTix;
        temp->depth = 1;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    //temp is in the tree so update the amount of tickets they have
    temp->tickets += numTix;
    return temp;
}

tree_node* insert(tree_node *root, tree_node *newNode){ //add to tree
    if (root == NULL) { //empty tree --> newNode is the root of the tree now
        newNode->depth = 0;
        return newNode;
    }
    else {
        if (strcmp(newNode->name, root->name) < 0) { //name to insert is on the left (alphabetically) of the root's name
            if (root->left != NULL) { //left children exist
                newNode->depth++; //increase depth before we go a level deeper
                root->left = insert(root->left, newNode);
            }
            else { //newNode is the new left child
                root->left = newNode;
            }
        }
        else { //name to insert is on the right (alphabetically) of the root's name
            if(root->right != NULL) { //right children exist
                newNode->depth++; //increase depth before we go a level deeper
                root->right = insert(root->right, newNode);
            }
            else { //newNode is the new right child
                root->right = newNode;
            }
        }
        return root;
    }
}

tree_node* findNode(tree_node *root, char name[]){ //find node with the customer's name
    if (root != NULL) {
        if (strcmp(name, root->name) == 0) { //found node with customer name
            return root;
        }
        if (strcmp(name, root->name) < 0) { //customer name is to the left (alphabetically) of the root's name, so search left subtree
            return findNode(root->left, name);
        }
        else { //customer name is to the right (alphabetically) of the root's name, so search right subtree
            return findNode(root->right, name);
        }
    }
    else{
        return NULL; //no node in the tree exists with that name
    }
}

tree_node* parent(tree_node *root, tree_node *node){ //finds parent of node
    if (root == NULL || root == node) { // Take care of NULL cases
        return NULL;
    }
    if (root->left == node || root->right == node) { // The root is the direct parent of node
        return root;
    }
    if (strcmp(node->name, root->name) < 0) { // Look for node's parent on the left side of the tree
        return parent(root->left, node);
    }
    else if (strcmp(node->name, root->name) > 0) {  // Look for node's parent on the right side of the tree
        return parent(root->right, node);
    }
    return NULL; // Catch any other extraneous cases.
}

tree_node* maxVal(tree_node *root){ //finds maxVal of the subtree with root "root"
    // Root stores the maximal value.
    if (root->right == NULL) {
        return root;
    }
    else { // The right subtree of the root stores the maximal value
        return maxVal(root->right);
    }
}

int isLeaf(tree_node *node){ //finds if this node is a leaf node
    return (node->left == NULL && node->right == NULL);
}

int hasOnlyLeftChild(tree_node *node){ //determines if this node has only left children
    return (node->left!= NULL && node->right == NULL);
}

int hasOnlyRightChild(tree_node *node){ //determines if this node has only right children
    return (node->left== NULL && node->right != NULL);
}

void depthChange(tree_node *root) { //change the depth of everything in the tree (including the root) to itself -1
    if (root != NULL) {
        depthChange(root->left);
        depthChange(root->right);
        root->depth--;
    }
}

tree_node* delete(tree_node *root, char name[], int numTix){ //deletes a specific number of tickets from customer with name "name", CHANGE THE DEPTHS
    tree_node *delnode, *new_del_node, *save_node;
    tree_node *par;
    char newName[NLEN];
    int newTickets;

    if (root == NULL) return root;

    delnode = findNode(root, name);
    if (delnode == NULL) return root;

    delnode->tickets -= numTix;
    if (delnode->tickets > 0) return root;

    par = parent(root, delnode);

    //********case 1**********
    //Take care of the case where the node to delete is a leaf node
    if (isLeaf(delnode)) { //case 1
        if (par == NULL) { //deleting the only node in the tree
            if (delnode->tickets <= 0) free(root);
            return NULL;
        }
        if (par->left == delnode) { //Deletes the node of it's a left child
            if (delnode->tickets <= 0) free(par->left);
            par->left = NULL;
        }
        else { //Deletes the node if it's a right child
            if (delnode->tickets <= 0) free(par->right);
            par->right = NULL;
        }
        return root;
    }

    //**********case 2***********
    //Take care of the case where the node to be deleted only has a left child
    if (hasOnlyLeftChild(delnode)) { //case 2.1
        if (par == NULL) { //deleting the root node of the tree
            if (delnode->tickets <= 0){
                save_node = delnode->left;
                depthChange(save_node); //make the depth of everything below delnode -1
                free(delnode); //free the node to delete
                return save_node; //return the new root of the resulting tree
            }
        }
        if (par->left == delnode) { //deletes the node if it has a left child
            if (delnode->tickets <= 0) {
                save_node = par->left; //save the node to delete
                par->left = par->left->left; //readjust the parent pointer
                depthChange(par->left); //make the depth of everything below delnode -1
                free(save_node); //free the memory for the deleted node
            }
        }
        else { //deletes the node if it has a right child
            if (delnode->tickets <= 0) {
                save_node = par->right; //save the node to delete
                par->right = par->right->left; //readjust the parent pointer
                depthChange(par->right); //make the depth of everything below delnode -1
                free(save_node); //free the memory for the deleted node
            }
        }
        return root;
    }

    //Take care of the case where the node to be deleted only has a right child
    if (hasOnlyRightChild(delnode)) { //case 2.2
        if (par == NULL) { //node to delete is the root node
            if (delnode->tickets <= 0) {
                save_node = delnode->right;
                depthChange(save_node); //make the depth of everything below delnode -1
                free(delnode); //free the node to delete
                return save_node; //return the new root of the resulting tree
            }
        }
        if (par->left == delnode) { //deletes the node if it has a left child
            if (delnode->tickets <= 0) {
                save_node = par->left; //save the node to delete
                par->left = par->left->right; //readjust the parent pointer
                depthChange(par->left); //make the depth of everything below delnode -1
                free(save_node); //free the memory for the deleted node
            }
        }
        else { //deletes the node if it has a right child
            if (delnode->tickets <= 0) {
                save_node = par->right; //save the node to delete
                par->right = par->right->right; //readjust the parent pointer
                depthChange(par->right); //make the depth of everything below delnode -1
                free(save_node); //free the memory for the deleted node
            }
        }
        return root;
    }

    //***************case 3****************
    //if your code reaches here, delnode has 2 children
    //find the new physical node to delete and save the info of delnode
    new_del_node = maxVal(delnode->left); //node that will actually be freed
    strcpy(newName, new_del_node->name);
    newTickets = new_del_node->tickets;

    delete(root, newName, newTickets); //now delete the proper node to keep shape

    //copy all of new_del_node info to delnode, effectively switching them
    strcpy(delnode->name, newName);
    delnode->tickets = newTickets;

    return root;
}

int count(tree_node *root){ //count up the total number of nodes in the tree
    if (root != NULL) {
        return 1 + count(root->left) + count(root->right);
    }
    else { //no tree to count nodes from
        return 0;
    }
}

double add(tree_node *root){ //adds up the total number of tickets held by all the people in the tree
    if (root != NULL) {
        return root->tickets + add(root->left) + add(root->right);
    }
    else { //no node to add tickets from
        return 0;
    }
}

int height(tree_node* root){ //calculates the height of each subtree, one node = height of 0, empty tree = height of -1
    int leftHeight, rightHeight;
    if(root == NULL) { //empty tree has a height of -1
        return -1;
    }
    leftHeight = height(root->left);
    rightHeight = height(root->right);
    if(leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

int countBefore(tree_node *root, char name[]) { //count the number of tickets of everyone in the tree before name alphabetically
    if (root == NULL) {
        return 0;
    }
    if (strcmp(root->name, name) <= 0) {
        return root->tickets + countBefore(root->left, name) + countBefore(root->right, name);
    }
    else{
        return countBefore(root->left, name);
    }
}

void bye_tree(tree_node *root) { //post order traversal to free the tree
    if (root != NULL) {
        bye_tree(root->left);
        bye_tree(root->right);
        free(root);
    }
}