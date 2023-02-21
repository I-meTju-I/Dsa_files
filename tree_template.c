#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int value;
    struct Node *left;
    struct Node *right;
}NODE;

void search(NODE *root){
    int val;
    NODE *temp;
    scanf("%d",&val);

    temp = root;
    if(temp->value == val){
        printf("Node value: %d\nNode adress: %p\n",temp->value,temp);
    }
}

void insert(NODE **root){
    int v;
    NODE *p;
    NODE *temp;
    scanf("Value of new node: %d",&v);

    temp->value = v;
    temp->left = NULL;
    temp->right = NULL;

    if(*root == NULL){
        *root = temp;
    }
    p = *root;
}

void delete(NODE *root){

}

int create(NODE *root){

}

void main(){
    NODE *root = NULL;
    char input;

    scanf("%c",&input);

    while(input != 'q'){
        switch (input){
        case 's':
            search(root);
            break;
        case 'c':
            create(&root);
            break;
        case 'd':
            delete(&root);
            break;
        case 'i':
            insert(&root);
            break;
        default:
            break;
        }
    }
}