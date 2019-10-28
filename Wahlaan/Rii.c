#include "Rii.h"
#include "Colas.h"

#define MAX_NUM 4294967295  //  2^32 - 1

struct VerticeSt {
    u32 nombre;
    u32 color;
    u32 grado;
    u32 *vecinos;
};

struct GrafoSt {
    u32 n;
    u32 m;
    u32 nc;
    u32 delta;
    Vertices v;
    u32 *orden;
};
/**
 * Dado un arreglo de u32, intercambia los elementos
 * que estan en la posición 'i' y 'j'.
 * **/
static void swap(u32 a[], u32 i, u32 j){
    u32 tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

/**
 * Dado un arreglo de Vertices ordenado de manera creciente por su nombre
 * real. Devuelve la posición en donde se encuentra 'nombre' dentro del
 * arreglo. En caso de no encontrarse retorna -1.
 * **/
static u32 BusquedaBinaria(Vertices v, u32 nombre, u32 left, u32 rigth){
    if(rigth >= left){
        u32 med = (left + rigth) / 2;

        if (v[med].nombre == nombre) return med;
        if (v[med].nombre > nombre) return BusquedaBinaria(v, nombre, left, med - 1);        
        return BusquedaBinaria(v, nombre, med + 1, rigth);

    } 
    return -1;
}

/**
 * Aloca memoria para un arreglo de tamaño n de u32, donde apoda
 * a los nombres reales de los vertices.
 * Estos nombres reales son apodados por un indice i = 0,1,...,n-1
 * el cual es el orden de llegada de los vertices.
 * **/
static u32 *OrdenDeVertices(u32 n){
    u32 *orden = calloc(n, sizeof(u32));
    for (u32 i = 0; i < n; i++){
        orden[i] = i;
    }
    return orden;
}


/**
 * Retorna el delta de un arreglo de Vertices de tamaño n
 * **/
static u32 ObtenerDelta(Vertices v, u32 n){
    u32 delta = 0;
    for(u32 i = 0; i < n; i++){
        if (delta <= v[i].grado) delta = v[i].grado;
    }
    return delta;
}

/**
 * Dado n vertices, m lados, nc colores, un arreglo
 * de Vertices y un arreglo con el orden de estos de vertices
 * retorna un Grafo alocado en memoria con estos datos.
 * **/
static Grafo CargarDatosGrafo(u32 n, u32 m, u32 nc, Vertices v, u32* orden) {
    Grafo G = (Grafo)malloc(sizeof(struct GrafoSt));
    G->n = n;
    G->m = m;
    G->nc = nc;
    G->v = v;
    G->orden = orden;
    G->delta = ObtenerDelta(v, n);
    return G;
}

/**
 * Setea los colores de los vertices de un Grafo G
 * en 2^32-1.
 * **/
static void ResetearColores(Grafo G){
   u32 n = G->n;
   for(u32 i = 0; i < n; i++){
       G->v[i].color = MAX_NUM;
   }
}

/**
 * Dado un arreglo de booleanos de tamaño delta + 1 
 * que representa los colores usados por los vecinos
 * de un vertice. Retorna el minimo color que no ha
 * sido usado.
 * **/
static u32 ColorMinimo(bool *coloresusados, u32 delta){
    u32 mincolor = 0;
    u32 i = 0;
    while(i < delta + 1 && coloresusados[i] == true){
        i++;
    }
    mincolor = i;
    return mincolor;
}

/**
 * Devuelve si un vértice esta coloreado o no.
 * Un vértice no coloreado es aquel que esta
 * seteado como 2^32-1
 * **/
static bool EstaColoreado(Grafo G, u32 i){
    return G->v[i].color != MAX_NUM;
}

/**
 * Retorna un vertice con los datos los datos
 * 'nombre', 'color', 'grado', y un arreglo de vecinos.
 * **/
static Vertice CrearVertice(u32 nombre, u32 color, u32 grado, u32 *vecinos) {
    Vertice v;
    v.nombre = nombre;
    v.color = color;
    v.grado = grado;
    v.vecinos = vecinos;
    return (v);
}


/**
 * Dado un arreglo de lados de tamaño l ordenado por
 * su primer componente, y n vertices
 * retorna un arreglo de vertices 
 * 
 * Por cada vertice realiza busqueda binaria para encontrar sus
 * vecinos dentro del arreglo de lados
**/
static Vertices ListaVertices(u32 n, u32 l, Lados lados){
    Vertices vertices = calloc(n, sizeof(struct VerticeSt));
    u32 v1 = ObtenerVerticeX(lados,0);
    Vertice vertice = CrearVertice(v1, 0, 1, NULL);
    vertices[0] = vertice;
    u32 j = 1;
    for(u32 i = 1; i < l; i++) {
        u32 v2 = ObtenerVerticeX(lados, i);
        if(v1 != v2) {
            v1 = v2;
            vertices[j] = CrearVertice(v1, j, 1, NULL);
            j++;
        } else {
            vertices[j-1].grado++;
        }
    }
    if(j != n) {
        free(vertices);
        vertices = NULL;
        return vertices;
    }
    u32 s = 0;     // Indice para recorrer el arreglo de lados
    for(u32 i = 0; i < n; i++) {
        u32* vecinos = calloc(vertices[i].grado, sizeof(u32));
        u32 k = vertices[i].grado;
        for(u32 j = 0; j < k; j++) {
            vecinos[j] = BusquedaBinaria(vertices, ObtenerVerticeY(lados,s), 0, n - 1);
            s++;
        }
        vertices[i].vecinos = vecinos;
    }
    return (vertices);
}

Grafo ConstruccionDelGrafo() {
    Grafo G = NULL;
    u32 n, m, x, y, i = 0;
    Lados lados = NULL;
    Vertices vertices = NULL;
    u32 *orden = NULL;
    char c;
    while(fscanf(stdin, " %c", &c) != EOF){
        if(c == 'p'){
            fscanf(stdin, " edge %u %u", &n, &m);
            lados = CrearListaLados(2*m);
            break;
        } else if(c == 'c') {
            fscanf(stdin, "%*[^\n]\n");
        } else {
            printf("error en primera linea sin comentario\n");
            return G;
        }
    }
    while(i < m && fscanf(stdin, " %c", &c) != EOF){
        if(c == 'e'){
            fscanf(stdin, "%u %u", &x, &y);
            lados = CargarListaLados(lados,i,x,y);
            i++;
        } else {
            printf("Mal formato de entrada\n");
            free(lados);
            return G;
        }
    }
    if(i != m) {
        printf("error de lectura en lado %u + 1\n", i);
        free(lados);
        return G;
    }
    OrdenarLados(lados, 2*m);
    vertices = ListaVertices(n, 2*m, lados);
    if(vertices == NULL) {
        free(lados);
        printf("cantidad de vertices leidos no es la declarada\n");
        return G;
    }
    orden = OrdenDeVertices(n);
    free(lados);
    G = CargarDatosGrafo(n, m, n, vertices, orden);
    Greedy(G);
    return G;
}

void DestruccionDelGrafo(Grafo G){
    for(u32 i = 0; i < G->n; i++){
        free(G->v[i].vecinos);
    }
    free(G->v);
    free(G->orden);
    free(G);
}

Grafo CopiarGrafo(Grafo G){
    Grafo C = (Grafo)malloc(sizeof(struct GrafoSt));
    if (C == NULL) {
        return NULL;
    }
    
    Vertices v = calloc(G->n, sizeof(Vertice));
    if (v == NULL) {
        free(C);
        return NULL;
    }
    
    
    u32 *orden = calloc(G->n, sizeof(u32));
    if (v == NULL) {
        free(C);
        free(v);
        return NULL;
    }
    C->n = G->n;
    C->m = G->m;
    C->nc = G->nc;
    C->orden = orden;
    C->delta = G->delta;
    for(u32 i = 0; i < G->n; i++){
        u32 *vecinos = calloc(G->v[i].grado, sizeof(u32));
        if (vecinos == NULL) {
            for(u32 k = 0; k < i; k++)
            {
                free(v[k].vecinos);
            }
            free(C);
            free(v);
            free(orden);
            return NULL;
        }
        for(u32 j = 0; j < G->v[i].grado; j++){
            vecinos[j] = G->v[i].vecinos[j];
        }
        v[i].vecinos = vecinos;
        v[i].nombre = G->v[i].nombre;
        v[i].color = G->v[i].color;
        v[i].grado = G->v[i].grado;
        orden[i] = G->orden[i];
    }
    C->v = v;
    C->orden = orden;

    return C;
}

u32 Greedy(Grafo G) {
    u32 n = G->n;
    u32 grado = 0;
    u32 ncolores = 0;
    u32 mincolor = 0;
    u32 colorvecino = 0;
    u32 delta = G->delta;
    bool *tmp = calloc((delta + 1), sizeof(bool)); 
    ResetearColores(G);
    for (u32 i = 0; i < n; i++){
        grado = GradoDelVertice(G, i);
        for(u32 j = 0; j < grado; j++){
            colorvecino = ColorJotaesimoVecino(G, i, j);
            if(colorvecino != MAX_NUM){
                tmp[colorvecino] = true;
            }
        }
        mincolor = ColorMinimo(tmp, delta);
        G->v[G->orden[i]].color = mincolor;

        if (mincolor == ncolores)
            ncolores++;

        for(u32 k = 0; k < ncolores; k++){
            tmp[k] = false;
        }
    }
    G->nc = ncolores;
    free(tmp);
    return ncolores;
}

u32 Bipartito(Grafo G) {
    ResetearColores(G);
    Cola cola = CrearCola(G->n);
    for(u32 k = 0; k < G->n; k++){
        if(ColorDelVertice(G, k) == MAX_NUM){
            Encolar(cola, G->orden[k]);
            G->v[G->orden[k]].color = 0;    
            bool esBipartito = true;
            while(!EsVacia(cola)){
                u32 u = Primero(cola);
                u32 grado = G->v[u].grado;
                for(u32 j = 0; j < grado; j++){
                    u32 vecino = G->v[u].vecinos[j];
                    if(EstaColoreado(G, vecino)){
                        if(G->v[u].color == G->v[vecino].color){
                            esBipartito = false;
                            break;
                        }
                    } else {
                        Encolar(cola, vecino);
                        G->v[vecino].color = 1 - G->v[u].color;
                    }
                }
                if(!esBipartito){
                    VaciarCola(cola);
                    Liberar(cola);
                    Greedy(G);
                    return 0;
                }
                else 
                    Decolar(cola);
            }
        }
    }
    Liberar(cola);
    G->nc = 2;
    
    return 1;
}

u32 NumeroDeVertices(Grafo G){
    return G->n;
}

u32 NumeroDeLados(Grafo G){
    return G->m;
}

u32 NumeroDeColores(Grafo G){
    return G->nc;
}

u32 NombreDelVertice(Grafo G, u32 i){
    return G->v[G->orden[i]].nombre;

}

u32 ColorDelVertice(Grafo G, u32 i){
    return G->v[G->orden[i]].color;
}

u32 GradoDelVertice(Grafo G, u32 i){
    return ((i >= G->n) ? MAX_NUM : G->v[G->orden[i]].grado);
}

u32 ColorJotaesimoVecino(Grafo G, u32 i, u32 j){
    u32 grado = GradoDelVertice(G, i);
    if (i >= G->n || j >= grado) return MAX_NUM;

    u32 apodo = G->v[G->orden[i]].vecinos[j];
    return G->v[apodo].color;
}

u32 NombreJotaesimoVecino(Grafo G, u32 i, u32 j){
    u32 apodo = G->v[G->orden[i]].vecinos[j];
    return G->v[apodo].nombre;
}

/** ORDEN NATURAL **/
char OrdenNatural(Grafo G){
    if(G == NULL)
        return 1;
    for(u32 i = 0; i < G->n; i++){
        G->orden[i] = i;
    }
    return 0;
}

/** ORDEN WELSHPOWELL **/
static void merge_WelshPowell(u32 a[], u32 left, u32 med, u32 right, Grafo G) {
    u32* tmp = (u32*)malloc(G->n*sizeof(u32));
    u32 i, j, k;
    for (i = left; i <= med; i++) {
        tmp[i] = a[i];
    }
    j = left;
    k = med + 1;
    for (i = left; i <= right; i++) {
        if (j <= med && (k > right || G->v[tmp[j]].grado >= G->v[a[k]].grado)) {
            a[i] = tmp[j];
            j++;
        } else {
            a[i] = a[k];
            k = k + 1;
        }
    }
    free(tmp);
}

static void merge_sort_rec_WelshPowell(Grafo G, u32 a[], u32 left, u32 right) {
    u32 med;
    if (right > left) {
        med = (left + right)/2;
        merge_sort_rec_WelshPowell(G, a, left, med);
        merge_sort_rec_WelshPowell(G, a, med + 1, right);
        merge_WelshPowell(a, left, med, right, G);
    }
}

/**
 * Ordena el arreglo 'a' de acuerdo al grado de los vertices
 * del Grafo G  en orden decreciente.
 **/
static void merge_sort_WelshPowell(Grafo G, u32 a[], u32 length) {
    merge_sort_rec_WelshPowell(G, a, 0, (length == 0) ? 0 : length - 1);
}

char OrdenWelshPowell(Grafo G){
    if(G == NULL)
        return 1;
    merge_sort_WelshPowell(G, G->orden, G->n);
    return 0;
}

/** SWITCH VERTICES **/
char SwitchVertices(Grafo G, u32 i, u32 j) {
    if(i >= NumeroDeVertices(G) || j >= NumeroDeVertices(G) ) return 1;
    swap(G->orden, i, j);
    return 0;
}

/** RMBCnormal **/
static void merge_RMBCnormal(u32 a[], u32 left, u32 med, u32 right, Grafo G) {
    u32* tmp = (u32*)malloc(G->n*sizeof(u32));
    u32 i, j, k;
    for (i = left; i <= med; i++) {
        tmp[i] = a[i];
    }
    j = left;
    k = med + 1;
    for (i = left; i <= right; i++) {
        if (j <= med && (k > right || G->v[tmp[j]].color <= G->v[a[k]].color)) {
            a[i] = tmp[j];
            j++;
        } else {
            a[i] = a[k];
            k = k + 1;
        }
    }
    free(tmp);
}

static void merge_sort_rec_RMBCnormal(Grafo G, u32 a[], u32 left, u32 right) {
    u32 med;
    if (right > left) {
        med = (left + right)/2;
        merge_sort_rec_RMBCnormal(G, a, left, med);
        merge_sort_rec_RMBCnormal(G, a, med + 1, right);
        merge_RMBCnormal(a, left, med, right, G);
    }
}

/**
 * Ordena el arreglo 'a' de acuerdo al color de los vertices
 * del Grafo G  en orden creciente.
 **/
static void merge_sort_RMBCnormal(Grafo G, u32 a[], u32 length) {
    merge_sort_rec_RMBCnormal(G, a, 0, (length == 0) ? 0 : length - 1);
}

char RMBCnormal(Grafo G) {
    if(G == NULL)
        return 1;
    merge_sort_RMBCnormal(G, G->orden, G->n);
    return 0;
}

/** RMBCrevierte **/
static void merge_RMBCrevierte(u32 a[], u32 left, u32 med, u32 right, Grafo G) {
    u32* tmp = (u32*)malloc(G->n*sizeof(u32));
    u32 i, j, k;
    for (i = left; i <= med; i++) {
        tmp[i] = a[i];
    }
    j = left;
    k = med + 1;
    for (i = left; i <= right; i++) {
        if (j <= med && (k > right || G->v[tmp[j]].color >= G->v[a[k]].color)) {
            a[i] = tmp[j];
            j++;
        } else {
            a[i] = a[k];
            k = k + 1;
        }
    }
    free(tmp);
}

static void merge_sort_rec_RMBCrevierte(Grafo G, u32 a[], u32 left, u32 right) {
    u32 med;
    if (right > left) {
        med = (left + right)/2;
        merge_sort_rec_RMBCrevierte(G, a, left, med);
        merge_sort_rec_RMBCrevierte(G, a, med + 1, right);
        merge_RMBCrevierte(a, left, med, right, G);
    }
}

/**
 * Ordena el arreglo 'a' de acuerdo al color de los vertices
 * del Grafo G  en orden decreciente.
 **/
static void merge_sort_RMBCrevierte(Grafo G, u32 a[], u32 length) {
    merge_sort_rec_RMBCrevierte(G, a, 0, (length == 0) ? 0 : length - 1);
}

char RMBCrevierte(Grafo G) {
    if(G == NULL)
        return 1;
    merge_sort_RMBCrevierte(G, G->orden, G->n);
    return 0;
}

/** RMBCchicogrande **/
static void merge_RMBCchicogrande(u32 a[], u32 left, u32 med, u32 right, Grafo G, u32 *vc) {
    u32* tmp = (u32*)malloc(G->n*sizeof(u32));
    u32 i, j, k;
    for (i = left; i <= med; i++) {
        tmp[i] = a[i];
    }
    j = left;
    k = med + 1;
    for (i = left; i <= right; i++) {
        if (j <= med && (k > right || vc[G->v[tmp[j]].color] <= vc[G->v[a[k]].color])) {
            a[i] = tmp[j];
            j++;
        } else {
            a[i] = a[k];
            k = k + 1;
        }
    }
    free(tmp);
}

static void merge_sort_rec_RMBCchicogrande(Grafo G, u32 a[], u32 left, u32 right, u32 *vc) {
    u32 med;
    if (right > left) {
        med = (left + right)/2;
        merge_sort_rec_RMBCchicogrande(G, a, left, med, vc);
        merge_sort_rec_RMBCchicogrande(G, a, med + 1, right, vc);
        merge_RMBCchicogrande(a, left, med, right, G, vc);
    }
}
static void merge_sort_RMBCchicogrande(Grafo G, u32 a[], u32 length, u32 *vc) {
    merge_sort_rec_RMBCchicogrande(G, a, 0, (length == 0) ? 0 : length - 1, vc);
}

char RMBCchicogrande(Grafo G) {
    if(G == NULL) return 1;
    RMBCnormal(G);
    u32* vc = calloc(G->nc,sizeof(u32));
    if(vc == NULL) return 1;
    for(u32 i = 0; i < G->n; i++) {
        u32 c = ColorDelVertice(G,i);
        vc[c] = vc[c] + 1;
    }
    merge_sort_RMBCchicogrande(G, G->orden, G->n, vc);
    free(vc);
    return 0;
}

/** SWITCHCOLORES **/
char SwitchColores(Grafo G, u32 i, u32 j) {
    if(i > G->nc || j > G->nc) return 1;
    for(u32 k = 0; k < G->n; k++) {
        if(ColorDelVertice(G, k) == i) G->v[G->orden[k]].color = j;
        else if (ColorDelVertice(G, k) == j) G->v[G->orden[k]].color = i; 
    }
    return 0;

}