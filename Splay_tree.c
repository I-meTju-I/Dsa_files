//Splay tree
//|-meTju-|

//Printing any output to terminal slows code significantly, do not use printf with //X if you want much better performance 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node{
    int value;
    struct node *left, *right, *parent;
}NODE;

//Global variable with root pointer
NODE **true_root = NULL;

//Function to find max value from left subtree when using join()
NODE *max_left(NODE *root){
    while(root->right != NULL){
        root = root->right;
    }
    return root;
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

//Splaying function that takes param NODE *root and makes it 
//root of tree using rotations and logic
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

//Split function that splits tree into two subtrees
//and returns them to delete()
void split(NODE *root,NODE **y,NODE **x){
    NODE *sub_left,*sub_right;
    splay(root);    //Splaying node with value that we want to delete
    if(root->right != NULL){
        sub_right = root->right;
        sub_right->parent = NULL;
    }else{
        sub_right = NULL;
    }
    if(root->left != NULL){
        sub_left = root->left;
        sub_left->parent = NULL;
    }else{
        sub_left = NULL;
    }
    root->right = NULL;
    root->left = NULL;
    *y = sub_left;
    *x = sub_right;
}

//Returns one tree that is made of left and right subtrees
NODE *join(NODE *sub_left,NODE *sub_right){
    NODE *x;
    if(sub_left == NULL){
        return sub_right;
    }
    if(sub_right == NULL){
        return sub_left;
    }
    x = max_left(sub_left);
    splay(x);
    x->right = sub_right;
    sub_right->parent = x;
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
        //printf("Node already exist\n"); //X
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
    NODE *sub_left, *sub_right, *temp;
    temp = *root;

    while(val != temp->value){
        if(val < temp->value){
             temp = temp->left;
        }else{
            temp = temp->right;
        }
    }

    split(temp,&sub_left,&sub_right);       //Passing temp to split and making it root
    free(temp);     //Dealocating temp      //and then isolating it
    *true_root = join(sub_left,sub_right);  //Making joined subtrees one root
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
        printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}