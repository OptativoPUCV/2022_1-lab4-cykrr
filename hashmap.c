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
    if(this->size / this->capacity >= 0.7) enlarge(this);
    long i = hash(key, this->capacity);
    while(this->buckets[i] != NULL)  {
        i++;
        if( i > this->capacity) i = 0;
    }
    this->buckets[i]  = createPair(key, value);
    this->size++;
    this->capacity--;
//  printf("[%ld]\n", i);
}

void enlarge(HashMap * map) {
    map->buckets = realloc(map->buckets, ((long int)map->capacity *1.5)*sizeof(Pair *) );
    Pair *bucketsCpy;
    bucketsCpy = malloc((long int)map->capacity * 1.5 * sizeof(Pair *));
    if(!map->buckets) exit(-1);
    map->capacity = ((long int)map->capacity * 1.5);
    Pair * head = firstMap(map);
    while(head != NULL){
        if(head->key) { 
            char* key = head->key;
            void *value = head->value;
            head->key = NULL;
            insertMap(map, key, value);
        }
    }
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
    Pair *pair = searchMap(map, key);
    if(pair){
        pair->key = NULL;
        map->size--;

    }
}

Pair * searchMap(HashMap * this,  char * key) {   
    long i = hash(key, this->capacity);
    while (this->buckets[i] && (strcmp(key, this->buckets[i]->key) != 0)){
        i++;
        if(i > this->capacity) return NULL;
    }
    this->current = i;
    return this->buckets[i];
    
}

Pair * firstMap(HashMap * map) {
    long i = map->current;
    while(map->buckets[i] == NULL || map->buckets[i]->key == NULL) { 
        i++;
    }
    map->current = i;
    return map->buckets[i];
}

Pair * nextMap(HashMap * map) {
    long i = map->current+1;
    while(map->buckets[i] == NULL) {
        i++;
        if(i > map->size) return NULL;
    }
    map->current = i;
    return map->buckets[i];
}
