//Hash table template without any collision handling
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
long hash(char *key,int size){
    long hash = 5381;
    int c;

    while (c = *key++){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
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

//Basic insert
void insert(HASH_TABLE *table,char *key,char *name){
    int index;
    ITEM *new;
    
    index = hash(key,table->size);
    new = create_item(key,name);

    table->array[index] = new;
    table->count += 1;
}

//Basic search
void search(HASH_TABLE table){
    char key[30];
    int index;
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
    int index;
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
}

//Prints not NULL indexes in hash table
void print_table(HASH_TABLE table){
    for(int i = 0; i < table.size;i++){
        if(table.array[i] != NULL){
            printf("On index [%d] is key: [%s] and name: [%s]\n",i,table.array[i]->key,table.array[i]->name);
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
    char name[17];
    srand(time(0));

    for(int i = 0;i < val;i++){
        rand_string(key,16);
        rand_string(name,16);
        insert(table,key,name);
    }
}

void main(){
    char input;
    char *key, *name;
    HASH_TABLE table;
    clock_t start,end;
    double cpu_time;
    int val;
    table = create_hashtable(5);
    
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
            break;
        case 'p':
            print_table(table);
        default:
            break;
        }
        printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}