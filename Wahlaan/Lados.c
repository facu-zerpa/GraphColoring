#include "Lados.h"

/** Estructura de lados entre 2 vertices**/
struct LadoSt {
    u32 x;
    u32 y;
};

Lado CrearLado(u32 x, u32 y) {
    Lado l;
    l.x = x;
    l.y = y;
    return l;
}

Lados CrearListaLados(u32 m) {
    Lados l = calloc(m, sizeof(struct LadoSt));
    return (l);
}

Lados CargarListaLados(Lados l, u32 i, u32 x, u32 y) {
    l[2*i] = CrearLado(x,y);
    l[2*i+1] = CrearLado(y,x);
    return (l);
}


/**
 * Comparador de la función dada en qsort para ordenar un arreglo
 * de lados de menor a mayor según su primera componente.
 * **/
static int Comparador(const void* a, const void* b) {
    Lado *x1 = (Lado*) a;
    Lado *x2 = (Lado*) b;
    if( x1->x < x2->x ) {
        return -1;
    } else if(x1->x > x2->x) {
        return 1;
    } else {
        return 0;
    }
}

void OrdenarLados(Lados l, u32 m) {
   qsort(l, m, sizeof(struct LadoSt), Comparador);
}

u32 ObtenerVerticeX(Lados l, u32 i) {
    return (l[i].x);
}

u32 ObtenerVerticeY(Lados l, u32 i) {
    return (l[i].y);
}
