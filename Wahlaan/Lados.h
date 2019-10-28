#ifndef _LADOS_H
#define _LADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;
typedef struct LadoSt *Lados;
typedef struct LadoSt Lado;

/** Crea un lado dados dos vertices x e y **/
Lado CrearLado(u32 x, u32 y);

/** Crea una lista de lados de longitud m**/
Lados CrearListaLados(u32 m);

/** 
 * Dados dos vertices x e y, carga los lados (x, y)
 * e (y, x) dentro de un arreglo L en sus posiciones
 * i e (i + 1).
 * **/ 
Lados CargarListaLados(Lados l, u32 i, u32 x, u32 y);

/**
 * Dado un arreglo L de lados, devuelve la primera componente
 * de la tupla i-esima
 * **/
u32 ObtenerVerticeX(Lados l, u32 i);

/**
 * Dado un arreglo L de lados, devuelve la segunda componente
 * de la tupla i-esima
 * **/
u32 ObtenerVerticeY(Lados l, u32 i);

/**
 * Ordena un arreglo de lados L, de menor a mayor según
 * su primera componente 
 * **/
void OrdenarLados(Lados l, u32 m);

#endif
