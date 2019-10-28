#ifndef _RII_H
#define _RII_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Lados.h"

/**
 * 
 * Benjamin Ocampo. nicolasbenjaminocampo@gmail.com
 * Facundo Zerpa, facu.zerpa@gmail.com
 *
 **/

typedef struct GrafoSt *Grafo;
typedef struct VerticeSt *Vertices;
typedef struct VerticeSt Vertice;


/**
 * Lee desde stdin un Grafo con formato DIMACS
 * Aloca memora para un Grafo G, en caso de error retorna NULL
 **/
Grafo ConstruccionDelGrafo();

/**
 * Libera la memoria ocupada por el Grafo G
 **/
void DestruccionDelGrafo(Grafo G);

/**
 * Se aloca memoria para un nuevo Grafo donde se le copian
 * los datos del Grafo G.
 * En caso de no poder alocar memoria se retorna NULL.
 * En caso de G = NULL, se retorna NULL.
 **/
Grafo CopiarGrafo(Grafo G);

/**
 * Colorea G con el orden actual de los vertices
 **/
u32 Greedy(Grafo G);

/**
 *  Determina si G es bipartito o no.
 *  '1' es bipartito. '0' en caso contrario.
 **/
u32 Bipartito(Grafo G);

/**
 * Devuelve la cantidad de vertices de G
 **/
u32 NumeroDeVertices(Grafo G);

/**
 *  Devuelve la cantidad de lados de G
 **/
u32 NumeroDeLados(Grafo G);

/**
 *  Devuelve la cantidad de colores con 
 *  el cual el grafo esta coloreado 
 **/
u32 NumeroDeColores(Grafo G);

/**
 *  Devuelve el nombre del vertice i-esimo de G
 **/
u32 NombreDelVertice(Grafo G, u32 i);

/**
 *  Devuelve el color actual del vertice
 *  i-esimo de G.
 *  Si i >= nvertices, devuelve 2^32-1
 **/
u32 ColorDelVertice(Grafo G, u32 i);

/**
 *  Devuelve el grado del vertice i-esimo de G
 *  Si i >= nvertices, devuelve 2^32-1
 **/
u32 GradoDelVertice(Grafo G, u32 i);

/**
 *  Devuelve el color actual del vecino j-esimo del
 *  vertice i-esimo de G.
 *  Si i >= nvertices o j >= grado del i-esimo vertice 
 *  devuelve 2^32-1.
 **/
u32 ColorJotaesimoVecino(Grafo G, u32 i, u32 j);

/**
 *  Devuelve el nombre del vecino j-esimo del
 *  vertice i-esimo de G.
 **/
u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j);

/**
 *  Ordena los vertices en orden creciente segun su nombre real.
 *  En caso de error retorna 1.
 **/
char OrdenNatural(Grafo G);

/**
 *  Ordena los vertices de G en forma decreciente segun su grado.
 **/
char OrdenWelshPowell(Grafo G);

/**
 *  Intercambia el vertice i-esimo con el 
 *  vertice j-esimo segun el orden actual de G.
 *  Si i o j >= nvertices devuelve '1'
 **/
char SwitchVertices(Grafo G, u32 i, u32 j);

/**
 *  Ordena los vertices de G en forma creciente segun su color
 *  En caso de error retorna '1'.
 **/
char RMBCnormal(Grafo G);

/**
 *  Ordena los vertices de G en forma decreciente segun su color
 *  En caso de error retorna '1'.
 **/
char RMBCrevierte(Grafo G);

/**
 *  Ordena los vertices de G de forma creciente, segun
 *  la cantidad de vertices que tiene cada color.
 *  En caso de error retorna '1'.
 **/
char RMBCchicogrande(Grafo G);

/**
 *  Intercambia todos los vertices con el color i con 
 *  todos los vertices con el color j.
 *  Si i o j >= ncolores de G, retorna '1'
 **/
char SwitchColores(Grafo G, u32 i, u32 j);

#endif