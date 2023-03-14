//Hash table template with linear probing collision handler
//|-meTju-|
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//Item struct containing key and name
typedef struct h_item{
    char *key, *name;
}ITEM;

//Hash table struct containing array of items and info about itself
typedef struct table{
    ITEM **array;
    long count,size;
}HASH_TABLE;

//Temporary hash function
unsigned long hash(char *key,int size){
    unsigned long hash = 5381;
    int c;

    while (c = *key++){
        hash = ((hash << 5) + hash) + c;
    }
    return (hash % size);
}

//Allocates memory for ITEM and fills it with args
ITEM *create_item(char *key, char *name){
    ITEM *new;

    new = (ITEM *)malloc(sizeof(ITEM));
    new->key = (char *)malloc(sizeof(char)*strlen(key) + 1);
    new->name = (char *)malloc(sizeof(char)*strlen(name) + 1);

    strcpy(new->key,key);
    strcpy(new->name,name);
    return new;
}

//Creates new hash table at the start of program
//and allocates memory for it
HASH_TABLE create_hashtable(int size){
    HASH_TABLE new;
    new.array = (ITEM **)calloc(size,sizeof(ITEM *));

    for(int i = 0;i < size;i++){
        new.array[i] = NULL;
    }

    new.count = 0;
    new.size = size;
    return new;
}

//Collision handler for linear probing
int collision_handler(ITEM **array,ITEM *item,unsigned long index,long size){
    while(array[index] != NULL && index < size - 1){
        index += 1;
    }
    if(array[index] != NULL){
        printf("array full!\n");
        return 0;
    }else{
        array[index] = item;
        return 1;
    }
}

//Rehashes elements from smaller table into bigger one
void rehash_up(HASH_TABLE *table,ITEM **new_array,int size){
    unsigned long index;
    for(int i = 0; i < size; i++){
        if(table->array[i] != NULL){
            index = hash(table->array[i]->key,table->size);
            collision_handler(new_array,table->array[index],index,table->size);
            table->array[i] = NULL;
        }
        free(table->array[i]);
    }
    free(table->array);
    table->array = new_array;
}

//Rehashes elements from larger table into smaller one
void rehash_down(HASH_TABLE *table,int size){
    unsigned long index;
    for(int i = 0; i < size; i++){
        if(table->array[i] != NULL){
            index = hash(table->array[i]->key,table->size);
            table->array[index] = table->array[i];
            table->array[i] = NULL;
        }
    }
}

void resize(HASH_TABLE *table){
    if((double)table->count / table->size >= 0.75){
        ITEM **new_array;
        table->size *= 2;
        new_array = (ITEM **)calloc(table->size,sizeof(ITEM *));
        rehash_up(table,new_array,table->size/2);
    }/* else if((double)table->count / table->size <= 0.35){
        table->size /= 2;
        rehash_down(table,table->size*2);
        table->array = (ITEM **)realloc(table->array,2 / table->size * sizeof(ITEM *));
    } */
}
//Basic insert
void insert(HASH_TABLE *table,char *key,char *name){
    unsigned long index;
    ITEM *new;
    
    index = hash(key,table->size);
    new = create_item(key,name);
    if(table->array[index] == NULL){
        table->array[index] = new;
    }else{
        printf("Handling collision.\n");
        if(collision_handler(table->array,new,index,table->size) == 0){
            free(new->key);
            free(new->name);
            free(new);
            return;
        };
    }
    table->count += 1;
    resize(table);
}

//Basic search
void search(HASH_TABLE table){
    char key[30];
    unsigned long index;
    printf("Key that you would like to search for: ");
    scanf("%s",key);
    index = hash(key,table.size);
    if(table.array[index]== NULL){
        printf("No key with value [%s] in hash table\n",key);
    }else{
        printf("Key exists on index [%d]. Key: [%s] and name: [%s]\n",index,table.array[index]->key,table.array[index]->name);
    }
}

//Basic delete
void delete(HASH_TABLE *table){
    char key[30];
    unsigned long index;
    printf("Key that you would like to delete: ");
    scanf("%s",key);
    index = hash(key,table->size);

    if(table->array[index] == NULL){
        printf("No key with value [%s] in hash table\n",key);
    }else{
        free(table->array[index]->key);     //Memory deallocation
        free(table->array[index]->name);
        free(table->array[index]);
        table->array[index] = NULL;
        printf("Deleted key with value [%s] in hash table\n",key);
    }
    resize(table);
}

//Prints not NULL indexes in hash table
void print_table(HASH_TABLE table){
    for(int i = 0; i < table.size;i++){
        if(table.array[i] != NULL && table.array[i] != 0){
            printf("On index [%d] is key: [%s] and name: [%s]\n",i,table.array[i]->key,table.array[i]->name);
        }else{
            printf("No node on index [%d]\n",i);
        }
    }
}

//Creates random string, argument length can be max 32
void rand_string(char string[],int len){
    char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";        

    if (len > 0){          
        for (int i = 0;i < len;i++){            
            int key = rand() % 61;
            string[i] = chars[key];
        }
        string[len] = '\0';
    }
}

//Cycles through insert() val times with random keys and names
void create(HASH_TABLE *table,int val){
    char key[17];
    char name[9];
    srand(time(0));

    for(int i = 0;i < val;i++){
        rand_string(key,16);
        rand_string(name,8);
        insert(table,key,name);
    }
}

void main(){
    char input;
    char key[17], name[17];
    HASH_TABLE table;
    clock_t start,end;
    double cpu_time;
    int val;
    table = create_hashtable(4);
    
    printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
    scanf(" %c",&input);
    while(input != 'q'){
        switch (input){
        case 'i':
            printf("Your key: ");
            scanf("%s",key);
            printf("Your name: ");
            scanf("%s",name);
            insert(&table,key,name);
            break;
        case 'd':
            delete(&table);
            break;
        case 's':
            search(table);
            break;
        case 'c':
            printf("Number of new keys: ");
            scanf("%d",&val);
            start = clock();
            create(&table,val);
            end = clock();
            cpu_time = (double)(end - start)/CLOCKS_PER_SEC;
            printf("Time taken: %lf sec.\n",cpu_time);
            break;
        case 'p':
            print_table(table);
            break;
        case 'b':
            printf("Table size: %d\nTable count: %d\nLoad factor: %.2f\n",table.size,table.count,(double)table.count / table.size);
        default:
            break;
        }
        printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}