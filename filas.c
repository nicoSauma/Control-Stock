#include "filas.h"
#include <strings.h>
#include "lista.h"
#include "arboles.h"

///FUNCIONES DE FILAS CON LISTAS DOBLES
void inicFila(Fila * fila)
{
    fila->inicio= inicLista();
    fila->fin= inicLista();
}

void agregar(Fila * fila, comprador dato)
{
    nodo * nuevo = creaNodo(dato);

    if(fila->inicio == NULL)
    {
        fila->inicio = nuevo;

    }
    else
    {
        fila->fin = agregaAlFinal(fila->fin, nuevo);
    }
    fila->fin = nuevo;
}

void leer(Fila *fila, nodoL *lista)
{
    nodoA *buscado;

    nodoL *seg = lista;
    int flag = 0;
    int aux = 0;
    int valortotal = 0;
    char continuar = 's';

    while (continuar == 's')
    {
        comprador dato;

        printf("\nIngrese nombre de la persona a atender: ");
        fflush(stdin);
        gets(dato.usuario);

        printf("Ingrese el ID del usuario: ");
        fflush(stdin);
        scanf("%i", &dato.idUsurario);

        do
        {
        printf("Ingrese el producto a comprar: ");
        fflush(stdin);
        gets(dato.productoComp);

        aux = buscarNombreEnArchivoDeSectores(dato.productoComp);
        if (aux == 0)
        {
            printf("\nEl producto no existe.Ingrese nuevamente el nombre del producto\n");
        }

        }while (aux == 0);


        while ((flag == 0) && (seg != NULL))
        {
            buscado = busquedaNombre(seg->arbolProductos, dato.productoComp);

            if (buscado != NULL)
            {
                if (strcmpi(buscado->dato.nombreProducto, dato.productoComp) == 0)
                {
                    flag = 1;
                }
            }
            else
            {
                seg = seg->siguiente;
            }
        }

        if (buscado != NULL)
        {
            printf("Ingrese la cantidad de los productos comprados: ");
            fflush(stdin);
            scanf("%i", &dato.cantidad);

            if (seg->arbolProductos->dato.cantidadProducto >= dato.cantidad)
            {
                dato.valor = buscado->dato.precio;
                dato.valor = dato.valor * dato.cantidad;
                valortotal = valortotal + dato.valor;
                agregar(fila, dato);

                buscado->dato.cantidadProducto= buscado->dato.cantidadProducto - dato.cantidad;
                actualizararchivoresta(buscado->dato.idProducto, dato.cantidad);
                printf("Se han restado %d productos del stock del producto %s.\n", dato.cantidad, dato.productoComp);



            }
            else
            {
                printf("Sobrepasa la cantidad de stock.\n");
            }
        }
        else
        {
            printf("El producto no fue encontrado.\n");
        }

        printf("Ingrese letra S si desea seguir cargando productos: ");
        fflush(stdin);
        scanf(" %c", &continuar);


    }

    printf("El total de la compra es: %i\n", valortotal);
}




comprador extraer(Fila * fila) //desapilar
{
    comprador rta;
    rta.cantidad = -1;

    if(fila->inicio != NULL)
    {
        rta = retornaPrimerDato(fila->inicio);
        fila->inicio = borraPrimerNodo(fila->inicio);

        if(fila->inicio == NULL)
        {
            fila->fin= NULL;
        }
    }
    return rta;
}

void muestraFila(Fila * fila)
{
    muestraLista(fila->inicio);
}

int filaVacia(Fila * fila)
{
    int flag= 0;
    if(fila->inicio!=NULL)
    {
        flag = 1;
    }
    return flag;
}


nodo *inicLista()
{
    return NULL;
}

nodo *creaNodo(comprador dato)
{
    nodo * nuevo = (nodo*)malloc(sizeof(nodo));

    nuevo->dato = dato;

    nuevo->sig  = NULL;
    nuevo->ante = NULL;

    return nuevo;
}


nodo *agregaAlFinal (nodo *ult, nodo *nuevo)  ///En una fila agregamos al final, ese es su comportamiento
{
    if(ult == NULL) /// Si la lista esta vacia
    {
        ult = nuevo;
    }
    else
    {
        ult->sig = nuevo;
        nuevo->ante = ult;
    }
    return ult;
}

nodo * borraPrimerNodo(nodo * lista)
{
    if(lista!=NULL)
    {
        nodo * aBorrar = lista;
        lista = lista->sig;
        if(lista!=NULL)
        {
            lista->ante= NULL;
        }
        free(aBorrar);
    }
    return lista;
}

comprador retornaPrimerDato(nodo * lista)
{
    comprador rta;
    rta.cantidad = -1;
    if(lista!= NULL)
    {
        rta = lista->dato;
    }
    else
    {
        printf("\nLa lista esta vacia.");
    }
    return rta;
}

void muestraLista(nodo *lista)
{
    nodo * seg = lista;
    while(seg!=NULL)
    {
        mostrarComprador(seg->dato);
        seg= seg->sig;
    }
}

void mostrarComprador (comprador aux)
{
    printf("\nNombre del comprador: %s ", aux.usuario);
    //puts(aux.usuario);

    printf("\nID del usuario: %i ", aux.idUsurario);
    //puts(aux.idUsurario);

    printf("\nProducto comprado: %s ",  aux.productoComp);

    printf("\nCantidad comprada: %i ", aux.cantidad);

    printf("\nValor del producto: %i ", aux.valor);

    printf("\n----------------------------------\n");
}

nodoL* restarstock(nodoL*lista, char nombrepro[], int cantidad)
{

    nodoA* buscado = busquedaNombre(lista->arbolProductos, nombrepro);

    if (buscado != NULL)
    {

        if (buscado->dato.cantidadProducto >= cantidad)
        {
            buscado->dato.cantidadProducto= buscado->dato.cantidadProducto - cantidad;

            printf("Se han restado %d productos del stock del producto %s.\n", cantidad, nombrepro);
        }
        else
        {
            printf("No hay suficientes productos en stock para la compra.\n");
        }
    }
    else
    {
        printf("El producto con nombre %s no fue encontrado.\n", nombrepro);
    }

    return lista;
}


