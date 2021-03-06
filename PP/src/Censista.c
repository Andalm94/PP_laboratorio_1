#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Censista.h"
#include "UTN.h"

#define EMPTY 0
#define FULL 1

#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3

int inicializarCensistas(Censista* list, int len){
	int retorno = -1;
	int i;

	if(list != NULL && len > 0){
		for (i=0; i<len; i++){
			list[i].isEmpty = EMPTY;
		}
		retorno = 0;
	}

	return retorno;
}

//------------------------------------------------------------------------------------
// -------------------------- ALTA - BAJA - MODIFICACIONES ---------------------------
//------------------------------------------------------------------------------------

int altaCensista(Censista* list, int len, int id, char nombre[], char apellido[], int dia, int mes, int anio, int edad, char calle[], char numeroCalle[]){
	int retorno = -1;

	int indexLibre = -1;


	if(buscarIndexLibre(list, len, &indexLibre) == 0){
		list[indexLibre].id = id;
		strcpy(list[indexLibre].nombre, nombre);
		strcpy(list[indexLibre].apellido, apellido);
		list[indexLibre].fechaDeNacimiento.dia = dia;
		list[indexLibre].fechaDeNacimiento.mes = mes;
		list[indexLibre].fechaDeNacimiento.anio = anio;
		list[indexLibre].edad = edad;
		strcpy(list[indexLibre].censistaDireccion.calle, calle);
		strcpy(list[indexLibre].censistaDireccion.numero, numeroCalle);
		list[indexLibre].estado = LIBERADO;
		list[indexLibre].zonaAsignadaId = -1;
		list[indexLibre].isEmpty = FULL;
		retorno = 0;
	}



	return retorno;
}

int bajaCensista(Censista* list, int len, int id, char mensaje[]){
	int retorno = -1;
	int index;
	char respuesta;

	if(list != NULL && len>0){

		index = buscarIndexCensistaPorId(list, len, id);
		if(index != -1 && mostrarUnCensista(list[index]) != -1 && getCharSiNo(mensaje, &respuesta, 1) == 0 && (respuesta == 'S' || respuesta =='s')){
			if(list[index].zonaAsignadaId == -1){
				list[index].isEmpty = EMPTY;
			}
			else{
				list[index].estado = INACTIVO;
			}
			retorno = 0;
		}
	}

	return retorno;
}

int modificarCensista(Censista* censista, char * nuevoDato, int opcion){
	int retorno = -1;
	int nuevoDatoInt;

	if(censista->isEmpty == FULL && opcion >= 1 && opcion <= 10){
		switch(opcion){
		case 1:
			strcpy(censista->nombre, nuevoDato);
			retorno = 0;
			break;
		case 2:
			strcpy(censista->apellido, nuevoDato);
			retorno = 0;
			break;
		case 3:
			if(strlen(nuevoDato)<=2 && validarEsInt(nuevoDato) == 0){
				nuevoDatoInt = atoi(nuevoDato);
				censista->fechaDeNacimiento.dia = nuevoDatoInt;
				retorno = 0;
			}
			break;
		case 4:
			if(strlen(nuevoDato)<=2 && validarEsInt(nuevoDato) == 0){
				nuevoDatoInt = atoi(nuevoDato);
				censista->fechaDeNacimiento.mes = nuevoDatoInt;
				retorno = 0;
			}
			break;
		case 5:
			if(strlen(nuevoDato)==4 && validarEsInt(nuevoDato) == 0){
				nuevoDatoInt = atoi(nuevoDato);
				censista->fechaDeNacimiento.anio = nuevoDatoInt;
				retorno = 0;
			}
			break;
		case 6:
			if(strlen(nuevoDato)<=2 && validarEsInt(nuevoDato) == 0){
				nuevoDatoInt = atoi(nuevoDato);
				censista->edad = nuevoDatoInt;
				retorno = 0;
			}
			break;
		case 7:
			strcpy(censista->censistaDireccion.calle, nuevoDato);
			retorno = 0;
			break;
		case 8:
			strcpy(censista->censistaDireccion.numero, nuevoDato);
			retorno = 0;
			break;
		case 9:
			break;
		}

	}

	return retorno;
}

//------------------------------------------------------------------------------------
// ------------------------------------ BUSQUEDA -------------------------------------
//------------------------------------------------------------------------------------

int buscarIndexLibre(Censista* list, int len, int * index){
	int retorno = -1;
	int indexLibre;
	int i;

	for (i=0; i<len; i++){
		if(list[i].isEmpty == 0){
			indexLibre = i;
			*index = indexLibre;
			retorno = 0;
			break;
		}
	}

	return retorno;
}

int buscarIndexCensistaPorId(Censista* list, int len, int id){
	int retorno = -1;

	if (list != NULL && len > 0 && id > -1) {

		for (int i = 0; i < len; i++) {
			if (list[i].id == id && list[i].isEmpty == FULL) {
				retorno = i;
				break;
			}
		}
	}

	return retorno;
}


//------------------------------------------------------------------------------------
// ------------------------------------ MOSTRAR -------------------------------------
//------------------------------------------------------------------------------------


int mostrarUnCensista(Censista censista){
	int retorno = -1;


	if(censista.isEmpty == FULL){
		printf("ID\t||\tNOMBRE\t||\tAPELLIDO\t||\tFECHA_DE_NACIMIENTO\t||\tEDAD\t||\tDIRECCION||\tESTADO||\tZONA\n");

		printf("%d", censista.id);
		printf("%20s", censista.nombre);
		printf("%20s", censista.apellido);
		printf("%20d/%d/%d", censista.fechaDeNacimiento.dia, censista.fechaDeNacimiento.mes, censista.fechaDeNacimiento.anio);
		printf("%20d", censista.edad);
		printf("%20s %s", censista.censistaDireccion.calle, censista.censistaDireccion.numero);
		printf("%10d", censista.estado);
		printf("%10d", censista.zonaAsignadaId);

		printf("\n");
		retorno = 0;
	}

	return retorno;
}


int mostrarCensistas(Censista* list, int len){
	int i;
	int retorno = -1;
	if(list != NULL && len > 0){
		printf("ID\t||\tNOMBRE\t||\tAPELLIDO\t||\tFECHA_DE_NACIMIENTO\t||\tEDAD\t||\tDIRECCION\t||\tESTADO\t||\tZONA\n");
		for(i=0; i<len; i++){
			if(list[i].isEmpty == FULL){
				printf("%d", list[i].id);
				printf("%20s", list[i].nombre);
				printf("%20s", list[i].apellido);
				printf("%20d/%d/%d", list[i].fechaDeNacimiento.dia, list[i].fechaDeNacimiento.mes, list[i].fechaDeNacimiento.anio);
				printf("%20d", list[i].edad);
				printf("%20s %s", list[i].censistaDireccion.calle, list[i].censistaDireccion.numero);
				printf("%10d", list[i].estado);
				printf("%10d", list[i].zonaAsignadaId);
				printf("\n");
			}
		}
		printf("\n\n");

		retorno = 0;
	}



	return retorno;
}

int hayCensistas(Censista* list, int len){
	int retorno = -1;
	int i;

	for (i=0; i<len; i++){
		if(list[i].isEmpty == FULL){
			retorno = 0;
			break;
		}
	}

	return retorno;
}



void hardcodearCensistas(Censista * list){

	list[0].id = 250;
	strcpy(list[0].nombre, "Andres");
	strcpy(list[0].apellido, "Almeida");
	strcpy(list[0].censistaDireccion.calle, "Santander");
	strcpy(list[0].censistaDireccion.numero, "1524");
	list[0].estado = LIBERADO;
	list[0].edad = 37;
	list[0].fechaDeNacimiento.dia = 24;
	list[0].fechaDeNacimiento.mes = 11;
	list[0].fechaDeNacimiento.anio = 1990;
	list[0].isEmpty = 1;


	list[1].id = 251;
	strcpy(list[1].nombre, "Pipe");
	strcpy(list[1].apellido, "Almeida");
	strcpy(list[1].censistaDireccion.calle, "Asamblea");
	strcpy(list[1].censistaDireccion.numero, "1237");
	list[1].estado = LIBERADO;
	list[1].edad = 22;
	list[1].fechaDeNacimiento.dia = 04;
	list[1].fechaDeNacimiento.mes = 02;
	list[1].fechaDeNacimiento.anio = 2000;
	list[1].isEmpty = 1;

	list[2].id = 252;
	strcpy(list[2].nombre, "Karina");
	strcpy(list[2].apellido, "Barreiro");
	strcpy(list[2].censistaDireccion.calle, "Colombres");
	strcpy(list[2].censistaDireccion.numero, "1479");
	list[2].estado = LIBERADO;
	list[2].edad = 30;
	list[2].fechaDeNacimiento.dia = 25;
	list[2].fechaDeNacimiento.mes = 03;
	list[2].fechaDeNacimiento.anio = 1992;
	list[2].isEmpty = 1;

	list[3].id = 253;
	strcpy(list[3].nombre, "Jorge");
	strcpy(list[3].apellido, "Barreiro");
	strcpy(list[3].censistaDireccion.calle, "Colombres");
	strcpy(list[3].censistaDireccion.numero, "1479");
	list[3].estado = LIBERADO;
	list[3].edad = 60;
	list[3].fechaDeNacimiento.dia = 01;
	list[3].fechaDeNacimiento.mes = 12;
	list[3].fechaDeNacimiento.anio = 1961;
	list[3].isEmpty = 1;

	list[4].id = 254;
	strcpy(list[4].nombre, "Gladys");
	strcpy(list[4].apellido, "Salucho");
	strcpy(list[4].censistaDireccion.calle, "Santander");
	strcpy(list[4].censistaDireccion.numero, "1340");
	list[4].estado = LIBERADO;
	list[4].edad = 61;
	list[4].fechaDeNacimiento.dia = 27;
	list[4].fechaDeNacimiento.mes = 07;
	list[4].fechaDeNacimiento.anio = 1960;
	list[4].isEmpty = 1;
}

