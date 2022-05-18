#ifndef UTN_H_
#define UTN_H_

/**
 * \brief Solicita un INT al usuario, lo valida en un rango y lo retorna por referencia
 * \param pNumeroIngresado Puntero donde se almacena el valor del INT solicitado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje mostrado al ingresar un INT fuera de rango
 * \param min, max Valores que establecen el rango
 * \param reintentos Cantidad de veces que el usuario puede ingresar el dato fuera de rango
 * \return -1 si el usuario no ingreso un INT validado. 0 si se realizo la carga satisfactoriamente
 */
int getInt(int * pNumeroIngresado, char * mensaje, char * mensajeError, int min, int max, int reintentos);

/**
 * \brief Solicita un FLOAT al usuario, lo valida en un rango y lo retorna por referencia
 * \param pNumeroIngresado Puntero donde se almacena el valor del FLOAT solicitado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje mostrado al ingresar un INT fuera de rango
 * \param min, max Valores que establecen el rango
 * \param reintentos Cantidad de veces que el usuario puede ingresar el dato fuera de rango
 * \return -1 si el usuario no ingreso un FLOAT validado. 0 si se realizo la carga satisfactoriamente
 */
int getFloat(float * pNumeroIngresado, char * mensaje, char * mensajeError, int min, int max, int reintentos);

/**
 * \brief Solicita una cadena al usuario, lo valida y lo retorna por referencia
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje mostrado al ingresar un INT fuera de rango
 * \param cadena Es el array por el que se devuelve la cadena
 * \param len Longitud del array
 * \param reintentos Es la cantidad de veces que puede intentar el usuario ingresar la cadena
 * \return -1 si hubo errores. 0 si se realizo la carga satisfactoriamente
 */
int getString (char mensaje[], char mensajeError[], char cadena[], int len, int reintentos);

/**
 * \brief Solicita al usuario un caracter. Pudiendo ser S,s,N,n
 * \param mensaje Es el mensaje a ser mostrado
 * \param caracter es la variable por la cual se devuelve el caracter ingresado
 * \param reintentos Es la cantidad de veces que puede intentar el usuario ingresar el dato
 * \return -1 si el usuario no ingresa un caracter valido. 0 si se realizo la carga satisfactoriamente
 */
int getCharSiNo (char mensaje[], char * caracter, int reintentos);

/**
 * \brief Recibe un array de caracteres y valida si solo tiene caracteres numericos. Acepta numeros negativos
 * \param cadena Es el array a ser validado
 * \return -1(ERROR), si tiene caracteres no numericos. 0(OK) Solo tiene caracteres numericos
 */
int validarEsInt(char * cadena);

/**
 * \brief Recibe un array de caracteres y valida si solo tiene caracteres numericos. Acepta numeros negativos
 * \param cadena Es el array a ser validado
 * \return -1(ERROR), si tiene caracteres no numericos. 0(OK) Solo tiene caracteres numericos
 */
int validarEsFloat(char * cadena);

/**
 * \brief Recibe por parametro un array de caracteres y le carga un valor.
 * \param cadena Es el array a ser cargado
 * \param len Longitud del array
 * \return -1(ERROR), si los parametros recibidos son nulos. 0(OK) Sei se realizo la carga correctamente
 */
int myGets(char * cadena, int len);

#endif
