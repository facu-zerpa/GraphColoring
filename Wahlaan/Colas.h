#ifndef _COLAS_H
#define _COLAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Colas *Cola;
typedef unsigned int u32;


/**
 * Aloja memoria para una cola de capacidad n
 * **/
Cola CrearCola(u32 n);

/**
 * Dada una cola, devuelve si esta vacia o no
 * **/
bool EsVacia(Cola cola);

/**
 * Agrega un elemento e al final de la cola
 * **/
void Encolar(Cola, u32 e);

/**
 * Remueve el primer elemento de la cola
 * **/
void Decolar(Cola cola);

/**
 * Devuelve el primer elemento de la cola
 * **/
u32 Primero(Cola cola);

/**
 * Libera memoria ocupada por la cola c
 * **/
void Liberar(Cola c);

/**
 * Dada una cola c, la vacía
 * **/
void VaciarCola(Cola c);

#endif