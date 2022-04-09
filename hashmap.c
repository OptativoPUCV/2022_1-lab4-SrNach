#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


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

void insertMap(HashMap * map, char * key, void * value) {
    if (searchMap(map, key) != NULL) return;
    long i = hash(key, map->capacity);
    Pair * par = createPair(key, value);

    while (i < map->capacity){
        if (map->buckets[i] == NULL || map->buckets[i]->key == NULL){
            map->buckets[i] = par;
            map->current = i;
            map->size++;
            return;
        }
        i++;
        if (i == map->capacity) i = 0;
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}

HashMap * createMap(long capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    
    map->buckets = (Pair**)calloc(capacity,sizeof(Pair*));
    //for (int i = 0; i < capacity; i++) map->buckets[i] = NULL;
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;

    return map;
}

void eraseMap(HashMap * map,  char * key) {  
    if (searchMap(map, key) != NULL){
        searchMap(map, key)->key = NULL;
        map->size--;
    }
}

Pair * searchMap(HashMap * map,  char * key) {
    //Si por algún motivo, hay una clave igual a la que se está buscando en un
    //espacio adelantado, y se encuentra un NULL antes, no se encontrará la key.
    for (int i = hash(key, map->capacity);i < map->capacity ; i++){
        map->current = i;
        if (map->buckets[i] == NULL) return NULL;

        if (map->buckets[i]->key == NULL) return NULL;

        if (is_equal(map->buckets[i]->key, key)) return map->buckets[i];

    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    for(int i = 0 ; i < map->capacity ; i++)
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL){
            map->current = i;
            return map->buckets[i];
        }
    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
