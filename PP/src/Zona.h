#ifndef ZONA_H_
#define ZONA_H_


struct {
	int censadosInSitu;
	int censadosVirtuales;
	int censadosAusentes;
} typedef Censados;

struct {
	char calle1[32];
	char calle2[32];
	char calle3[32];
	char calle4[32];
} typedef Calles;

struct {
  int id;
  int censistaId;
  int localidad;
  Calles callesDeZona;
  int estado;
  Censados censadosPorZona;
  int isEmpty;
} typedef Zona;

/** \brief Inicializa en 0 los campos isEmpty del array
* \param list lista de zonas
* \param len tamanio del array
* \return Retorna -1 si recibe parametros incorrectos. Retorna 0 si se inicializa correctamente
*/
int inicializarZonas(Zona* list, int len);

/** \brief Recibe por parametros los datos que se cargaran en el array de zonas
* \param list lista de zonas
* \param len tamanio del array
* \param id
* \param localidad
* \param calle1
* \param calle2
* \param calle3
* \param calle4
* \return Retorna -1 si hubo errores. Retorna 0 si se realiza el alta correctamente
*/
int altaZona(Zona* list, int len, int id, int localidad, char calle1[], char calle2[], char calle3[], char calle4[]);

/** \brief Recibe por parametro el ID de una zona para darla de baja.
 ** Si la zona existe y el usuario confirma: list[index].isEmpty = EMPTY]
* \param list lista de zonas
* \param len tamanio del array
* \param id identificador con el que se buscara la zona
* \param mensaje: mensaje de confirmacion de baja
* \return Retorna -1 si hubo errores. Retorna 0 si se da la baja correctamente
*/
int bajaZona(Zona* list, int len, int id, char mensaje[], char arrayLocalidades[][32]);

/** \brief Busca el primer index libre del array y lo retorna por referencia a traves de la variable index
* \param list lista de zonas
* \param len tamanio del array
* \param index variable donde se almacenara el indice libre
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int buscarIndexLibreZona(Zona* list, int len, int * index);

/** \brief Busca el index de una zona a traves de un ID pasado por parametro
* \param list lista de zonas
* \param len tamanio del array
* \param id variable que se utilizara para buscar el index de la zona con dicho ID
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int buscarIndexZonaPorId(Zona* list, int len, int id);

/** \brief Recibe una zona por parametro y la muestra
 * Se muestra el nombre de la localidad cargada a traves del
 * listado de localidades pasado como segundo parametro
* \param zonaSeleccionada: zona a mostrar
* \param arrayLocalidades: listado de localidades
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int mostrarUnaZona(Zona zonaSeleccionada, char arrayLocalidades[][32]);

/** \brief Recibe un listado de zonas por parametro y las muestra
 * Se muestra el nombre de la localidad cargada a traves del
 * listado de localidades pasado como segundo parametro
* \param list: listado de zonas a mostrar
* \param arrayLocalidades: listado de localidades
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int mostrarZonas(Zona * list, int len,  char arrayLocalidades[][32]);

/** \brief Recibe por parametro una zona seleccionada y los censados de dicha zona
 * Carga los censados en cada campo correspondiente.
* \param zonaSeleccionada: zona a cargar datos
* \param censadosInSitu
* \param censadosVirtuales
* \param censadosAusentes
* \return Retorna -1 si hubo errores. Retorna 0 en caso contrario
*/
int cargarDatos(Zona *zonaSeleccionada, int censadosInSitu, int censadosVirtuales, int censadosAusentes);

/** \brief Recibe un listado de zonas y valida si hay zonas cargadas
* \param list lista de zonas
* \param len tamanio del array
* \return Retorna -1 si no hay zonas cargadas. Retorna 0 si hay al menos una zona cargada
*/
int hayZonas(Zona* list, int len);

/** \brief Recibe un listado de zonas y le hardcodea datos en los campos de las 5 primeras posiciones del array
* \param list lista de zonas
* \return --
*/
void hardcodearZonas(Zona* list);

#endif
