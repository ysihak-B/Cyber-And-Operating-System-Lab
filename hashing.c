// #include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> 
#include <assert.h>

const int BUCKET_COUNT = 7;

struct Binding{
    const char* key;
    int value;
    struct Binding* next;
};

struct HashTable{
    struct Binding **buckets;
};

struct HashTable* create();

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



int power(int x, int y);

int power(int x, int y){
    if(y > 0){
        return x * power(x, y-1);
    }
    return 1;
}



unsigned int hash(const char* key);

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


struct Binding* find(struct HashTable* table, const char* key);

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


bool add(struct HashTable* table, const char* key, int value);

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


bool remove(struct HashTable* table, const char* key);

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


void delete_table (struct HashTable* table);

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
                chain = table->buckets[i];
            }
        }
    }
    
    free(table);
    
}



    
int main(int argc, char const *argv[])
{
    struct HashTable* table = create();
    
    assert(add(table, "ysihak", 5) == true);
    assert(add(table, "abebe", 4) == true);
    assert(add(table, "alemu", 3) == true);
    assert(add(table, "kibret", 6) == true);
    assert(add(table, "bamlaku", 7) == true);
    
    
    assert(add(table, "haile", 2) == true);
    assert(add(table, "haile", 1) == false);
    
    assert(remove(table, "kibret") == true);
    assert(remove(table, "alemu") == true);
    
    assert( find(table, "ysihak") != NULL);
    assert( find(table, "kibret") == NULL);
    assert( find(table, "Test Key") == NULL);

    assert( add(table, "Test Key", 11) == true);
    assert( add(table, "Test Key", 11) == false);

    struct Binding* binding =  find(table, "Test Key");
    assert( binding != NULL &&  binding->value == 11);
    
    delete_table(table);

    return 0;
}
