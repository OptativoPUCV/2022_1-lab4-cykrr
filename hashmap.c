#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include "util.h"

typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * this, char * key, void * value) {
    long i = hash(key, this->capacity);
    while(this->buckets[i] != NULL)  {
        if (i < this->capacity)
            i++;
        else    i = 0;
    }
    this->buckets[i]  = createPair(key, value);
    this->size++;
    printf("[%ld]\n", i);
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (!map) {
        err_msg("K:No se pudo crear el mapa");
        exit(1);
    }
    map->size = 0;
    map->current = -1;

    map->capacity = capacity;
    map->buckets = malloc(sizeof(Pair*)*capacity);

    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
