//AVL tree
//|-meTju-|
//This version needs more testing because delete is broken
//Printing any output to terminal slows code significantly, do not use printf with //X if you want much better performance 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct node{
    int value;
    struct node *left, *right, *parent;
    int height;     //Implementation with height stored inside NODE
}NODE;

//Global variable with root pointer
NODE **true_root = NULL;

//Function to find min value from right subtree when using delete()
int min_right(NODE *root){
    NODE* temp;
    temp = root->right;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp->value;
}

//Gets height of right and left subtrees, than returns max + 1
int get_height(NODE *root){
    int left_h = 0, right_h = 0;
    if(root == NULL){
        return 0;
    }
    if(root->left != NULL){
        left_h = root->left->height;
    }
    if(root->right != NULL){
        right_h = root->right->height;
    }
    return 1 + max(left_h,right_h);
}

//Gets balance by using formula H[left subtree] - H[right subtree]
int get_balance(NODE *root){
    return get_height(root->left) - get_height(root->right);
}

//Rotation functions
void left_rotate(NODE *root){
    NODE* temp;
    temp = root->right;
    if(root->right->left != NULL){
        root->right = root->right->left;
        root->right->parent = root;
    }else{
        root->right = NULL;
    }
    if(root->parent == NULL){
        *true_root = temp;
        temp->parent = NULL;
    }else if(root == root->parent->left){
        root->parent->left = temp;
    }else{
        root->parent->right = temp;
    }
    temp->parent = root->parent;
    temp->left = root;
    root->parent = temp;

    root->height = get_height(root);
    temp->height = get_height(temp);
}

void right_rotate(NODE *root){
    NODE* temp;
    temp = root->left;
    if(root->left->right != NULL){
        root->left = root->left->right;
        root->left->parent = root;
    }else{
        root->left = NULL;
    }
    if(root->parent == NULL){
        *true_root = temp;
        temp->parent = NULL;
    }else if(root == root->parent->left){
        root->parent->left = temp;
    }else{
        root->parent->right = temp;
    }
    temp->parent = root->parent;
    temp->right = root;
    root->parent = temp;

    root->height = get_height(root);
    temp->height = get_height(temp);
}

//Function that is making rotations by using logic
//Balance factor can be from interval <-1,1>
//anything outside of it must be rotated
void rotate(NODE *temp,int val){
    int balance;
    balance = get_balance(temp);
    temp->height = get_height(temp);

    if(balance > 1){
        if(val < temp->left->value){
            right_rotate(temp);
        }else if(val > temp->left->value){
            left_rotate(temp->left);
            right_rotate(temp);
        }
    }else if(balance < -1){
        if(val > temp->right->value){
            left_rotate(temp);
        }else if(val < temp->right->value){
            right_rotate(temp->right);
            left_rotate(temp);
        }
    }
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
        return 1;
    }
    if(val > temp->value){
        search(val,temp->right);
        return 1;
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
        new->height = 1;

        *root = new;
        return 1;
    }

    temp = *root;
    if(val == temp->value){
        //printf("Node already exist\n"); //X
        return 0;
    }
    if(val < temp->value){
        insert(val,&temp->left,temp);
    }
    if(val > temp->value){
        insert(val,&temp->right,temp);
    }
    rotate(temp,val);
    return 1;
}

//Delete function using complicated logic to delete right 
//nodes and making sure pointers are set right
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
    rotate(temp,val);
    return 1;
}

//Cycles insert() with random values
int create(int val,NODE **root){
    int number;
    srand(time(0));
    for(int i = 0;i < val;i++){
        number = rand() % val + 1;
        //printf("Creating node with number.. %d\n",number); //X
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
    true_root = &root;

    printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
    scanf("%c",&input);

    while(input != 'q'){
        //printf("Current root and true_root: %p %p ",root,*true_root);
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
            printf("Height of root is: %d\n",get_height(root));
            printf("Balance of root is: %d\n",get_balance(root));
            break;
        case 'd':
            printf("Value you wish to delete: ");
            scanf("%d",&val);
            delete(val,&root);
            break;
        case 'i':
            printf("Value of new node: ");
            scanf("%d",&val);
            start = clock();
            insert(val,&root,NULL);
            end = clock();
            cpu_time = (double)(end - start)/CLOCKS_PER_SEC;
            printf("Time taken: %lf sec.\n",cpu_time);
            break;
        case 'p':
            printf("Printing tree...\n");
            print_tree(root,0);
        default:
            break;
        }
        printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}