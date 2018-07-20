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

typedef struct n_ {
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

        if(argc != 2) {
                printf("Usage: %s <filename>\n", argv[0]);
                exit(1);
        }

        Node *begin = NULL;
        Node *zipCodeNode=NULL;

        begin = importTree(argv[1]);

        if(begin == NULL) {
                perror("\nUnable to import tree from file");
                exit(1);
        }

        int num = 0;
        int zipCount;
        int zipSearch = 0;
        char *stateSearch = malloc(sizeof(char)*3);

        while(num!=3) {// The program should continue to run and operate until the user selects three.

                printf("\n1: Find number in a state\n2: Find a ZIP code\n3: Exit\n> "); \
                scanf("%d", &num);

                switch(num) {

                case 1: {

                        printf("\nEnter the state: ");
                        scanf("%s", stateSearch);
                        zipCount = findStateCount(begin, stateSearch);

                        if(zipCount== 0) {

                                printf("\nNo results found for that state\n");
                        }
                        else {
                                printf("\nThe state of %s has %d zip codes in the file.\n", stateSearch,zipCount);
                        }
                        break;
                }

                case 2: {
                        printf("\nEnter the ZIP you want to find: ");
                        scanf("%d", &zipSearch);
                        zipCodeNode = findZipCode(begin, zipSearch);

                        if(zipCodeNode == NULL) {
                                printf("\nNo results found for zip code %d\n", zipSearch);
                        }

                        else {
                                printf("\nResult found for zip code %d: ", zipSearch);
                                printf("\n\tCity: %s", zipCodeNode->city);
                                printf("\n\tState: %s\n", zipCodeNode->state);

                        }
                        break;
                }
                case 3: {
                        printf("\nProgram Terminated.\n");
                        freeTree(begin);
                        free(stateSearch);
                        exit(0);

                        break;
                }

                default: {

                        printf("\nError - not a valid option. Try again.\n");
                }

                }

                freeTree(begin);
                free(stateSearch);

                return 0;
        }
}

void freeTree(Node* root){

        if(root == NULL) {
                return;
        }

        freeTree(root->left);
        freeTree(root->right);
        free(root->city);
        free(root);
}

int findStateCount(Node* begin, char* state){

        if(begin == NULL) {
            return 0;
        }
        else {
                if(strcmp(begin->state, state) == 0) {
                        return 1 + findStateCount(begin->left, state) + findStateCount(begin->right, state);
                }
        }
        return findStateCount(begin->left, state) + findStateCount(begin->right, state);
}

Node* addNode(Node* root, Node* newNode) {

        if (newNode == NULL) {
                perror("Error, New node could not be created\n");
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

        }
}

Node* importTree(char* filename){

        Node* begin = NULL;
        FILE *file = fopen(filename, "r");

        if(file == NULL) {
                perror("File could not be opened");
                exit(1);
        }

        Node* newNodePtr = malloc(sizeof(Node));

        if (newNodePtr == NULL) {
                perror("Could not allocate the memory needed, exiting program. \n");
                exit(1);
        }

        newNodePtr->city = malloc(sizeof(char)*30);

        if ((newNodePtr->city)== NULL) {
                perror("Could not allocate the memory needed, exiting program.\n");
                exit(1);
        }

        newNodePtr->left = NULL;
        newNodePtr->right = NULL;

        char*  line = malloc(sizeof(char)*50);

        if(fgets(line, 50, file) == NULL) {
                if (!feof(file)) {
                        printf("\n");
                        exit(1);
                }
        }

        char* temp = strtok(line, ",");
        newNodePtr->zipCode = atoi(temp);
        temp = strtok(NULL, ",");
        strcpy(newNodePtr->city, temp);
        temp = strtok(NULL, ",");
        strcpy(newNodePtr->state, temp);
        newNodePtr->state[2] = '\0';

        begin = addNode(begin, newNodePtr);

        if(!begin) {
                printf("Root is NULL\n");
                exit(1);
        }

        free(line);

        return begin;
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
                find = findZipCode(root->left, zipCode);

                if(find!= NULL) {
                        return find;
                }
                find = findZipCode(root->right, zipCode);
                if(find!= NULL) {
                        return find;
                }
        }
        return NULL;
        //Input: the root of the tree and the zip code you are searching for.Return: a pointer to the node that you found matched the zip code, or NULL if not found. Using the zip code, search the tree for a matching node. There will either be one node found with that zip code, or none found. This function must be recursive. You are not allowed to use system calls.
}
