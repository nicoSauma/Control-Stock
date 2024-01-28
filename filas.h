#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "lista.h"
#include "archivoAndLDA.h"

#ifndef FILAS_H_INCLUDED
#define FILAS_H_INCLUDED

typedef struct{
char usuario[100];
int idUsurario;
char productoComp [100];
int cantidad;
int valor;
}comprador;


typedef struct nodo
{
    comprador dato;
    struct nodo * sig;
    struct nodo * ante;
}nodo;


typedef struct
{
    nodo dato;
    nodo * inicio;
    nodo * fin;
}Fila;


nodo *inicLista();
nodo *creaNodo(comprador dato);
nodo *agregaAlFinal (nodo *ult, nodo *nuevo);
nodo * borraPrimerNodo(nodo * lista);
comprador retornaPrimerDato(nodo * lista);
void mostrarComprador (comprador aux);
void muestraLista(nodo *lista);

void inicFila(Fila * fila);
void agregar(Fila * fila, comprador dato);
void leer(Fila * fila, nodoL*lista);
comprador extraer(Fila * fila);
void muestraFila(Fila * fila);
int filaVacia(Fila * fila);
nodoL* restarstock(nodoL*lista, char nombrepro[] , int cantidad);

comprador extraerUltimo(Fila *fila);

#endif // FILAS_H_INCLUDED
