//RedBlack tree
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

NODE **true_root = NULL;

NODE *max_left(NODE *root){
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

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
}

void splay(NODE *root){
    while(root->parent != NULL){
        if(root->parent->parent == NULL){
            if(root == root->parent->left){
                right_rotate(root->parent);
            }else{
                left_rotate(root->parent);
            }
        }else if(root == root->parent->left && root->parent == root->parent->parent->left){
            right_rotate(root->parent->parent);
            right_rotate(root->parent);
        }else if(root == root->parent->right && root->parent == root->parent->parent->right){
            left_rotate(root->parent->parent);
            left_rotate(root->parent);
        }else if(root == root->parent->right && root->parent == root->parent->parent->left){
            left_rotate(root->parent);
            right_rotate(root->parent);
        }else{
            right_rotate(root->parent);
            left_rotate(root->parent);
        }
    }
}

NODE *split(NODE *root,NODE **y,NODE **x){
    NODE *sub_left,*sub_right;
    splay(root);
    if(root->right != NULL){
        sub_right = root->right;
        sub_right->parent = NULL;
    }else{
        sub_right = NULL;
    }
    sub_left = root;
    sub_left->right = NULL;
    root = NULL;
    *y = sub_left;
    *x = sub_right;
}

NODE *join(NODE *sub_left,NODE *sub_right){
    NODE *temp;
    NODE *x;
    if(sub_left == NULL){
        *true_root = sub_right;
    }
    if(sub_right == NULL){
        *true_root = sub_left;
    }
    x = max_left(sub_left);
    splay(x);
    x->right = temp;
    temp->parent = x;
    return x;
}

int search(int val,NODE **root){
    NODE *temp;

    temp = *root;
    if(temp == NULL){
        printf("No node with value [%d] is in tree\n",val);
        splay(temp->parent);
        return 0;
    }
    if(temp->value == val){
        printf("Node with value [%d] exists on adress: %p\n",temp->value,temp);
        splay(temp);
        return 1;
    }
    if(val < temp->value){
        search(val,&temp->left);
    }
    if(val > temp->value){
        search(val,&temp->right);
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
        splay(*root);
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

//WIP, NOT WORKING YET
int delete(int val,NODE **root){
    NODE *sub_left, *sub_right, *temp;
    temp = *root;
    split(temp,&sub_left,&sub_right); 
    if(sub_left != NULL){
        sub_left->left->parent = NULL;
        free(sub_left->left);
        sub_left->left = NULL;
    }
    *true_root = join(sub_left->left,sub_right);
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
    true_root = &root;

    printf("Select your operation - s = search, c = create, i = insert, d = delete, p = print, q = quit: ");
    scanf("%c",&input);

    while(input != 'q'){
        switch (input){
        case 's':
            printf("Value you wish to search for: ");
            scanf("%d",&val);
            start = clock();
            search(val,&root);
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