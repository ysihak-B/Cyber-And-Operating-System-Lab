/*
*
* main.c
*
This is the main function for the hashtable implementation
use "gcc -o main main.c" command to run the program.
*/

#include <stdlib.h>
#include <assert.h>
#include "./hashtable/hashtable.h"

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

    assert( add(table, "Test1 Key", 11) == true);
    assert( add(table, "Test Key", 11) == true);
    assert( add(table, "Test Key", 11) == false);

    struct Binding* binding1 =  find(table, "Test1 Key");
    assert( binding1 != NULL &&  binding1->value == 11);

    struct Binding* binding =  find(table, "Test Key");
    assert( binding != NULL &&  binding->value == 11);
    
    delete_table(table);

    return 0;
}



