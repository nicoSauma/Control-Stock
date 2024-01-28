#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <strings.h>

nodoL* iniclista(){

    return NULL;
}

nodoL* crearnodo(sector dato){
    nodoL* nuevo=(nodoL*)malloc(sizeof(nodoL));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;
    return nuevo;
}

nodoL* agregaralprincipio(nodoL* lista, nodoL* nuevo)
{
    if(lista==NULL){
        lista=nuevo;
    }
    else{
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;
}

nodoL* buscar_ultimo (nodoL*lista){
nodoL*seg=lista;
while(seg->siguiente!=NULL){
    seg=seg->siguiente;
}
return seg;
}

nodoL* agregarAlFinal(nodoL* lista, nodoL*nuevo){
if(lista==NULL){
    lista=nuevo;
}
else {
    nodoL* ultimo=buscar_ultimo(lista);
    ultimo->siguiente=nuevo;
}
return lista;
}


void mostrar_lista (nodoL* lista){
   nodoL *seguidora=lista;
while(seguidora!=NULL) {
    escribir(seguidora);
    seguidora=seguidora->siguiente;
}
}

void escribir(nodoL*aux){

printf("%s ", aux->dato.nombreSector);
printf("%i", aux->dato.idSector);
}

nodoL* borrarPrimerNodo (nodoL*lista){
nodoL*aux;

if (lista!=NULL){
    aux=lista;
    lista=lista->siguiente;
    free(aux);
    }

return lista;
}

nodoL* retornarprimernodo (nodoL*lista){
nodoL* rta=lista;

if (lista==NULL){
    printf("\n La lista esta vacia");
}

else {
    rta=lista;
}
return rta;
}

nodoLP*iniclistaLP()
{
    return NULL;
}
nodoLP* crearnodolp(proveedor dato){
    nodoLP* nuevo=(nodoLP*)malloc(sizeof(nodoLP));
    nuevo->dato=dato;
    nuevo->siguiente=NULL;
    return nuevo;
}

void mostrar_listaprov(nodoLP* lista)

{
   nodoLP *seguidora=lista;
while(seguidora!=NULL) {
        if(seguidora->dato.estadoprovedor == 1)
        {
            escribirprovlista(seguidora);
        }
        seguidora=seguidora->siguiente;
}
}

void escribirprovlista(nodoLP*aux){
printf("\n--------------------------\n");
printf("El nombre del proveedor es:%s\n",aux->dato.nombreprov);
printf("El numero del proveedor es:%i\n", aux->dato.numerocontacto);
printf("La direccion del proovedor es:%s\n",aux->dato.direccion);
printf("Tipo de producto del proveedor:%s\n",aux->dato.tipoproducto);

printf("\n--------------------------\n");
}


nodoLP* agregaralprincipioLP(nodoLP* lista, nodoLP* nuevo)
{
    if(lista==NULL){
        lista=nuevo;
    }
    else{
        nuevo->siguiente=lista;
        lista=nuevo;
    }
    return lista;
}



nodoLP * agregarEnOrdenNombreAscendente(nodoLP* lista, nodoLP* nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if(strcmpi(nuevoNodo->dato.nombreprov , lista->dato.nombreprov)<0)
        {
            lista=agregaralprincipioLP(lista, nuevoNodo);
        }
        else
        {
            nodoLP*anterior=lista;
            nodoLP*seguidora=lista->siguiente;

            while((seguidora!=NULL)&& (strcmpi(nuevoNodo->dato.nombreprov , seguidora->dato.nombreprov)>=0))
            {
                anterior=seguidora;
                seguidora=seguidora->siguiente;
            }

            nuevoNodo->siguiente=seguidora;
            anterior->siguiente=nuevoNodo;
        }
    }
   return lista;
}


nodoLP * agregarEnOrdenNombreDescendente(nodoLP* lista, nodoLP* nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        if(strcmpi(nuevoNodo->dato.nombreprov , lista->dato.nombreprov)> 0)
        {
            lista=agregaralprincipioLP(lista, nuevoNodo);
        }
        else
        {
            nodoLP*anterior=lista;
            nodoLP*seguidora=lista->siguiente;
            while((seguidora!=NULL)&& (strcmpi(nuevoNodo->dato.nombreprov , seguidora->dato.nombreprov)<0))
            {
                anterior=seguidora;
                seguidora=seguidora->siguiente;
            }

            nuevoNodo->siguiente=seguidora;
            anterior->siguiente=nuevoNodo;
        }
    }
return lista;
}


nodoLP* agregarEnOrdenTipoProductoAscendente(nodoLP* lista, nodoLP* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if(strcmpi(nuevoNodo->dato.tipoproducto, lista->dato.tipoproducto) < 0)
        {
            lista = agregaralprincipioLP(lista, nuevoNodo);
        }
        else
        {
            nodoLP* anterior = lista;
            nodoLP* seguidora = lista->siguiente;

            while((seguidora != NULL) && (strcmpi(nuevoNodo->dato.tipoproducto, seguidora->dato.tipoproducto) >= 0))
            {
                anterior = seguidora;
                seguidora = seguidora->siguiente;
            }

            nuevoNodo->siguiente = seguidora;
            anterior->siguiente = nuevoNodo;
        }
    }
    return lista;
}


nodoLP* agregarEnOrdenTipoProductoDescendente(nodoLP* lista, nodoLP* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if(strcmpi(nuevoNodo->dato.tipoproducto, lista->dato.tipoproducto) > 0)
        {
            lista = agregaralprincipioLP(lista, nuevoNodo);
        }
        else
        {
            nodoLP* anterior = lista;
            nodoLP* seguidora = lista->siguiente;

            while((seguidora != NULL) && (strcmpi(nuevoNodo->dato.tipoproducto, seguidora->dato.tipoproducto) < 0))
            {
                anterior = seguidora;
                seguidora = seguidora->siguiente;
            }

            nuevoNodo->siguiente = seguidora;
            anterior->siguiente = nuevoNodo;
        }
    }
    return lista;
}





