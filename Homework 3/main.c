//
//  main.c
//  Homework 3
//
//  Created by Brendan Krekeler on 7/15/18.
//  Copyright © 2018 Brendan Krekeler. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n_{
    int zipCode; //A zip code that exists in the given city/state
    char* city; //Will point to a city name
    char state[3]; // A state abbreviation. Note that we need room for the NULL terminator!

    struct n_* left; // connections to other nodes
    struct n_* right; // connection to other nodes

} Node;

Node* addNode(Node* root, Node* newNode);
int findStateCount(Node* root, char* state);
Node* findZipCode(Node* root, int zipCode);
void freeTree(Node* root);
Node* importTree(char* filename);


int main(int argc, char** argv) {

        if(argc != 2) { //sends error and exits program if file is not provided

                printf("Usage: %s <filename>\n", argv[0]);
                exit(1);
        }

        Node *root = NULL;
        Node *zipNode=NULL;

        root = importTree(argv[1]);

        if(root == NULL) { //error check to see if file can be opened

                printf("\nUnable to import tree from file");
                exit(1);

        }
        int num, zipCount,zipSearch = 0;
        char *stateSearch = malloc(sizeof(char)*3);

        while(num!=3) {//loop runs until user selects 3 to terminate program

                printf("\n1: Find number in a state\n2: Find a ZIP code\n3: Exit\n> "); \
                scanf("%d", &num);

                switch(num) {

                case 1: {//selection tells how many zip codes are in a state

                        printf("\nEnter the state: ");
                        scanf("%s", stateSearch);
                        zipCount = findStateCount(root, stateSearch);

                        if(zipCount== 0) {

                                printf("\nNo results found for that state\n");
                        }
                        else {
                                printf("\nThe state of %s has %d zip codes in the file.\n", stateSearch,zipCount);
                        }
                        break;
                }

                case 2: {//selection finds city and state
                        printf("\nEnter the ZIP you want to find: ");
                        scanf("%d", &zipSearch);
                        zipNode = findZipCode(root, zipSearch);

                        if(zipNode == NULL) {  //if zip code is not found
                                printf("\nNo results found for zip code %d\n", zipSearch);
                        }

                        else {  //if zip code is found
                                printf("\nResult found for zip code %d: ", zipSearch);
                                printf("\n\tCity: %s", zipNode->city);
                                printf("\n\tState: %s\n", zipNode->state);

                        }
                        break;
                }
                case 3: {//selection terminates program
                        printf("\nProgram Terminated.\n");
                        freeTree(root);
                        free(stateSearch);
                        exit(0);

                        break;
                }

                default: {

                        printf("\nError - not a valid option. Try again.\n");
                }

                }

        //frees memory used in program
        freeTree(root);
        free(stateSearch);

        return 0;
        //Input: your command line arguments.Return: a number.Get your tree made, present options to the user, get user input and call functions accordingly. Loop the program until the user decides to quit. Take note that you will need to read in the state somehow from the user. You can assume that the user puts in a proper 2-character state code, and that there will be no problem with the input.
        }
}

Node* addNode(Node* root, Node* newNode) {

        if (newNode == NULL) {
                printf("Error, New node could not be created\n");
                exit(1);
        }

        if (root == NULL) {
                return newNode;
        }
        else {

                if(newNode->zipCode > root->zipCode) {
                        root->right = addNode(root->right,newNode);
                }

                if(newNode->zipCode < root->zipCode) {
                        root->left = addNode(root->left,newNode);
                }

                return root;


                //Input: the root of the tree, and the new node ready to be added to the tree.
                //Return: the root of the tree
                //Add the newest node to the tree. The node has been prefilled with data, so you do not have to modify the new node in anyway. Just connect it to the tree in the manner you have been doing. This function must be recursive
        }
}

Node* importTree(char* filename){

        Node* root = NULL;
        FILE *file = fopen(filename, "r");

        if(file == NULL) {
                printf("Error, could not open file.\n");
                exit(1);
        }

        Node* nodePtr = malloc(sizeof(Node));

        if (nodePtr == NULL) {
                printf("Was not able to allocate memory. \n");
                exit(1);
        }

        nodePtr->city = malloc(sizeof(char)*30);

        if ((nodePtr->city)== NULL) {
                printf("Was not able to allocate memory.\n");
                exit(1);
        }

        nodePtr->left = NULL;
        nodePtr->right = NULL;

        char*  line = malloc(sizeof(char)*50);

        if(fgets(line, 50, file) == NULL) {
                if (!feof(file)) {
                        printf("end\n");
                        exit(1);
                }
        }

        char* temp = strtok(line, ",");
        nodePtr->zipCode = atoi(temp);
        temp = strtok(NULL, ",");
        strcpy(nodePtr->city, temp);
        temp = strtok(NULL, ",");
        strcpy(nodePtr->state, temp);
        nodePtr->state[2] = '\0';

        root = addNode(root, nodePtr);

        if(!root) {
                printf("Root is NULL\n");
                exit(1);
        }

        free(line);

        return root;
}

int findStateCount(Node* root, char* state){

        //Input: the root of the tree and the state you are searching forReturn: the number of instances the state shows up throughout the tree
        // Using the string for the state, get a count of all nodes in the tree that have that same state. This might take a little thought, but with recursion it’s very simple. This function must be recursive. You are not allowed to use system calls.

        if(root == NULL) {//cannot find state
                return 0;
        }
        else {
                if(strcmp(root->state, state) == 0) {
                        return 1 + findStateCount(root->left, state) + findStateCount(root->right, state);
                }
        }
        return findStateCount(root->left, state) + findStateCount(root->right, state);
}

Node* findZipCode(Node* root, int zipCode){

        if(root == NULL) {
                return NULL;
        }
        else {
                if(root->zipCode == zipCode) {
                        return root;
                }
                Node *find = NULL;
                find = findZipCode(root->left, zipCode);//searches left side of tree

                if(find!= NULL) {
                        return find;
                }
                find = findZipCode(root->right, zipCode);//searches right side of tree
                if(find!= NULL) {
                        return find;
                }
        }
        return NULL;
        //Input: the root of the tree and the zip code you are searching for.Return: a pointer to the node that you found matched the zip code, or NULL if not found. Using the zip code, search the tree for a matching node. There will either be one node found with that zip code, or none found. This function must be recursive. You are not allowed to use system calls.
}

void freeTree(Node* root){

        if(root == NULL) {
                return;
        }

        freeTree(root->left);
        freeTree(root->right);
        free(root->city);
        free(root);
        //Input: the root of the tree.You are to free everything that the tree has allocated. Note that there is more to the node than just an integer and pointers. The difficulty of the function does not change, however.
}
