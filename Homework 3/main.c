//
//  main.c
//  Homework 3
//
//  Created by Brendan Krekeler on 7/15/18.
//  Copyright © 2018 Brendan Krekeler. All rights reserved.
//

#include <stdio.h>

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


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
        //Input: your command line arguments.Return: a number.Get your tree made, present options to the user, get user input and call functions accordingly. Loop the program until the user decides to quit. Take note that you will need to read in the state somehow from the user. You can assume that the user puts in a proper 2-character state code, and that there will be no problem with the input.
    
    return 0;
}

Node* addNode(Node* root, Node* newNode) {
    //Input: the root of the tree, and the new node ready to be added to the tree.
    //Return: the root of the tree
    //Add the newest node to the tree. The node has been prefilled with data, so you do not have to modify the new node in anyway. Just connect it to the tree in the manner you have been doing. This function must be recursive
}

int findStateCount(Node* root, char* state){
    
    //Input: the root of the tree and the state you are searching forReturn: the number of instances the state shows up throughout the tree
    // Using the string for the state, get a count of all nodes in the tree that have that same state. This might take a little thought, but with recursion it’s very simple. This function must be recursive. You are not allowed to use system calls.
    
}

Node* findZipCode(Node* root, int zipCode){
    
    //Input: the root of the tree and the zip code you are searching for.Return: a pointer to the node that you found matched the zip code, or NULL if not found. Using the zip code, search the tree for a matching node. There will either be one node found with that zip code, or none found. This function must be recursive. You are not allowed to use system calls.
}

void freeTree(Node* root){
    
    //Input: the root of the tree.You are to free everything that the tree has allocated. Note that there is more to the node than just an integer and pointers. The difficulty of the function does not change, however.
    
}
