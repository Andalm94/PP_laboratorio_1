#ifndef CENSISTA_H_
#define CENSISTA_H_

struct {
	int dia;
	int mes;
	int anio;
} typedef Fecha;

struct {
	char calle[32];
	char numero[32];
} typedef Direccion;

struct {
  int id;
  char nombre[32];
  char apellido[32];
  Fecha fechaDeNacimiento;
  int edad;
  Direccion censistaDireccion;
  int estado;
  int zonaAsignadaId;
  int isEmpty;
} typedef Censista;

/** \brief Inicializa en 0 los campos isEmpty del array
* \param list lista de censistas
* \param len tamanio del array
* \return Retorna -1 si recibe parametros incorrectos. Retorna 0 si se inicializa correctamente
*/
int inicializarCensistas(Censista* list, int len);

/** \brief Recibe por parametros los datos que se cargaran en el array de censista
 * Al dar de alta al censista, se carga su estado como LIBERADO.
* \param list lista de censistas
* \param len tamanio del array
* \param id
* \param nombre
* \param apellido
* \param dia
* \param mes
* \param anio
* \param edad
* \param calle
* \param numero calle
* \return Retorna -1 si hubo errores. Retorna 0 si se realiza el alta correctamente
*/
int altaCensista(Censista* list, int len, int id, char nombre[], char apellido[], int dia, int mes, int anio, int edad, char calle[], char numeroCalle[]);


/** \brief Recibe por parametro el ID de un censista para darlo de baja.
 ** Si el censista tiene zona asignada: list[index].estado = INACTIVO
 ** Si el censista NO tiene zona asignada: list[index].isEmpty = EMPTY]
* \param list lista de censistas
* \param len tamanio del array
* \param id identificador con el que se buscara al censista
* \param mensaje: mensaje de confirmacion de baja
* \return Retorna -1 si hubo errores. Retorna 0 si se da la baja correctamente
*/
int bajaCensista(Censista* list, int len, int id, char mensaje[]);


/** \brief Recibe por parametro un censista y un nuevo dato. Carga ese nuevo dato al campo correspondiente indicado por el parametro 'opcion'
* \param list lista de censistas
* \param nuevoDato dato nuevo a cargar en el campo correspondiente
* \param opcion variable que define el campo a modificar
* \return Retorna -1 si hubo errores. Retorna 0 si se modifica el campo correctamente
*/
int modificarCensista(Censista* censista, char * nuevoDato, int opcion);

/** \brief Busca el primer index libre del array y lo retorna por referencia a traves de la variable index
* \param list lista de censistas
* \param len tamanio del array
* \param index variable donde se almacenara el indice libre
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int buscarIndexLibre(Censista* list, int len, int * index);

/** \brief Busca el index de un censista a traves de un ID pasado por parametro
* \param list lista de censistas
* \param len tamanio del array
* \param id variable que se utilizara para buscar el index del censista con dicho ID
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int buscarIndexCensistaPorId(Censista* list, int len, int id);

/** \brief Recibe un censista por parametro y lo muestra
* \param censista: censista a mostrar
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int mostrarUnCensista(Censista censista);

/** \brief Recibe el listado de censista y lo muestra
* \param list lista de censistas
* \param len tamanio del array
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int mostrarCensistas(Censista* list, int len);

/** \brief Recibe un listado de censistas y valida si hay censistas cargados
* \param list lista de censistas
* \param len tamanio del array
* \return Retorna -1 si no hay censistas cargados. Retorna 0 si hay al menos un censista cargado
*/
int hayCensistas(Censista* list, int len);

/** \brief Recibe un listado de censistas y le hardcodea datos en los campos de las 5 primeras posiciones del array
* \param list lista de censistas
* \return --
*/
void hardcodearCensistas(Censista * list);

#endif

