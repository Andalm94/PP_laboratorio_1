#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Censista.h"
#include "Zona.h"
#include "UTN.h"

#define PENDIENTE 0
#define FINALIZADO 1

#define EMPTY 0
#define FULL 1

int inicializarZonas(Zona* list, int len){
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

int altaZona(Zona* list, int len, int id, char localidad[], char calle1[], char calle2[], char calle3[], char calle4[]){
	int retorno = -1;

	int indexLibre = -1;


	if(buscarIndexLibreZona(list, len, &indexLibre) == 0){
		list[indexLibre].id = id;
		strcpy(list[indexLibre].localidad, localidad);
		strcpy(list[indexLibre].callesDeZona.calle1, calle1);
		strcpy(list[indexLibre].callesDeZona.calle2, calle2);
		strcpy(list[indexLibre].callesDeZona.calle3, calle3);
		strcpy(list[indexLibre].callesDeZona.calle4, calle4);
		list[indexLibre].censadosPorZona.censadosInSitu = 0;
		list[indexLibre].censadosPorZona.censadosVirtuales = 0;
		list[indexLibre].censadosPorZona.censadosAusentes = 0;
		list[indexLibre].estado = PENDIENTE;
		list[indexLibre].isEmpty = FULL;
		retorno = mostrarUnaZona(list[indexLibre]); //Si se carga exitosamente, en retorno se carga 0.
	}



	return retorno;
}

int bajaZona(Zona* list, int len, int id, char mensaje[]){
	int retorno = -1;
	int index;
	char respuesta;

	if(list != NULL && len>0){

		index = buscarIndexZonaPorId(list, len, id);
		if(index != -1 && mostrarUnaZona(list[index]) != -1 && getCharSiNo(mensaje, &respuesta, 1) == 0 && (respuesta == 'S' || respuesta =='s')){
			list[index].isEmpty = EMPTY;
			retorno = 0;
		}
	}

	return retorno;
}

int buscarIndexZonaPorId(Zona* list, int len, int id){
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


int buscarIndexLibreZona(Zona* list, int len, int * index){
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


int mostrarUnaZona(Zona zonaSeleccionada){
	int retorno = -1;


	if(zonaSeleccionada.isEmpty == FULL){
		printf("ID\t||\tLOCALIDAD\t||\tCALLES\t||\tESTADO\t||\tCENSADOS IN SITU\t||\tCENSADOS VIRTUALES||\tAUSENTES\n");

		printf("%d", zonaSeleccionada.id);
		printf("%s", zonaSeleccionada.localidad);
		printf("%s, %s, %s, %s", zonaSeleccionada.callesDeZona.calle1, zonaSeleccionada.callesDeZona.calle2, zonaSeleccionada.callesDeZona.calle3, zonaSeleccionada.callesDeZona.calle4);
		printf("%d", zonaSeleccionada.estado);
		printf("%20d", zonaSeleccionada.censadosPorZona.censadosInSitu);
		printf("%20d", zonaSeleccionada.censadosPorZona.censadosVirtuales);
		printf("%20d", zonaSeleccionada.censadosPorZona.censadosAusentes);

		printf("\n");
		retorno = 0;
	}

	return retorno;
}

int mostrarZonas(Zona * list, int len){
	int retorno = -1;
	int i;


	if(list != NULL && len > 0){
		printf("ID\t||\tLOCALIDAD\t||\tCALLES\t||\tESTADO\t||\tCENSADOS IN SITU\t||\tCENSADOS VIRTUALES||\tAUSENTES\n");
		for(i=0; i<len; i++){
			if(list[i].isEmpty == FULL){

				printf("%d", list[i].id);
				printf("%s", list[i].localidad);
				printf("%s, %s, %s, %s", list[i].callesDeZona.calle1, list[i].callesDeZona.calle2, list[i].callesDeZona.calle3, list[i].callesDeZona.calle4);
				printf("%d", list[i].estado);
				printf("%20d", list[i].censadosPorZona.censadosInSitu);
				printf("%20d", list[i].censadosPorZona.censadosVirtuales);
				printf("%20d", list[i].censadosPorZona.censadosAusentes);

				printf("\n");
				retorno = 0;
			}
		}
		printf("\n\n");
	}



	return retorno;

}

int cargarDatos(Zona *zonaSeleccionada, int censadosInSitu, int censadosVirtuales, int censadosAusentes){
	int retorno = -1;


	if(zonaSeleccionada->isEmpty == FULL && (censadosInSitu + censadosVirtuales + censadosAusentes) > 0){

		zonaSeleccionada->censadosPorZona.censadosInSitu = censadosInSitu;
		zonaSeleccionada->censadosPorZona.censadosVirtuales = censadosVirtuales;
		zonaSeleccionada->censadosPorZona.censadosAusentes = censadosAusentes;
		zonaSeleccionada->estado = FINALIZADO;

		retorno = 0;
	}


	return retorno;

}

int hayZonas(Zona* list, int len){
	int retorno = -1;
	int i;

	if(list != NULL && len > 0){
		for (i=0; i<len; i++){
			if(list[i].isEmpty == FULL)
			retorno = 0;
			break;
		}
	}

	return retorno;
}