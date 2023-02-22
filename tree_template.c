//Tree template without self balancing coded 
//|-meTju-|
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
}NODE;

int search(int val,NODE *root){
    NODE *temp;

    temp = root;
    if(temp == NULL){
        printf("No node with value [%d] is in tree\n",val);
        return 0;
    }
    if(temp->value == val){
        printf("Node with value [%d] exists on adress: %p\n",temp->value,temp);
        return 1;
    }
    if(val < temp->value){
        search(val,temp->left);
    }
    if(val > temp->value){
        search(val,temp->right);
    }
}

int insert(int val,NODE **root){
    NODE *temp;
    NODE *new;

    new = (NODE *)malloc(sizeof(NODE));
    new->value = val;
    new->left = NULL;
    new->right = NULL;

    if(*root == NULL){
        *root = new;
        return 1;
    }

    temp = *root;
    if(val < temp->value){
        insert(val,&temp->left);
    }
    if(val > temp->value){
        insert(val,&temp->right);
    }
}

//WIP
int delete(int val,NODE **root){
    NODE *temp;
    NODE *garb;

    temp = *root;
    if(temp == NULL){
        printf("No node with value [%d] is in tree\n",val);
        return 0;
    }
    //Left child node
    if(temp->left->value == val){
        //Case 1
        if(temp->left->right == NULL && temp->left->left == NULL){
            free(temp->left);
            temp->left = NULL;
        }
        //Case 2
        if(temp->left->right != NULL){
            garb = temp->left;
            temp->left = temp->left->right;
            free(garb);
        }else if(temp->left->left != NULL){
            garb = temp->left;
            temp->left = temp->left->left;
            free(garb);
        }
        //Case 3 WIP... 
        return 1;
    }
    //Right child node
    if(temp->right->value == val){
        //Case 1
        if(temp->right->right == NULL && temp->right->left == NULL){
            free(temp->right);
            temp->right = NULL;
        }
        //Case 2
        if(temp->right->right != NULL){
            garb = temp->right;
            temp->right = temp->right->right;
            free(garb);
        }else if(temp->right->left != NULL){
            garb = temp->right;
            temp->right = temp->right->left;
            free(garb);
        }
        //Case 3 WIP...
        return 1;
    }
    if(val < temp->value){
        delete(val,&temp->left);
    }
    if(val > temp->value){
        delete(val,&temp->right);
    }

}

int create(int val,NODE **root){
    int number;
    srand(time(0));
    for(int i = 0;i < val;i++){
        number = rand() % 100;
        printf("Creating node with number.. %d\n",number);
        insert(number,root);
    }
}

void main(){
    NODE *root = NULL;
    int val;
    char input;

    printf("Select your operation - s = search, c = create, i = insert, d = delete, q = quit: ");
    scanf("%c",&input);

    while(input != 'q'){
        switch (input){
        case 's':
            printf("Value you wish to search for: ");
            scanf("%d",&val);
            search(val,root);
            break;
        case 'c':
            printf("Number of new nodes: ");
            scanf("%d",&val);
            create(val,&root);
            break;
        case 'd':
            printf("Value you wish to delete: ");
            scanf("%d",&val);
            delete(val,&root);
            break;
        case 'i':
            printf("Value of new node: ");
            scanf("%d",&val);
            insert(val,&root);
            break;
        default:
            break;
        }
        printf("Your operation? s = search, c = create, i = insert, d = delete, q = quit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}