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
			list[i].censistaId = -1;
		}
		retorno = 0;
	}

	return retorno;
}

int altaZona(Zona* list, int len, int id, int localidad, char calle1[], char calle2[], char calle3[], char calle4[]){
	int retorno = -1;

	int indexLibre = -1;


	if(buscarIndexLibreZona(list, len, &indexLibre) == 0){
		list[indexLibre].id = id;
		list[indexLibre].localidad = localidad;
		strcpy(list[indexLibre].callesDeZona.calle1, calle1);
		strcpy(list[indexLibre].callesDeZona.calle2, calle2);
		strcpy(list[indexLibre].callesDeZona.calle3, calle3);
		strcpy(list[indexLibre].callesDeZona.calle4, calle4);
		list[indexLibre].censadosPorZona.censadosInSitu = 0;
		list[indexLibre].censadosPorZona.censadosVirtuales = 0;
		list[indexLibre].censadosPorZona.censadosAusentes = 0;
		list[indexLibre].estado = PENDIENTE;
		list[indexLibre].isEmpty = FULL;
		retorno = 0;
	}



	return retorno;
}

int bajaZona(Zona* list, int len, int id, char mensaje[], char arrayLocalidades[][32]){
	int retorno = -1;
	int index;
	char respuesta;

	if(list != NULL && len>0){

		index = buscarIndexZonaPorId(list, len, id);
		if(index != -1 && mostrarUnaZona(list[index], arrayLocalidades) != -1 && getCharSiNo(mensaje, &respuesta, 1) == 0 && (respuesta == 'S' || respuesta =='s')){
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


int mostrarUnaZona(Zona zonaSeleccionada, char arrayLocalidades[][32]){
	int retorno = -1;


	if(zonaSeleccionada.isEmpty == FULL){
		printf("ID\t||\tLOCALIDAD\t||\tCALLES\t||\tESTADO\t||\tCENSADOS IN SITU\t||\tCENSADOS VIRTUALES||\tAUSENTES\n");

		printf("%-3d", zonaSeleccionada.id);
		printf("%20s", arrayLocalidades[zonaSeleccionada.localidad-1]);
		printf("%20s, %-10s, %-10s, %-15s", zonaSeleccionada.callesDeZona.calle1, zonaSeleccionada.callesDeZona.calle2, zonaSeleccionada.callesDeZona.calle3, zonaSeleccionada.callesDeZona.calle4);
		printf("%10d", zonaSeleccionada.estado);
		printf("%10d", zonaSeleccionada.censadosPorZona.censadosInSitu);
		printf("%10d", zonaSeleccionada.censadosPorZona.censadosVirtuales);
		printf("%10d", zonaSeleccionada.censadosPorZona.censadosAusentes);

		printf("\n");
		retorno = 0;
	}

	return retorno;
}

int mostrarZonas(Zona * list, int len,  char arrayLocalidades[][32]){
	int retorno = -1;
	int i;


	if(list != NULL && len > 0){

		printf("ID\t||\tLOCALIDAD\t||\t\tCALLES\t\t\t||\tESTADO\t||\tCENSADOS IN SITU\t||\tCENSADOS VIRTUALES||\tAUSENTES\n");
		for(i=0; i<len; i++){
			if(list[i].isEmpty == FULL){

				printf("%-3d", list[i].id);
				printf("%20s", arrayLocalidades[list[i].localidad-1]);
				printf("%20s, %-10s, %-10s, %-15s", list[i].callesDeZona.calle1, list[i].callesDeZona.calle2, list[i].callesDeZona.calle3, list[i].callesDeZona.calle4);
				printf("%10d", list[i].estado);
				printf("%10d", list[i].censadosPorZona.censadosInSitu);
				printf("%10d", list[i].censadosPorZona.censadosVirtuales);
				printf("%10d", list[i].censadosPorZona.censadosAusentes);

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

void hardcodearZonas(Zona* list){
	list[0].localidad = 1;
	strcpy(list[0].callesDeZona.calle1, "Colombres");
	strcpy(list[0].callesDeZona.calle2, "Boedo");
	strcpy(list[0].callesDeZona.calle3, "San Juan");
	strcpy(list[0].callesDeZona.calle4, "Independencia");
	list[0].isEmpty = 1;
	list[0].id = 500;
	list[0].censistaId = -1;

	list[1].localidad = 2;
	strcpy(list[1].callesDeZona.calle1, "Rivadavia");
	strcpy(list[1].callesDeZona.calle2, "Acoyte");
	strcpy(list[1].callesDeZona.calle3, "Yerbal");
	strcpy(list[1].callesDeZona.calle4, "Hidalgo");
	list[1].isEmpty = 1;
	list[1].id = 501;
	list[1].censistaId = -1;

	list[2].localidad = 3;
	strcpy(list[2].callesDeZona.calle1, "Carabobo");
	strcpy(list[2].callesDeZona.calle2, "Santander");
	strcpy(list[2].callesDeZona.calle3, "Avelino Diaz");
	strcpy(list[2].callesDeZona.calle4, "Pumacahua");
	list[2].isEmpty = 1;
	list[2].id = 502;
	list[2].censistaId = -1;

	list[3].localidad = 4;
	strcpy(list[3].callesDeZona.calle1, "Emilio Mitre");
	strcpy(list[3].callesDeZona.calle2, "Salas");
	strcpy(list[3].callesDeZona.calle3, "Estrada");
	strcpy(list[3].callesDeZona.calle4, "Cachimayo");
	list[3].isEmpty = 1;
	list[3].id = 503;
	list[3].censistaId = -1;


	list[4].localidad = 5;
	strcpy(list[4].callesDeZona.calle1, "Hipolito Yrigoyen");
	strcpy(list[4].callesDeZona.calle2, "Don Bosco");
	strcpy(list[4].callesDeZona.calle3, "Yapeyu");
	strcpy(list[4].callesDeZona.calle4, "Quintino Bocayuva");
	list[4].isEmpty = 1;
	list[4].id = 504;
	list[4].censistaId = -1;
}
