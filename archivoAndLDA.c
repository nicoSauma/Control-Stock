#include "archivoAndLDA.h"
#include <strings.h>
#include "lista.h"
#include "arboles.h"


registroarchivo cargaUnProducto (registroarchivo aux)
{

    printf("\nIngrese nombre del sector: ");
    fflush(stdin);
    gets(aux.nombreSector);

    printf("\nIngrese id del sector: ");
    fflush(stdin);
    scanf("%i",&aux.idSector);

    aux.estadosector=1;

    printf("\nIngrese id del producto: ");
    fflush(stdin);
    scanf("%i",&aux.idProducto);

    printf("\nIngrese nombre del producto: ");
    fflush(stdin);
    gets(aux.nombreProducto);

    printf("\nIngrese cantidad del producto: ");
    fflush(stdin);
    scanf("%i",&aux.cantidadProducto);

    printf("\nIngrese precio del producto: ");
    fflush(stdin);
    scanf("%i",&aux.precio);


    return aux;
}

void muestraUnProducto (registroarchivo aux)
{
    printf("\n--------------------------------\n");
    printf("\nID producto: %i\n", aux.idProducto);
    printf("\nProducto: %s\n", aux.nombreProducto);
    printf("\nCantidad: %i\n", aux.cantidadProducto);
    printf("\nPrecio: %i\n", aux.precio);
    printf("\nID sector: %i\n", aux.idSector);
    printf("\nSector: %s\n", aux.nombreSector);
    printf("--------------------------------\n");
}

void cargaArchivo (char archivo[])
{
    registroarchivo aux;
    char continuar='s';
    FILE* archi=fopen(archivo, "ab");
    if(archi!=NULL)
    {
        while(continuar=='s')
        {
            aux=cargaUnProducto(aux);
            fwrite(&aux,sizeof(registroarchivo),1,archi);

            printf("Si desea continuar presione S ");
            fflush(stdin);
            scanf("%c", &continuar);
        }
        fclose(archi);
    }
}

void muestraArchivo (char archivo[])
{
    registroarchivo aux;

    FILE* archi=fopen(archivo, "rb");

    if (archi!=NULL)
    {
        while(fread(&aux,sizeof(registroarchivo),1,archi)>0)
        {
            muestraUnProducto(aux);
        }
        fclose(archi);
    }
}

proveedor cargaunproveedor(proveedor aux)
{
    int flag = 0; /// 1 es encontrado
    do
    {
        printf("Ingrese el nombre del proveedor: ");
        fflush(stdin);
        gets(aux.nombreprov);

        flag = buscarNombreEnArchivo(aux.nombreprov);

        if (flag == 1)
        {
            printf("El nombre ya existe en el archivo. Ingrese otro nombre.\n");
        }
    }
    while (flag == 1);

    printf("\nIngrese el numero de contacto del proveedor: ");
    fflush(stdin);
    scanf("%i", &aux.numerocontacto);

    printf("\nIngrese direccion del proveedor: ");
    fflush(stdin);
    gets(aux.direccion);

    printf("\nIngrese tipo de producto del proveedor: ");
    fflush(stdin);
    gets(aux.tipoproducto);

    aux.estadoprovedor = 1;

    return aux;

}


int buscarNombreEnArchivo(char nombre [])
{
    FILE* buffer = fopen(archivoprov, "rb");
    registroarchivoprov aux;
    int flag = 0;

    if (buffer)
    {

        while ((flag == 0) && fread(&aux, sizeof(registroarchivoprov), 1, buffer) >0 )
        {
            if (strcmpi(aux.nombreprov, nombre)==0)
            {
                flag = 1;
            }
        }

        fclose(buffer);
    }

    return flag;
}

int buscarNombreEnArchivoDeSectores(char nombre [])
{
    FILE* buffer = fopen(archivogeneral, "rb");
    registroarchivo aux;
    int flag = 0;

    if (buffer)
    {

        while ((flag == 0) && fread(&aux, sizeof(registroarchivo), 1, buffer) >0 )
        {
            if (strcmpi(aux.nombreProducto, nombre)==0)
            {
                flag = 1;
            }
        }

        fclose(buffer);
    }

    return flag;
}


proveedor cargaunproveedormanual()
{
    proveedor aux;
    printf("Ingrese el nombre del proveedor: ");
    fflush(stdin);
    gets(aux.nombreprov);

    printf("\nIngrese el numero de contacto del proveedor: ");
    fflush(stdin);
    scanf("%i", &aux.numerocontacto);

    printf("\nIngrese direccion del proveedor: ");
    fflush(stdin);
    gets(aux.direccion);

    printf("\nIngrese tipo de producto del proveedor: ");
    fflush(stdin);
    gets(aux.tipoproducto);

    /*printf("\nIngrese estado del provedor: ");
    fflush(stdin);
    scanf("%i",&aux.estadoprovedor);*/
    aux.estadoprovedor = 1;

    return aux;

}

void cargaArchivoprov (char archivo[])
{
    proveedor aux;
    char continuar='s';
    FILE* archi=fopen(archivo, "ab");
    if(archi!=NULL)
    {
        while(continuar=='s')
        {
            aux=cargaunproveedor(aux);
            fwrite(&aux,sizeof(proveedor),1,archi);

            printf("\nSi desea continuar presione 's' ");
            fflush(stdin);
            scanf("%c", &continuar);
        }
        fclose(archi);
    }
}

void muestraproveedor(proveedor aux)
{
    printf ("\n--------------------------------\n");
    printf("El nombre del proveedor es:%s\n",aux.nombreprov);
    printf("El numero de contacto del proveedor es:%d\n",aux.numerocontacto);
    printf("La direccion del proveedor es:%s\n",aux.direccion);
    printf("El tipo de producto que distribuye es:%s\n",aux.tipoproducto);
    printf ("\n--------------------------------\n");
}

void muestraArchivoprov (char archivo[])
{
    proveedor aux;

    FILE* archi=fopen(archivo, "rb");

    if (archi!=NULL)
    {
        while(fread(&aux,sizeof(proveedor),1,archi)>0)
        {
            if(aux.estadoprovedor == 1)
            {
                muestraproveedor(aux);
            }

        }
        fclose(archi);
    }
}


nodoLP* cargarlistaprovdesdearchi(char archivo[], nodoLP*lista)
{
    proveedor aux;
    nodoLP *nuevo;
    FILE *archi = fopen(archivo, "rb");

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(proveedor), 1, archi) > 0)
        {
            nodoLP *buscado = buscarproveedorenlista(lista, aux.nombreprov);

            if (buscado == NULL)
            {
                nodoLP* nuevo = crearnodolp(aux);
                lista = agregaralprincipioLP(lista, nuevo);
            }
        }
        fclose(archi);
    }
    return lista;
}




nodoLP* cargarlistaprovdesdearchiEnOrden1(char archivo[], nodoLP*lista)
{
    proveedor aux;
    nodoLP *nuevo;
    FILE *archi = fopen(archivo, "rb");

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(proveedor), 1, archi) > 0)
        {
            nodoLP *buscado = buscarproveedorenlista(lista, aux.nombreprov);

            if (buscado == NULL)
            {
                nodoLP* nuevo = crearnodolp(aux);
                lista = agregarEnOrdenNombreAscendente(lista, nuevo);
            }
        }
        fclose(archi);
    }
    return lista;
}


nodoLP* cargarlistaprovdesdearchiEnOrden2(char archivo[], nodoLP*lista)
{
    proveedor aux;
    nodoLP *nuevo;
    FILE *archi = fopen(archivo, "rb");

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(proveedor), 1, archi) > 0)
        {
            nodoLP *buscado = buscarproveedorenlista(lista, aux.nombreprov);

            if (buscado == NULL)
            {
                nodoLP* nuevo = crearnodolp(aux);
                lista = agregarEnOrdenNombreDescendente(lista, nuevo);
            }
        }
        fclose(archi);
    }
    return lista;
}


nodoLP* cargarlistaprovdesdearchiEnOrden3(char archivo[], nodoLP*lista)
{
    proveedor aux;
    nodoLP *nuevo;
    FILE *archi = fopen(archivo, "rb");

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(proveedor), 1, archi) > 0)
        {
            nodoLP *buscado = buscarproveedorenlista(lista, aux.nombreprov);

            if (buscado == NULL)
            {
                nodoLP* nuevo = crearnodolp(aux);
                lista = agregarEnOrdenTipoProductoAscendente(lista, nuevo);
            }
        }
        fclose(archi);
    }
    return lista;
}


nodoLP* cargarlistaprovdesdearchiEnOrden4(char archivo[], nodoLP*lista)
{
    proveedor aux;
    nodoLP *nuevo;
    FILE *archi = fopen(archivo, "rb");

    if (archi != NULL)
    {
        while (fread(&aux, sizeof(proveedor), 1, archi) > 0)
        {
            nodoLP *buscado = buscarproveedorenlista(lista, aux.nombreprov);

            if (buscado == NULL)
            {
                nodoLP* nuevo = crearnodolp(aux);
                lista = agregarEnOrdenTipoProductoDescendente(lista, nuevo);
            }
        }
        fclose(archi);
    }
    return lista;
}


nodoLP* buscarproveedorenlista(nodoLP* lista, char nombreprov[20])
{
    nodoLP *seg = lista;
    nodoLP *buscado = NULL;

    while (seg != NULL)
    {
        if (strcmpi(seg->dato.nombreprov, nombreprov) == 0)
        {
            buscado = seg;
            break;
        }
        seg = seg->siguiente;
    }
    return buscado;
}


void muestraunsector(registroarchivosector aux)
{
    printf("\nSector:%s\n",aux.nombresector);
    printf("ID sector:%i",aux.idsector);
}

sector cargasector(registroarchivo reg)
{
    sector s;
    s.idSector=reg.idSector;
    strcpy(s.nombreSector,reg.nombreSector);
    s.estadosector=reg.estadosector;

    return s;
}

producto cargaproducto(registroarchivo reg)
{
    producto p;
    p.cantidadProducto=reg.cantidadProducto;
    p.idProducto=reg.idProducto;
    strcpy(p.nombreProducto,reg.nombreProducto);
    p.precio=reg.precio;
    return p;
}
nodoL*alta(nodoL*lista, sector s, producto p)
{
    nodoA*nuevoarbol=crearNodoArbol(p);
    nodoL*buscado=buscarpos(lista, s.idSector);

    if(buscado==NULL)
    {
        nodoL*Snuevo=crearnodo(s);
        lista=agregaralprincipio(lista,Snuevo);
        lista->arbolProductos=inicArbol();
        buscado=lista;
    }
    lista->arbolProductos=insertar(lista->arbolProductos,nuevoarbol);
    return lista;

}

nodoL*buscarpos(nodoL*lista, int idsector)
{
    nodoL*seg=lista;
    nodoL*buscado=NULL;
    int flag=0;
    while((seg!=NULL) && (flag==0))
    {
        if(seg->dato.idSector == idsector)
        {
            buscado=seg;
            flag=1;
        }
        seg=seg->siguiente;
    }

    return buscado;
}

nodoL*cargalistadesdeARCHIVO(nodoL*lista, char archivo[], registroarchivo reg)
{
    producto p;
    sector s;

    FILE *archi=fopen(archivo,"rb");

    if(archi!=NULL)
    {
        while(fread(&reg,sizeof(registroarchivo),1,archi)>0)
        {
            s=cargasector(reg);

            nodoL*buscado=buscarpos(lista,s.idSector);

            if(buscado==NULL)
            {
                p=cargaproducto(reg);
                lista=alta(lista,s,p);
            }
            else
            {

                p=cargaproducto(reg);
                nodoA*busproducto=buscarporProductoID(buscado->arbolProductos,p.idProducto);
                if(busproducto==NULL)
                {

                    nodoA*produainsrtar=crearNodoArbol(p);
                    buscado->arbolProductos= insertar(buscado->arbolProductos,produainsrtar);

                }
            }
        }
        fclose(archi);
    }
    return lista;
}

void mostrarLDA(nodoL*lista)
{
    nodoL*seg=lista;

    while(seg!=NULL)
    {
        if(seg->dato.estadosector==1)
        {
             printf("\nEl nombre del sector es: %s\n",seg->dato.nombreSector);
        printf("El ID del sector es: %i\n",seg->dato.idSector);
        inorden(seg->arbolProductos);
        printf("\n-------------------------------------\n");
        }

        seg=seg->siguiente;
    }

}

void mostrarUnSectorLDA(nodoL*lista, int idDelSector)
{
    nodoL*seg=lista;
    int flag=0;

    while(seg!=NULL && flag==0)
    {
        if(seg->dato.idSector==idDelSector)
        {

            printf("\n-------------------------------------\n");
            printf("\nEl nombre del sector es: %s\n",seg->dato.nombreSector);
            printf("El ID del sector es: %i\n\n",seg->dato.idSector);
            inorden(seg->arbolProductos);
            printf("\n-------------------------------------\n");

            flag=1;

        }
        else
        {
            seg=seg->siguiente;
        }
    }
}

/// NUEVOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

int menuDatosProveedor()
{
    int opc;

    printf("Que desea modificar?\n");
    printf("\n[ 1 ] Nombre.");
    printf("\n[ 2 ] Numero de telefono.");
    printf("\n[ 3 ] Direccion del proveedor.");
    printf("\n[ 4 ] Tipo de producto.");
    printf("\n[ 0 ] SALIR");
    printf("\n\nINGRESE UNA OPCION: ");
    printf("\n");
    scanf("%i", &opc);
    system("cls");

    return opc;
}

nodoLP * modificarProveedor(nodoLP * lista, char nombreBuscar[])
{

    nodoLP * seguidora = lista;
    proveedor copia;
    int opc;
    int flag = 0;
    char ctrl = 's';

    while(seguidora != NULL)
    {
        if (strcmpi(seguidora->dato.nombreprov, nombreBuscar)== 0)
        {
            do
            {
                opc = menuDatosProveedor();
                switch (opc)
                {
                case 1:
                    printf("\nIngrese el nuevo nombre: ");
                    fflush(stdin);
                    gets(seguidora->dato.nombreprov);


                    printf("\nDesea continuar modificando datos:(s/n) ");
                    fflush(stdin);
                    scanf("%c", &ctrl);
                    break;
                case 2:
                    printf("\nIngrese el nuevo numero de telefono: ");
                    scanf("%i", &seguidora->dato.numerocontacto);


                    printf("\nDesea continuar modificando datos:(s/n) ");
                    fflush(stdin);
                    scanf("%c", &ctrl);
                    break;
                case 3:
                    printf("\nIngrese la nueva direccion: ");
                    fflush(stdin);
                    gets(seguidora->dato.direccion);


                    printf("\nDesea continuar modificando datos:(s/n) ");
                    fflush(stdin);
                    scanf("%c", &ctrl);
                    break;
                case 4:
                    printf("\nIngrese el tipo de producto: ");
                    fflush(stdin);
                    gets(seguidora->dato.tipoproducto);

                    printf("\nDesea continuar modificando datos:(s/n) ");
                    fflush(stdin);
                    scanf("%c", &ctrl);
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    printf("\nOpcion incorrecta. Ingrese nuevamente: ");
                    break;
                }

            }
            while (opc != 0 && ctrl == 's');

            strcpy(copia.nombreprov,seguidora->dato.nombreprov);
        copia.numerocontacto = seguidora->dato.numerocontacto;
        strcpy(copia.direccion, seguidora->dato.direccion);
        strcpy(copia.tipoproducto, seguidora->dato.tipoproducto);
        }

        seguidora = seguidora->siguiente;
    }



    guardarListaEnArchivo(nombreBuscar,copia);
    return lista;
}





int menuDatosSector()
{
    int opc1;

    printf("Que desea modificar?\n");
    printf("\n[ 1 ] Nombre.");
    printf("\n[ 2 ] ID Sector.");
    printf("\n[ 0 ] SALIR");
    printf("\n\nINGRESE UNA OPCION: ");
    printf("\n");
    scanf("%i", &opc1);
    system("cls");

    return opc1;
}

nodoL * modificarSector(nodoL * lista, char nombreBuscar[])
{

    nodoL * seguidora = lista;
    sector copia;
    int opc1;
    int flag = 0;
    char ctrl = 's';

    while(seguidora != NULL)
    {
        if (strcmpi(seguidora->dato.nombreSector, nombreBuscar)== 0)
        {
            do
            {
                opc1 = menuDatosSector();
                switch (opc1)
                {
                case 1:
                    printf("\nIngrese el nuevo nombre: ");
                    fflush(stdin);
                    gets(seguidora->dato.nombreSector);


                    printf("\nDesea continuar modificando datos:(s/n) ");
                    fflush(stdin);
                    scanf("%c", &ctrl);
                    break;
                case 2:
                    printf("\nIngrese el nuevo ID del sector: ");
                    scanf("%i", &seguidora->dato.idSector);


                    printf("\nDesea continuar modificando datos:(s/n) ");
                    fflush(stdin);
                    scanf("%c", &ctrl);
                    break;
                case 0:
                    system("cls");
                    break;
                default:
                    printf("\nOpcion incorrecta. Ingrese nuevamente: ");
                    break;
                }
            }
            while (opc1 != 0 && ctrl == 's');

            strcpy(copia.nombreSector,seguidora->dato.nombreSector);
        copia.idSector = seguidora->dato.idSector;
        }

        seguidora = seguidora->siguiente;
    }



    guardarListaEnArchivosectores(nombreBuscar,copia);
    return lista;
}



void guardarListaEnArchivosectores(char nombre [], sector nuevo)
{
    FILE *buffer = fopen(archivogeneral, "r+b");
    registroarchivo aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(registroarchivo), 1, buffer) > 0)
        {
            if (strcmpi(aux.nombreSector, nombre)==0)
            {
                strcpy(aux.nombreSector, nuevo.nombreSector);
                aux.idSector = nuevo.idSector;

                fseek(buffer, sizeof(registroarchivo)*(-1), 1);
                fwrite(&aux, sizeof(registroarchivo), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }

}

























void guardarListaEnArchivo(char nombre [], proveedor nuevo)
{
    FILE *buffer = fopen(archivoprov, "r+b");
    proveedor aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(proveedor), 1, buffer) > 0)
        {
            if (strcmpi(aux.nombreprov, nombre)==0)
            {
                strcpy(aux.nombreprov, nuevo.nombreprov);
                strcpy(aux.direccion, nuevo.direccion);
                strcpy(aux.tipoproducto, nuevo.tipoproducto);
                aux.numerocontacto = nuevo.numerocontacto;

                fseek(buffer, sizeof(proveedor)*(-1), 1);
                fwrite(&aux, sizeof(proveedor), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }

}

void guardarEstadoProveedorEnArchivo(char nombre [])
{
    FILE *buffer = fopen(archivoprov, "r+b");
    proveedor aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(proveedor), 1, buffer) > 0)
        {
            if (strcmpi(aux.nombreprov, nombre)==0)
            {
                aux.estadoprovedor = 0;

                fseek(buffer, sizeof(proveedor)*(-1), 1);
                fwrite(&aux, sizeof(proveedor), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }

}

nodoLP * darDeBajaUnProveedor (nodoLP * lista, char nombre [])
{
    nodoLP * seguidora = lista;
    proveedor copia;

    while(seguidora != NULL)
    {
        if (strcmpi(seguidora->dato.nombreprov, nombre)== 0)
        {
            seguidora->dato.estadoprovedor = 0;
            copia.estadoprovedor = 0;
        }

        seguidora = seguidora->siguiente;

    }

    guardarEstadoProveedorEnArchivo(nombre);
    return lista;
}

void guardarEstadoProveedorActivoEnArchivo(char nombre [])
{
    FILE *buffer = fopen(archivoprov, "r+b");
    proveedor aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(proveedor), 1, buffer) > 0)
        {
            if (strcmpi(aux.nombreprov, nombre)==0)
            {
                aux.estadoprovedor = 1;

                fseek(buffer, sizeof(proveedor)*(-1), 1);
                fwrite(&aux, sizeof(proveedor), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }

}

nodoLP * darDeAltaUnProveedor (nodoLP * lista, char nombre [])
{
    nodoLP * seguidora = lista;

    while(seguidora != NULL)
    {
        if (strcmpi(seguidora->dato.nombreprov, nombre)== 0)
        {
            seguidora->dato.estadoprovedor = 1;
        }

        seguidora = seguidora->siguiente;

    }

    guardarEstadoProveedorActivoEnArchivo(nombre);
    return lista;
}

int menuOrdenamientos()
{
    int opc;

    printf("¿Como desea ordenar las listas?\n");

    printf("\n[ 1 ] Nombre ascendente\n");
    printf("\n[ 2 ] Nombre descendente\n");
    printf("\n[ 3 ] Tipo de producto ascendente\n");
    printf("\n[ 4 ] Tipo de producto descendente\n");
    printf("\n[ 0 ] SALIR");
    printf("\n\nINGRESE UNA OPCION: ");
    printf("\n  ");
    scanf("%i", &opc);
    system("cls");

    return opc;
}

int ordenarSegunOpc(nodoLP * lista)
{
    int opc;
    char ctrl = 's';

    opc = menuOrdenamientos();
    switch (opc)
    {
    case 1:
        ordenarListaNombreAscendente(lista);
        break;
    case 2:
        ordenarListaNombreDescendente(lista);
        break;
    case 3:
        ordenarListaTipoProductoAscendente(lista);
        break;
    case 4:
        ordenarListaTipoProductoDescendente(lista);
        break;
    case 0:
        system("cls");
        break;
    default:
        printf("OPCION INCORRECTA. Intente de nuevo.\n\n");
        break;

    }
    return opc;
}

void ordenarListaNombreAscendente(nodoLP* lista)
{
    nodoLP *i, *j;
    proveedor aux;

    for (i = lista; i != NULL; i = i->siguiente)
    {
        for (j = i->siguiente; j != NULL; j = j->siguiente)
        {
            if (strcmpi(i->dato.nombreprov, j->dato.nombreprov) >0)
            {
                aux = i->dato;
                i->dato = j->dato;
                j->dato = aux;
            }
        }
    }
}

void ordenarListaNombreDescendente(nodoLP* lista)
{
    nodoLP *i, *j;
    proveedor aux;

    for (i = lista; i != NULL; i = i->siguiente)
    {
        for (j = i->siguiente; j != NULL; j = j->siguiente)
        {
            if (strcmpi(i->dato.nombreprov, j->dato.nombreprov) <0)
            {
                aux = i->dato;
                i->dato = j->dato;
                j->dato = aux;
            }
        }
    }
}

void ordenarListaTipoProductoAscendente(nodoLP* lista)
{
    nodoLP *i, *j;
    proveedor aux;

    for (i = lista; i != NULL; i = i->siguiente)
    {
        for (j = i->siguiente; j != NULL; j = j->siguiente)
        {
            if (strcmpi(i->dato.tipoproducto, j->dato.tipoproducto) >0)
            {
                aux = i->dato;
                i->dato = j->dato;
                j->dato = aux;
            }
        }
    }
}

void ordenarListaTipoProductoDescendente(nodoLP* lista)
{
    nodoLP *i, *j;
    proveedor aux;

    for (i = lista; i != NULL; i = i->siguiente)
    {
        for (j = i->siguiente; j != NULL; j = j->siguiente)
        {
            if (strcmpi(i->dato.tipoproducto, j->dato.tipoproducto) <0)
            {
                aux = i->dato;
                i->dato = j->dato;
                j->dato = aux;
            }
        }
    }
}

nodoL*sumarstock(nodoL*lista,int idsector,int idproducto, int cantidadentrada)
{
    nodoA*buscado;
    nodoL*buscalista=buscarpos(lista,idsector);
    if(buscalista!=NULL)
    {
        buscado=buscarporProductoID(buscalista->arbolProductos,idproducto);

        if(buscado!=NULL)
        {
            buscado->dato.cantidadProducto= buscado->dato.cantidadProducto + cantidadentrada;

        }

        else
        {
            printf("El producto no fue encontrado");
        }
    }
//    actualizararchivosuma(buscado->dato.nombreProducto,cantidadentrada);
    return lista;
}

nodoL *darDeBajaUnSecotr(nodoL* lista, char nombre[])
{
    nodoL * seguidora = lista;

    while(seguidora != NULL)
    {
        if (strcmpi(seguidora->dato.nombreSector, nombre)== 0)
        {
            seguidora->dato.estadosector = 0;


        }

        seguidora = seguidora->siguiente;

    }
    return lista;
}

nodoL * darDeAltaUnsector (nodoL * lista, char nombre [])
{
    nodoL * seguidora = lista;
    int flag=0;
    while(seguidora != NULL)
    {
        if (strcmpi(seguidora->dato.nombreSector, nombre)== 0 && (flag==0))
        {
            seguidora->dato.estadosector = 1;
            guardarEstadoSectoraltaEnArchivo(nombre);
            flag=1;
        }

        seguidora = seguidora->siguiente;

    }
    return lista;
}

void guardarEstadoSectorEnArchivo(char nombre[])
{
    FILE *buffer = fopen(archivogeneral, "r+b");
    registroarchivo aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(registroarchivo), 1, buffer) > 0)
        {
            if (strcmpi(aux.nombreSector, nombre)==0)
            {
                aux.estadosector = 0;

                fseek(buffer, sizeof(registroarchivo)*(-1), 1);
                fwrite(&aux, sizeof(registroarchivo), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }

}

void guardarEstadoSectoraltaEnArchivo(char nombre[])
{
    FILE *buffer = fopen(archivogeneral, "r+b");
    registroarchivo aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(registroarchivo), 1, buffer) > 0)
        {
            if (strcmpi(aux.nombreSector, nombre)==0)
            {
                aux.estadosector = 1;

                fseek(buffer, sizeof(registroarchivo)*(-1), 1);
                fwrite(&aux, sizeof(registroarchivo), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }

}



nodoL * darDeBajaUnsEC (nodoL * lista, char nombre [])
{

    nodoL * seguidora = lista;
    sector copia;

    while(seguidora != NULL)
    {
        if (strcmpi(seguidora->dato.nombreSector, nombre)== 0)
        {
            seguidora->dato.estadosector = 0;
            copia.estadosector = 0;
            guardarEstadoSectorEnArchivo(nombre);
        }

        seguidora = seguidora->siguiente;

    }

    return lista;
}





void actualizararchivosuma(int id , int cantidad)
{
    FILE *buffer = fopen(archivogeneral, "r+b");
    registroarchivo aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(registroarchivo), 1, buffer) > 0)
        {
            if(aux.idProducto == id)
            {

                aux.cantidadProducto= aux.cantidadProducto+cantidad;

                fseek(buffer, sizeof(registroarchivo)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(registroarchivo), 1, buffer);

                flag = 1;
            }

        }
        fclose(buffer);
    }

}

void actualizararchivoresta(int id, int cantidad)
{
    FILE *buffer = fopen(archivogeneral, "r+b");
    registroarchivo aux;
    int flag = 0;

    if (buffer)
    {
      while (flag == 0 && fread(&aux, sizeof(registroarchivo), 1, buffer) > 0)
        {
            if (aux.idProducto==id)
            {
                aux.cantidadProducto= aux.cantidadProducto-cantidad;

                fseek(buffer, sizeof(registroarchivo)*(-1), SEEK_CUR);
                fwrite(&aux, sizeof(registroarchivo), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }

}





