//Tree template without self balancing coded 
//|-meTju-|

//Printing any output to terminal slows code significantly, do not use printf with //X if you want much better performance 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
}NODE;

int min_right(NODE *root){
    NODE* temp;
    temp = root->right;
    while(temp->left != NULL){
        temp = temp->left;
    }
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

int insert(int val,NODE **root,NODE *par){
    NODE *temp;
    NODE *new;

    if(*root == NULL){
        new = (NODE *)malloc(sizeof(NODE));
        new->value = val;
        new->left = NULL;
        new->right = NULL;
        new->parent = par;


        *root = new;
        return 1;
    }

    temp = *root;
    if(val == temp->value){
        printf("Node already exist\n"); //X
        return 0;
    }
    if(val < temp->value){
        insert(val,&temp->left,temp);
    }
    if(val > temp->value){
        insert(val,&temp->right,temp);
    }
}

int delete(int val,NODE **root){
    NODE *temp;
    NODE *garb;
    int temp_val;

    temp = *root;
    if(temp == NULL){
        printf("No node with value [%d] is in tree\n",val);
        return 0;
    }else if(temp->value == val){
        //Case 1
        if(temp->right == NULL && temp->left == NULL){
            if(temp->parent == NULL){
                *root = NULL;
            }else if(temp->parent->left == temp){
                temp->parent->left = NULL;
            }else if(temp->parent->right == temp){
                temp->parent->right = NULL;
            }
            free(temp);
            return 1;
        //Case 2
        }else if(temp->right != NULL && temp->left == NULL){
            garb = temp->right;
            if(temp->parent == NULL){
                *root = temp->right;
                temp->right->parent = NULL;
            }else if(temp->parent->left == temp){
                temp->parent->left = garb;
            }else if(temp->parent->right == temp){
                temp->parent->right = garb;
            }
            free(temp);
            return 1;
        }else if(temp->right == NULL && temp->left != NULL){
            garb = temp->left;
            if(temp->parent == NULL){
                *root = temp->left;
                temp->left->parent = NULL;
            }else if(temp->parent->left == temp){
                temp->parent->left = garb;
            }else if(temp->parent->right == temp){
                temp->parent->right = garb;
            }
            free(temp);
            return 1;
        //Case 3
        }else{
            temp_val = min_right(temp);
            delete(temp_val,&temp);
            temp->value = temp_val;
            return 1;
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
        number = rand() % val + 1;
        printf("Creating node with number.. %d\n",number); //X
        insert(number,root,NULL);
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

    printf("Select your operation - s = search, c = create, i = insert, d = delete, p = print, q = quit: ");
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
            insert(val,&root,NULL);
            break;
        case 'p':
            printf("Printing tree...\n");
            print_tree(root,0);
        default:
            break;
        }
        printf("Select your operation - s = search, c = create, i = insert, d = delete, p = print, q = quit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}