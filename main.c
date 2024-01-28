#include <stdio.h>
#include <stdlib.h>
#include "arboles.h"
#include "lista.h"
#include "filas.h"
#include "registroAndInicio.h"
#include "archivoAndLDA.h"





int main()
{
    char archivoUsuario [] = "archivo.bin";

    int menu();

    int opc, flag = 1;
    Usuario nuevo;

    do
    {
        opc = menu();

        system("cls");
        system("color 5E");

        switch (opc)
        {
        case 1:
            nuevo = iniciosesion(archivoUsuario);
            if (nuevo.enter == 1)
            {
                menuUsuario(nuevo);
            }
            else
            {
                printf("Contrasena o mail incorrecto.\n\n");
            }
            break;
        case 2:
            registroEnd(archivoUsuario);
            break;
        default:
            flag = 0;
            break;
        }

        if (flag == 1)
        {
            system("PAUSE");
        }
    }
    while (flag == 1);

    printf("Termina programa...\n");
    return 0;
}


int menu()
{
    system("color 5E");
    int input, valid = 0;
    system("cls");

    printf("\n\t\t\t\t\t\t CONTROL DE STOCK");
    printf("\n------------------------------------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t     OPCIONES");
    printf("\n [ 1 ] Iniciar sesion");
    printf("\n [ 2 ] Registrarse");
    printf("\n [ 0 ] SALIR");
    printf("\n\nINGRESE UNA OPCION: ");

    do
    {
        fflush(stdin);
        valid = scanf("%i", &input);
    }
    while (valid == 0);

    return input;
}

void menuUsuario(Usuario a)
{

    nodoLP *listaprov = iniclistaLP();
    nodoL *listaarb = iniclista();
    registroarchivo reg;
    listaarb = cargalistadesdeARCHIVO(listaarb,archivogeneral,reg);

    int opcionprincipal;
    int aux;
    int elegirOrden;
    char auxOrden;
    int opcionOrden;
    int opcion;
    int flag = 0;

    do
    {
        printf("Ingrese a que seccion del programa desea acceder:\n");
        printf("\n [ 1 ] Proveedores\n");
        printf("\n [ 2 ] Sectores\n");
        printf("\n [ 3 ] Compradores\n");
        printf("\n [ 4 ] Salir del programa\n");
        printf("\n  ");

        scanf("%i", &opcionprincipal);
        system("cls");

        switch (opcionprincipal)
        {
        case 1:
        {
            do
            {

                printf("\n\nIngrese la opcion que desea realizar:\n");
                printf("\n [ 1 ] Cargar un nuevo proveedor\n");
                printf("\n [ 2 ] Buscar un proveedor dentro del sistema y ver su informacion\n");
                printf("\n [ 3 ] Mostrar lista de proveedores completa\n");
                printf("\n [ 4 ] Modificar datos del proveedor\n");
                printf("\n [ 5 ] Dar de baja un proveedor\n");
                printf("\n [ 6 ] Dar de alta un proveedor\n");
                printf("\n [ 7 ] Mostrar lista de proveedores en orden\n");
                printf("\n [ 0 ] Salir de la seccion proveedores\n");
                printf("\n  ");
                scanf("%i", &opcion);
                system("cls");


                switch (opcion)
                {
                case 1:

                    do
                    {
                        printf("\nElija una opcion:\n");
                        printf("\n [ 1 ]  Agregar en orden ascendente por nombre\n");
                        printf("\n [ 2 ]  Agregar en orden descendente por nombre\n");
                        printf("\n [ 3 ]  Agregar en orden ascendente por tipo de producto\n");
                        printf("\n [ 4 ]. Agregar en orden descendente por tipo de producto\n");
                        printf("\n [ 0 ] Salir\n");
                        printf("\n  ");
                        scanf("%i", &opcionOrden);

                        switch(opcionOrden)
                        {
                        case 1:
                        {
                            cargaArchivoprov(archivoprov);
                            listaprov = cargarlistaprovdesdearchiEnOrden1(archivoprov,listaprov);
                            mostrar_listaprov(listaprov);
                            flag = 1;
                            break;
                        }
                        case 2:
                        {
                            cargaArchivoprov(archivoprov);
                            listaprov = cargarlistaprovdesdearchiEnOrden2(archivoprov, listaprov);
                            mostrar_listaprov(listaprov);
                            flag = 1;
                            break;
                        }
                        case 3:
                        {
                            cargaArchivoprov(archivoprov);
                            listaprov = cargarlistaprovdesdearchiEnOrden3(archivoprov, listaprov);
                            mostrar_listaprov(listaprov);
                            flag = 1;
                            break;
                        }
                        case 4:
                        {
                            cargaArchivoprov(archivoprov);
                            listaprov = cargarlistaprovdesdearchiEnOrden4(archivoprov, listaprov);
                            mostrar_listaprov(listaprov);
                            flag = 1;
                            break;
                        }
                        case 0:
                            printf("Saliendo del programa.\n");
                            flag=1;
                            break;
                        default:
                            printf("Opción inválida.\n");
                        }
                    }
                    while (opcion != 0 && flag == 0);

                    break;
                case 2:

                    if (listaprov == NULL)
                    {
                        listaprov = cargarlistaprovdesdearchi(archivoprov,listaprov);
                    }
                    system("cls");
                    printf("Ha elegido buscar un proveedor y mostrar su informacion.\n\n");
                    char nombrebusqueda[30];
                    printf("Ingrese el nombre del proveedor que desea buscar: ");
                    fflush(stdin);
                    gets(nombrebusqueda);

                    nodoLP * buscado = buscarproveedorenlista(listaprov, nombrebusqueda);
                    if (buscado != NULL)
                    {
                        printf("El proveedor fue encontrado con exito\n");
                        escribirprovlista(buscado);

                    }
                    else
                    {
                        printf("\nEl proveedor no fue encontrado dentro del sistema\n");
                    }
                    printf("\n\n");
                    system("pause");
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    printf("\nHa elegido mostrar la lista de proveedores.\n");

                    if (listaprov == NULL)
                    {
                        listaprov = cargarlistaprovdesdearchi(archivoprov,listaprov);
                    }
                    mostrar_listaprov(listaprov);

                    break;
                case 4:
                    system("cls");
                    printf("Modificando un proveedor.\n");
                    char nombreprov[20];
                    printf("Ingrese el nombre del proveedor que desea modificar: ");
                    fflush(stdin);
                    gets(nombreprov);
                    if (listaprov == NULL)
                    {
                        listaprov = cargarlistaprovdesdearchi(archivoprov,listaprov);
                    }

                    buscado = buscarproveedorenlista(listaprov,nombreprov);
                    if (buscado != NULL)
                    {
                        listaprov = modificarProveedor(listaprov,nombreprov);
                        mostrar_listaprov(listaprov);
                    }
                    else
                    {
                        printf("Proveedor no encontrado en la lista.\n");

                    }
                    system("pause");
                    system("cls");
                    break;
                case 5:

                    if (listaprov == NULL)
                    {
                        listaprov = cargarlistaprovdesdearchi(archivoprov,listaprov);
                    }

                    printf("Ingrese el nombre del proveedor que desea dar de baja: ");
                    fflush(stdin);
                    gets(nombreprov);
                    buscado = buscarproveedorenlista(listaprov,nombreprov);

                    if (buscado != NULL)
                    {
                        listaprov = darDeBajaUnProveedor(listaprov,nombreprov);
                        printf("El proveedor %s ha sido dado de baja correctamente ", nombreprov);
                    }
                    else
                    {
                        printf("Proveedor no encontrado en la lista.\n");
                    }

                    break;
                case 6:
                    if (listaprov == NULL)
                    {
                        listaprov = cargarlistaprovdesdearchi(archivoprov,listaprov);
                    }


                    printf("Ingrese el nombre del proveedor que desea dar de alta: ");
                    fflush(stdin);
                    gets(nombreprov);
                    buscado = buscarproveedorenlista(listaprov,nombreprov);
                    if (buscado != NULL)
                    {
                        listaprov = darDeAltaUnProveedor(listaprov,nombreprov);
                        printf("El proveedor %s ha sido dado de alta correctamente ", nombreprov);
                    }
                    else
                    {
                        printf("Proveedor no encontrado en la lista.\n");
                    }
                    break;
                case 7:

                    do
                    {
                    if (listaprov == NULL)
                    {
                        listaprov = cargarlistaprovdesdearchi(archivoprov,listaprov);
                    }
                        aux = ordenarSegunOpc(listaprov);
                        if (aux != 0)
                        {

                            mostrar_listaprov(listaprov);

                            printf("\nSi quiere ver la lista de otra manera presione 's': ");
                            fflush(stdin);
                            scanf("%c", &auxOrden);
                        }
                    }
                    while (aux != 0 && auxOrden == 's');

                    break;
                case 0:
                    printf("Saliendo de la seccion de proveedores.\n");
                    system("cls");
                    break;
                default:
                    printf("OPCION INCORRECTA. Intente de nuevo.\n\n");
                    break;
                }
            }
            while (opcion != 0);
            break;

        }


            case 2:
        {
            int opcion1;
            do
            {
                printf("\n\nIngrese la opcion que desea realizar:\n");
                printf("\n [ 1 ] Cargar un nuevo sector\n");
                printf("\n [ 2 ] Buscar sector especifico\n");
                printf("\n [ 3 ] Mostrar todos los sectores y sus productos\n");
                printf("\n [ 4 ] Sumar stock por producto\n");
                printf("\n [ 5 ] Dar de baja un sector\n");
                printf("\n [ 6 ] Dar de alta un sector\n");
                printf("\n [ 7 ] Modificar sector\n");
                printf("\n [ 8 ] Salir de la seccion sectores\n");

                scanf("%i", &opcion1);

                switch (opcion1)
                {
                case 1:
                    system("cls");
                    printf("\nCARGANDO NUEVO SECTOR...\n");
                    cargaArchivo(archivogeneral);
                    listaarb = cargalistadesdeARCHIVO(listaarb,archivogeneral,reg);
                    break;
                case 2:
                    system("cls");
                    printf("BUSCANDO SECTOR...\n");
                    int busquedaID;
                    printf("Ingrese la ID de un sector a buscar: ");
                    fflush(stdin);
                    scanf("%d",&busquedaID);
                    mostrarUnSectorLDA(listaarb,busquedaID);
                    break;
                case 3:
                    printf("MOSTRANDO TODOS LOS SECTORES Y SUS PRODUCTOS...\n");
                    mostrarLDA(listaarb);
                    break;
                case 4:
                    system("cls");
                    printf("Stockear sector...\n");
                    int cantidadprodacomprar;
                    int busquedaid2;
                    printf("Ingrese el ID del producto que desea stockear: ");
                    fflush(stdin);
                    scanf("%i",&busquedaid2);

                    printf("Ingrese la cantidad de productos que va a comprar: ");
                    fflush(stdin);
                    scanf("%i",&cantidadprodacomprar);
                    int sectorid;
                    printf("Ingrese el id del sector: ");
                    fflush(stdin);
                    scanf("%i",&sectorid);

                    listaarb=sumarstock(listaarb,sectorid,busquedaid2,cantidadprodacomprar);
                    actualizararchivosuma(busquedaid2,cantidadprodacomprar);
                    break;

                    case 5:
                    system("cls");
                            printf("\nDar de baja sector...\n");
                            char nombresec[20];
                            printf("Ingrese el nombre del sector que desea dar de baja\n");
                            fflush(stdin);
                            gets(nombresec);
                            listaarb=darDeBajaUnsEC(listaarb,nombresec);
                    break;



                    case 6:
                    system("cls");
                        printf("\nDar de alta sector...\n");
                            char nombresec1[20];
                            printf("Ingrese el nombre del sector que desea dar de alta\n");
                            fflush(stdin);
                            gets(nombresec1);
                            listaarb=darDeAltaUnsector(listaarb,nombresec1);

                    break;

                      case 7:
                    system("cls");
                        printf("\nModificando sector\n");
                            char nombresec2[20];
                            printf("Ingrese el nombre del sector que desea modificar\n");
                            fflush(stdin);
                            gets(nombresec2);
                            listaarb=modificarSector(listaarb,nombresec2);

                    break;

                case 8:
                    printf("Saliendo de la seccion sectores.\n");
                    system("cls");
                    break;
                default:
                    printf("OPCION INCORRECTA. Intente de nuevo.\n\n");
                    break;
                }
            }
            while (opcion1 != 8);
            break;
        }

        case 3:
        {

            Fila fila;
            inicFila(&fila);
            int opcion3;

            do
            {

                printf("\n [ 1 ] Cargar un comprador en la fila ");
                printf("\n [ 2 ] Atender en la caja por orden de llegada ");
                printf("\n [ 3 ] Mostrar fila ");
                printf("\n [ 4 ] Salir ");
                printf("\nIngrese la opcion: ");
                scanf("%d", &opcion3);

                switch (opcion3)
                {
                case 1:
                    system("cls");

                    leer(&fila, listaarb);


                    break;
                case 2:
                    system("cls");

                    if (filaVacia(&fila))
                    {
                        comprador atendido = extraer(&fila);
                        printf("\nComprador atendido:\n");
                        mostrarComprador(atendido);
                    }
                    else
                    {
                        printf("\nNo hay compradores en la fila.\n");
                    }
                    break;
                case 3:
                    if(filaVacia(&fila))
                    {
                       muestraFila(&fila);
                    }
                    else
                    {
                        printf("\nLa fila esta vacia\n");
                    }

                    break;
                case 4:
                    printf("\nSaliendo...\n");
                    break;
                default:
                    printf("\nOpcion no valida.\n");
                    break;
                }
            }
            while (opcion3 != 4);
            break;
        }

        case 4:
            printf("Saliendo del programa.\n");
            break;

        default:
            printf("Opcion no valida. Intente de nuevo.\n\n");
            break;
        }

    }
    while (opcionprincipal != 4);
}

