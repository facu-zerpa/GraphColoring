#include "Colas.h"

struct Colas {
    u32 prim;
    u32 n;
    u32 c;
    u32* elem;
};

Cola CrearCola(u32 n) {
    Cola cola = (Cola) malloc(sizeof(struct Colas));
    cola->prim = 0;
    cola->n = 0;
    cola->c = n;
    cola->elem = calloc(n, sizeof(unsigned int));
    return cola;
}

bool EsVacia(Cola c) {
    return (c->n == 0);
}

void Encolar(Cola c, u32 e) {
    c->elem[(c->prim + c->n) % c->c] = e;
    c->n = c->n + 1;
}

void Decolar(Cola c) {
    c->n = c->n - 1;
    c->prim = (c->prim + 1) % c->c;
}

u32 Primero(Cola c) {
    return c->elem[c->prim];
}

void Liberar(Cola c) {
    for(u32 i = 0; i < c->c; i++)
    {
        free(c->elem);
        c->elem = NULL;
    }
    free(c);
}

void VaciarCola(Cola c){
    c->n = 0;
}