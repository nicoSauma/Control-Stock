#include "arboles.h"


void mostrarPersona(producto pro)
{

    printf("\nID producto: %i", pro.idProducto);
    printf("\nNombre producto: %s", pro.nombreProducto);
    printf("\nCantidad: %i", pro.cantidadProducto);
    printf("\nPrecio: %i", pro.precio);
    printf("\n");

}

nodoA* inicArbol()
{
    return NULL;
}

nodoA* crearNodoArbol(producto dato)
{
    nodoA* nuevo= (nodoA*) malloc(sizeof(nodoA));

    nuevo->dato=dato;
    nuevo->der=NULL;
    nuevo->izq=NULL;

    return nuevo;
}

nodoA* insertar (nodoA* arbol, nodoA *nuevo)
{

    if (arbol==NULL)
    {
        arbol=nuevo;
    }

    else
    {
        if(nuevo->dato.cantidadProducto>arbol->dato.cantidadProducto)
        {
            arbol->der=insertar(arbol->der,nuevo);
        }
        else
        {
            arbol->izq=insertar(arbol->izq,nuevo);
        }

    }
    return arbol;
}

nodoA* buscar (nodoA* arbol, producto dato)
{
    nodoA* rta=NULL;

    if (arbol!=NULL)
    {
        if(dato.idProducto==arbol->dato.idProducto)
        {
            rta=arbol;
        }
        else
        {
            if(dato.idProducto>arbol->dato.idProducto)
            {
                rta=buscar(arbol->der,dato);
            }
            else
            {
                rta=buscar(arbol->izq,dato);
            }

        }

    }
    return rta;
}

nodoA* buscarporProductoID (nodoA* arbol, int idproducto)
{
    nodoA* rta=NULL;

    if (arbol!=NULL)
    {
        if(idproducto==arbol->dato.idProducto)
        {
            rta=arbol;
        }
        else
        {
            if(idproducto>arbol->dato.idProducto)
            {
                rta=buscarporProductoID(arbol->der,idproducto);
            }
            else
            {
                rta=buscarporProductoID(arbol->izq,idproducto);
            }

        }

    }
    return rta;
}


nodoA* busquedaNombre(nodoA* arbol, char buscado[])
{
    nodoA* rta=NULL;

    if (arbol!=NULL)
    {
        if(strcmpi(buscado,arbol->dato.nombreProducto)==0)
        {
            rta=arbol;
        }
        else
        {

            rta=busquedaNombre(arbol->izq,buscado);
            if (rta==NULL)
            {
                rta=busquedaNombre(arbol->der,buscado);
            }
        }

    }
    return rta;
}

void preorder (nodoA* arbol)
{
    if(arbol!=NULL)
    {
        mostrarPersona(arbol->dato);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorden (nodoA* arbol)
{
    if(arbol!=NULL)
    {
        inorden(arbol->izq);
        mostrarPersona(arbol->dato);
        inorden(arbol->der);
    }
}

void postorden (nodoA* arbol)
{
    if(arbol!=NULL)
    {
        postorden(arbol->izq);
        postorden(arbol->der);
        mostrarPersona(arbol->dato);
    }
}

nodoA* nodoMasIzquierda(nodoA* arbol)
{
    if(arbol)
    {
        if(arbol->izq != NULL)
        {
            arbol = nodoMasIzquierda(arbol->izq);
        }
    }
    return arbol;//si el arbol esta vacio retorna NULL
}


nodoA* nodoMasDerecha(nodoA* arbol)
{
    if(arbol)
    {
        if(arbol->der != NULL)
        {
            arbol = nodoMasDerecha(arbol->der);
        }
    }
    return arbol;
}


int esHoja(nodoA * arbol)
{
    int rta=0;

    if(arbol)
    {
        if(arbol->izq==NULL && arbol->der==NULL)
        {
            rta=1;
        }
    }
    return rta;
}

int esGrado1(nodoA * arbol)
{
    int rta=0;

    if(arbol)
    {
        if( (arbol->izq==NULL && arbol->der!=NULL) || (arbol->izq!=NULL && arbol->der==NULL) )
        {
            rta=1;
        }
    }
    return rta;
}

nodoA* borrarTodoArbol(nodoA* arbol)
{
    if(arbol)
    {
        if(esHoja(arbol))
        {
            nodoA* aux = arbol;
            free(aux);
            arbol = NULL;//como la otra vuelta recursiva espera a un arbol, si solo lo libero estaria rompiedo la funcion. POr eso debo devolver un NULL
        }
        else
        {
            arbol->izq = borrarTodoArbol(arbol->izq);
            arbol->der = borrarTodoArbol(arbol->der);

            if(esHoja(arbol)) //tengo que comparar una vez mas, ya que a la vuelta de la ultima iteracion recursiva, quedara la raiz sola, convirtiendose en una hoja
            {
                nodoA* aux = arbol;
                free(aux);
                arbol = NULL;
            }
        }
    }
    return arbol;
}

nodoA* borrarNodoArbolBis(nodoA* arbol, int idProducto){
    if(arbol!=NULL){ // cond corte y sol triv implicita: no hace nada y retorna arbol, que va a ser NULL)
        if(idProducto > arbol->dato.idProducto){
            arbol->der = borrarNodoArbolBis(arbol->der, idProducto); // si el dato buscado es mayor, busca por la dcha
        }
        else if (idProducto < arbol->dato.idProducto){
            arbol->izq = borrarNodoArbolBis(arbol->izq, idProducto); //si el dato buscado es menor, busca por la izq
        }
        else if (idProducto == arbol->dato.idProducto){  // si lo encontró (si no es < ni > ni llego al final es pq lo encontró)
            if(esHoja(arbol)){
                free(arbol);// puede ser q la hoja a borrar fuera el nodo q buscaba originariamente, o q fuera el nodo que "subi" y ahora necesito borrarlo para q no quede duplicado
                arbol = NULL; //como estamos en funcion recursiva, el otro llamado espera 1 nodo y si solo hago el free habra error
            }else if(esGrado1(arbol)){
                nodoA* aux;
                if (arbol->der){   /// si los hijos son del lado izquierdo
                    aux = arbol;
                    arbol = arbol->der;
                    free(aux);
                }
                else{             /// si los hijos son del lado derecho
                    aux = arbol;
                    arbol = arbol->izq;
                    free(aux);
                }
            }else{             /// tiene 2 hijos
                nodoA* masDer = nodoMasDerecha(arbol->izq);
                arbol->dato = masDer->dato;  //al nodo a borrar le asigno como nuevo dato el del nodo mas derecho de la rama izquierda (el mas grande de los menores)
                arbol->izq = borrarNodoArbolBis(arbol->izq, arbol->dato.idProducto); //y ahora busco y borro del lado izq el nodo que "subí"
            }
        }
    }
    return arbol;
}
