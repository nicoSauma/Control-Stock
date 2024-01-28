#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "arboles.h"

typedef struct {
int idSector;
char nombreSector[30];
int estadosector;
}sector;

typedef struct nodoL{
sector dato;
nodoA* arbolProductos;
struct nodoL* siguiente;
}nodoL;

typedef struct {
 char nombreprov[20];
    int numerocontacto;
    char direccion[20];
    char tipoproducto[30];
     int estadoprovedor;
}proveedor;

typedef struct nodoLP{
proveedor dato;
struct nodoLP* siguiente;
}nodoLP;

nodoL* iniclista();

nodoL* crearnodo(sector dato);

nodoL* agregaralprincipio(nodoL* lista, nodoL* nuevo);

nodoL* buscar_ultimo (nodoL*lista);

nodoL* agregarAlFinal(nodoL* lista, nodoL*nuevo);

void mostrar_lista (nodoL* lista);

void escribir(nodoL*aux);

nodoL* borrarPrimerNodo (nodoL*lista);

nodoL* retornarprimernodo (nodoL*lista);

nodoLP*iniclistaLP();

void escribirprovlista(nodoLP*aux);

void mostrar_listaprov (nodoLP* lista);

nodoLP* crearnodolp(proveedor dato);

nodoLP* agregaralprincipioLP(nodoLP* lista, nodoLP* nuevo);

#endif // LISTA_H_INCLUDED
