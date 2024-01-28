#ifndef ARCHIVOANDLDA_H_INCLUDED
#define ARCHIVOANDLDA_H_INCLUDED
#include "lista.h"
#define archivoprov "registroarhivoprov.bin"
#define archivogeneral "registroarchivogeneral.bin"
typedef struct
{
    int idProducto;
    char nombreProducto[30];
    int cantidadProducto;
    int precio;
    int estado;
    int idSector;
    char nombreSector[30];
    int estadosector;
} registroarchivo;

typedef struct
{
    char nombreprov[20];
    int numerocontacto;
    char direccion[20];
    char tipoproducto[30];
    int estadoprovedor;
} registroarchivoprov;

typedef struct
{
    int idsector;
    char nombresector[20];
} registroarchivosector;


registroarchivo cargaUnProducto (registroarchivo aux);
void muestraUnProducto (registroarchivo aux);

void cargaArchivo (char archivo[]);
void muestraArchivo (char archivo[]);


proveedor cargaunproveedor(proveedor aux);  ///funcion para cargar el archivo original

proveedor cargaunproveedormanual(); /// funcion aux para cargar un proveedor. Luego se utiliza en cargar archivo
void cargaArchivoprov (char archivo[]);

void muestraproveedor(proveedor aux); /// funcion aux para mostrar un proveedor. Luego se utiliza en mostrar archivo
void muestraArchivoprov (char archivo[]);


nodoLP* buscarproveedorenlista(nodoLP* lista, char nombreprov[20]); /// busca si un proveedor existe en la lista
nodoLP* cargarlistaprovdesdearchi(char archivo[], nodoLP*lista);   ///  carga la lista de proveedores con los datos del archivo,
                                                                  ///   verificando que no se repita el nombre de la empresa

void muestraunsector(registroarchivosector aux);
sector cargasector(registroarchivo reg);  /// funcion aux que se invoca en la funcion siguiente
nodoL*cargalistadesdeARCHIVO(nodoL*lista, char archivo[], registroarchivo reg); /// toma los datos desde el archivo y carga la lista
                                                                               ///  de sectores
nodoL*alta(nodoL*lista, sector s, producto p);
nodoL*buscarpos(nodoL*lista, int idsector);
producto cargaproducto(registroarchivo reg);


void mostrarLDA(nodoL*lista);
void mostrarUnSectorLDA(nodoL*lista, int idDelSector);


int menuDatosProveedor();
nodoLP * modificarProveedor(nodoLP * lista, char nombreBuscar[]);
void guardarListaEnArchivo(char nombre [], proveedor nuevo);
void guardarEstadoProveedorEnArchivo(char nombre []);
nodoLP * darDeBajaUnProveedor (nodoLP * lista, char nombre []);
void guardarEstadoProveedorActivoEnArchivo(char nombre []);
nodoLP * darDeAltaUnProveedor (nodoLP * lista, char nombre []);
int menuOrdenamientos();
int ordenarSegunOpc(nodoLP * lista);
void ordenarListaNombreAscendente(nodoLP* lista);
void ordenarListaNombreDescendente(nodoLP* lista);
void ordenarListaTipoProductoAscendente(nodoLP* lista);
void ordenarListaTipoProductoDescendente(nodoLP* lista);


nodoL*sumarstock(nodoL*lista,int idsector,int idproducto, int cantidadentrada);
void actualizararchivoresta(int id, int cantidad);
void actualizararchivosuma(int id , int cantidad);


#endif // ARCHIVOANDLDA_H_INCLUDED
