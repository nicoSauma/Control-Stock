#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct{
int idProducto;
char nombreProducto[30];
int cantidadProducto;
int precio;
}producto;

typedef struct nodoA{
producto dato;
struct nodoA* der;
struct nodoA* izq;
}nodoA;

void mostrarPersona(producto pro);

nodoA* inicArbol();

nodoA* crearNodoArbol(producto dato);

nodoA* insertar (nodoA* arbol, nodoA*nuevo);

nodoA* buscar (nodoA* arbol, producto dato);

nodoA* buscarporProductoID (nodoA* arbol, int idproducto);

nodoA* busquedaNombre(nodoA* arbol, char buscado[]);

void preorder (nodoA* arbol);

void inorden (nodoA* arbol);

void postorden (nodoA* arbol);

nodoA* nodoMasIzquierda(nodoA* arbol);

nodoA* nodoMasDerecha(nodoA* arbol);

int esHoja(nodoA * arbol);

int esGrado1(nodoA * arbol);

nodoA* borrarTodoArbol(nodoA* arbol);

nodoA* borrarNodoArbolBis(nodoA* arbol, int idProducto);

#endif // ARBOLES_H_INCLUDED

