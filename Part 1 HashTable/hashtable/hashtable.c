/**
 * hashtable.c
 *
 * This is the implementation file for the interfaces found in hashtable.h.
 * This file implements hashtable using using separate chaining technique.
 * Specifically, it implements the Binding and HashTable structs, and the functions declared
 * in the hashtable.h file
 */
#include <stdbool.h> 
#include <assert.h>
#include <stdlib.h>

const int BUCKET_COUNT = 7; 
struct Binding{
    const char* key;
    int value;
    struct Binding* next;
};

struct HashTable{
    struct Binding **buckets;
};


/* this function in going to create a hash table and alocate memory 
which the whole program is based up on.
*/
struct HashTable* create(){
    struct HashTable* table;
    table = (struct HashTable*)malloc(sizeof(struct HashTable));
    if(table == NULL){
        // printf("memory error");
        return NULL;
    }
    else{
        // printf("\nthe table is created");
    }
    
    table->buckets = (struct Binding**)malloc(sizeof(struct Binding*) * BUCKET_COUNT);
    if(table->buckets == NULL){
        // printf("\nmemory error");
        return NULL;
    }
    else{
        // printf("\nthe buckets are created\n");
    }
    
    for(int i=0; i<BUCKET_COUNT; i++){
        table->buckets[i] = NULL;
    }
    
    return table;
}

// this function will compute the power of two values and returns the result
int power(int x, int y){
    if(y > 0){
        return x * power(x, y-1);
    }
    return 1;
}


//this function hashes(changes) the given key and returns a corresponding integer value.
unsigned int hash(const char* key){
    int p = 31;
    int total = 0;
    char* alphabets = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; key[i] != '\0'; i++){
        for(int j = 0; j < 26; j++){
            if (key[i] == alphabets[j]){
                int pos = j + 1;
                total = total + (pos * (power(p, i)));
            }
            else if(key[i] == ' '){
                total = total + (27 * (power(p, i)));
            }
        }
    }
    return total % BUCKET_COUNT;   
}


/* 
this function searches for the given key accordingly with its hash value
and returns its pointer if the value exists otherwise returns null
*/
struct Binding* find(struct HashTable* table, const char* key){
    unsigned int hashed_value = hash(key);
    struct Binding *chain, *prev;
    chain = table->buckets[hashed_value];
    for(; chain != NULL;){
        if(chain->key == key){
            return chain;
        }
        else{
            prev = chain;
            chain = chain->next;
        }
    }
    return NULL;
}

/*
this function is going to add the given key at its hash value and returns true
if it doesn't exist previously and if it exists, it will only update the value
and return false.
*/
bool add(struct HashTable* table, const char* key, int value){
    struct Binding *temp;
    struct Binding* new_node = (struct Binding*)malloc(sizeof(struct Binding));
    unsigned int hashed_value = hash(key);
    struct Binding* binding = find(table, key);
    if(binding == NULL){
        temp = table->buckets[hashed_value];
        table->buckets[hashed_value] = new_node;
        new_node->key = key;
        new_node->value = value;
        new_node->next = temp;
        return true;
    }
    else{
        binding->value = value;
        return false;
    }
}

/*
this functions will erase the given key from the table using its hash value
and return true if it exists otherwise it returns false
*/
bool remove(struct HashTable* table, const char* key){
    unsigned int hashed_value = hash(key);
    struct Binding *chain, *prev;
    chain = table->buckets[hashed_value];
    prev = NULL;
    for(;chain != NULL;){
        if(chain->key == key){
            if(prev != NULL){
                prev->next = chain->next;
            }
            free(chain);
            return true;
        }
        else{
            prev = chain;
            chain = chain->next;
        }
    }
    return false;
}


// this function will free all dynamically allocated memory by traversing through each chain.
void delete_table (struct HashTable* table){
    for(int i=0; i<BUCKET_COUNT; i++){
        struct Binding *chain, *prev;
        for(prev = NULL, chain = table->buckets[i]; chain != NULL; 
        prev = chain, chain = chain->next){
            if(chain->next == NULL){
                if(prev != NULL){
                    prev->next = chain->next;
                }
                free(chain);
                prev = NULL;
                chain = table->buckets[i];
            }
        }
    }
    
    free(table);
    
}
