//Tree template without self balancing coded 
//|-meTju-|
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define COUNT 10

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
}NODE;

int min_right(NODE *root){
    NODE* temp;
    temp = root->right;
    while(temp->left != NULL){
        temp = temp->left;
    }
    //printf("Value: %d",temp->value);
    return temp->value;
}

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

    if(*root == NULL){
        new = (NODE *)malloc(sizeof(NODE));
        new->value = val;
        new->left = NULL;
        new->right = NULL;

        *root = new;
        return 1;
    }

    temp = *root;
    if(val == temp->value){
        //printf("Node already exist\n");
        return 0;
    }
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
    int temp_val;

    temp = *root;
    if(temp == NULL){
        printf("No node with value [%d] is in tree\n",val);
        return 0;
    }
    //Left child node
    if(temp->left != NULL){
        if(temp->left->value == val){
            //Case 1
            if(temp->left->right == NULL && temp->left->left == NULL){
                free(temp->left);
                temp->left = NULL;
                return 1;
            }
            //Case 2
            if(temp->left->right != NULL && temp->left->left == NULL){
                garb = temp->left;
                temp->left = temp->left->right;
                free(garb);
                return 1;
            }else if(temp->left->left != NULL && temp->left->right == NULL){
                garb = temp->left;
                temp->left = temp->left->left;
                free(garb);
                return 1;
            }else{
                //Case 3 WIP...
                temp_val = min_right(temp->left);
                delete(temp_val,&temp);
                temp->left->value = temp_val;
                return 1;
            }
        }
    }
    //Right child node
    if(temp->right != NULL){
        if(temp->right->value == val){
            //Case 1
            if(temp->right->right == NULL && temp->right->left == NULL){
                free(temp->right);
                temp->right = NULL;
                return 1;
            }
            //Case 2
            if(temp->right->right != NULL && temp->right->left == NULL){
                garb = temp->right;
                temp->right = temp->right->right;
                free(garb);
                return 1;
            }else if(temp->right->left != NULL && temp->right->right == NULL){
                garb = temp->right;
                temp->right = temp->right->left;
                free(garb);
                return 1;
            }else{
                //Case 3 WIP...
                temp_val = min_right(temp->right);
                delete(temp_val,&temp);
                temp->right->value = temp_val;
                return 1;
            }
        }
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
        //Printing any output to terminal slows code significantly, do not use in final form
        //printf("Creating node with number.. %d\n",number);
        insert(number,root);
    }
}

void print_tree(NODE *root, int level){
    if (root == NULL)
            return;
    for (int i = 0; i < level; i++)
            printf(i == level - 1 ? "|-" : "  ");
    printf("%d\n", root->value);
    print_tree(root->right, level + 1);
    print_tree(root->left, level + 1);
}


void main(){
    NODE *root = NULL;
    int val;
    char input;
    clock_t start,end;
    double cpu_time;

    printf("Select your operation - s = search, c = create, i = insert, d = delete, q = quit: ");
    scanf("%c",&input);

    while(input != 'q'){
        switch (input){
        case 's':
            printf("Value you wish to search for: ");
            scanf("%d",&val);
            start = clock();
            search(val,root);
            end = clock();
            cpu_time = (double)(end - start)/CLOCKS_PER_SEC;
            printf("Time taken: %lf sec.\n",cpu_time);
            break;
        case 'c':
            printf("Number of new nodes: ");
            scanf("%d",&val);
            start = clock();
            create(val,&root);
            end = clock();
            cpu_time = (double)(end - start)/CLOCKS_PER_SEC;
            printf("Time taken: %lf sec.\n",cpu_time);
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
        case 'p':
            printf("Printing tree...\n");
            print_tree(root,0);
        default:
            break;
        }
        printf("Your operation? s = search, c = create, i = insert, d = delete, p = print, q = quit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}