//Hash table
//|-meTju-|
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct h_item{
    char *key, *name;
}ITEM;


typedef struct table{
    ITEM **array;
    long count,size;
}HASH_TABLE;

long hash(char *key){
    long hash = 5381;
    int c;

    while (c = *key++){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

ITEM *create_item(char *key, char *name){
    ITEM * new;

    new = (ITEM *)malloc(sizeof(ITEM));
    new->key = (char *)malloc(sizeof(char)*strlen(key) + 1);
    new->name = (char *)malloc(sizeof(char)*strlen(name) + 1);

    strcpy(new->key,key);
    strcpy(new->name,name);
    return new;
}

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

void insert(HASH_TABLE *table){
    int hash_key;
    char *key,*name;
    ITEM *new;

    scanf("Your key: %s\n Your name: %s\n",key,name);
    hash_key = hash(key);
    new = create_item(key,name);

    table->array[hash_key] = new;
}

void main(){
    char input;
    HASH_TABLE table;
    table = create_hashtable(10);
    
    printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
    scanf(" %c",&input);
    while(input != 'q'){
        switch (input){
        case 'i':
            insert(&table);
            break;
        case 'd':
            break;
        case 's':
            break;
        case 'c':
            break;
        default:
            break;
        }
        printf("Select your operation - (s)earch, (c)reate, (i)nsert, (d)elete, (p)rint, (q)uit: ");
        scanf(" %c",&input);
    }
    printf("\nQuitting...\n");
}