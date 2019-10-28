#include "Rii.h"
#include "assert.h"

/*
* Ejemplo main
*/

int main() {
    Grafo G = ConstruccionDelGrafo();
    printf("Construccion realizada\n");

    printf("Orden Natural Greedy: %u\n", Greedy(G));
  
    RMBCrevierte(G);    
    printf("RMBCCrevierte Greedy: %u\n", Greedy(G));
    
    OrdenWelshPowell(G);
    printf("OrdenWelshPowell Greedy: %u\n", Greedy(G));

    DestruccionDelGrafo(G);
    printf("Destruccion del grafo\n");
    return 0;
}