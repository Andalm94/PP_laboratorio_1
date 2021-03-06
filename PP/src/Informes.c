#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Censista.h"
#include "Zona.h"
#include "Informes.h"
#include "UTN.h"

#define PENDIENTE 0
#define FINALIZADO 1

#define EMPTY 0
#define FULL 1

#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3

int contarCensistasActivosPendientes(Censista* listaCensistas, int lenCensistas, Zona* listaZonas, int lenZonas, int* contadorCensistas){
	int retorno = -1;
	int i;
	int estadoZona;
	int contador = 0;
	int indexZona;

	if(listaCensistas != NULL && listaZonas != NULL && lenCensistas>0 && lenZonas > 0){

		retorno = 0;
		for (i=0; i<lenCensistas; i++){
			indexZona = buscarIndexZonaPorId(listaZonas, lenZonas, listaCensistas[i].id);
			estadoZona = listaZonas[indexZona].estado;

			if(listaCensistas[i].estado == ACTIVO && estadoZona == PENDIENTE){
				contador++;

			}
		}
		*contadorCensistas = contador;

	}




	return retorno;
}

int mostrarCensistasPorZona(){
	int retorno = -1;


	return retorno;
}

int buscarLocalidadConMasAusentes(Zona* listaZonas, int lenZonas, int* indexLocalidadesConMasAusentes, int cantidadLocalidades){
	int retorno = -1;
	int ausentesEnLocalidad = 0;
	int ausentesMax = 0;
	int indexLocalidadAusentesMax = -1;
	int i;
	int j;

	if(listaZonas != NULL && lenZonas > 0){
		retorno = 0;

		for(j=0; j<cantidadLocalidades; j++){

			for(i=0; i<lenZonas; i++){
				if(listaZonas[i].isEmpty == FULL && listaZonas[i].estado == FINALIZADO){
					ausentesEnLocalidad += listaZonas[i].censadosPorZona.censadosAusentes;

				}
			}



			if(ausentesEnLocalidad > ausentesMax){
				ausentesMax = ausentesEnLocalidad;
				indexLocalidadAusentesMax = j;
			}

		}


		*indexLocalidadesConMasAusentes = indexLocalidadAusentesMax;

	}

	return retorno;
}

int censistaConZonaMasCensada(Censista* listaCensistas, int lenCensistas, Zona* listaZonas, int lenZonas, int* indexCensista){
	int retorno = -1;

	int totalCensadosEnZona;
	int censadosMax = 0;
	int idZonaConMasCensados;

	int indexCensistaConZonaMasCensada = -1;


	int i;

	if(listaCensistas != NULL && listaZonas != NULL && lenCensistas>0 && lenZonas > 0){
		retorno = 0;

		//Busco el ID de la zona con mas censados en total
		for(i=0; i<lenZonas; i++){
			if(listaZonas[i].isEmpty == FULL && listaZonas[i].estado == FINALIZADO){
				totalCensadosEnZona = listaZonas[i].censadosPorZona.censadosInSitu + listaZonas[i].censadosPorZona.censadosVirtuales + listaZonas[i].censadosPorZona.censadosAusentes;

				if(totalCensadosEnZona > censadosMax){
					censadosMax = totalCensadosEnZona;
					idZonaConMasCensados = listaZonas[i].id;
				}
			}
		}


		//Con ese id, busco el index del censista
		indexCensistaConZonaMasCensada = buscarIndexCensistaPorId(listaCensistas, lenCensistas, idZonaConMasCensados);
		*indexCensista = indexCensistaConZonaMasCensada;

	}

	return retorno;
}

int promedioCensosPorCensistaYZona(Censista* listaCensistas, int lenCensistas, Zona* listaZonas, int lenZonas, int* promedio){
	int retorno = -1;


	if(listaCensistas != NULL && listaZonas != NULL && lenCensistas>0 && lenZonas > 0){

	}
	return retorno;
}
