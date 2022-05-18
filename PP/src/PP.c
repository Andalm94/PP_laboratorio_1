#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Censista.h"
#include "Zona.h"
#include "UTN.h"

//defines de censistas
#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3

//defines de zonas
#define PENDIENTE 0
#define FINALIZADO 1

#define MAX_CENSISTAS 1000
#define MAX_ZONAS 10000

int main(void) {
	setbuf(stdout, NULL);


	Censista censistas[MAX_CENSISTAS];
	int idCensista = 100;
	char nombreCensista[32];
	char apellidoCensista[32];
	int diaNacimientoCensista;
	int mesNacimientoCensista;
	int anioNacimientoCensista;
	int edadCensista;
	char localidadCencista[32];
	char calleCensista[32];
	char numeroCalleCensista[32];
	int estadoCensista;
	int zonaAsignadaCensista;

	Zona zonas[MAX_ZONAS];
	int idZona = 500;
	char localidadZona[32];
	char calle1Zona[32];
	char calle2Zona[32];
	char calle3Zona[32];
	char calle4Zona[32];
	int censadosInSituZona;
	int censadosVirtuales;
	int censadosAusentes;

	int auxiliarId;
	int idCensistaSeleccionado;
	int indexCensistaSeleccionado;
	int idZonaSeleccionada;
	int indexZonaSeleccionada;

	int censadosInSituCargados;
	int censadosVirtualesCargados;
	int censadosAusentesCargados;




	int opcionMenuPrincipal;
	int opcionMenuModificaciones;

	char nuevoDato[32];

	//HARDCOREO
	censistas[0].id = 250;
	strcpy(censistas[0].nombre, "Andres");
	strcpy(censistas[0].apellido, "Almeida");
	strcpy(censistas[0].censistaDireccion.calle, "Santander");
	strcpy(censistas[0].censistaDireccion.numero, "1524");
	strcpy(censistas[0].censistaDireccion.localidad, "CABA");
	censistas[0].edad = 37;
	censistas[0].fechaDeNacimiento.dia = 24;
	censistas[0].fechaDeNacimiento.mes = 11;
	censistas[0].fechaDeNacimiento.anio = 1990;
	censistas[0].isEmpty = 1;

	censistas[1].id = 251;
	strcpy(censistas[1].nombre, "Pipe");
	strcpy(censistas[1].apellido, "Almeida");
	strcpy(censistas[1].censistaDireccion.calle, "CalleFalsa");
	strcpy(censistas[1].censistaDireccion.numero, "123");
	strcpy(censistas[1].censistaDireccion.localidad, "Springfield");
	censistas[1].edad = 22;
	censistas[1].fechaDeNacimiento.dia = 04;
	censistas[1].fechaDeNacimiento.mes = 02;
	censistas[1].fechaDeNacimiento.anio = 2021;
	censistas[1].isEmpty = 1;

	strcpy(zonas[0].localidad, "CABA");
	strcpy(zonas[0].callesDeZona.calle1, "Beauchef");
	strcpy(zonas[0].callesDeZona.calle2, "Bilbao");
	strcpy(zonas[0].callesDeZona.calle3, "Estrada");
	strcpy(zonas[0].callesDeZona.calle4, "Sala");
	zonas[0].isEmpty = 1;
	zonas[0].id = 500;
	zonas[0].censistaId = 250;
	//-----------------------------


	printf("----------SISTEMA DE GESTION DE ZONAS Y CENSISTAS----------\n");
	do{
		printf("-----------------------MENU PRINCIPAL----------------------\n");
		printf("1) CARGAR CENSISTA\n");
		printf("2) MODIFICAR CENSISTA\n");
		printf("3) DAR BAJA A CENSISTA\n");
		printf("4) CARGAR ZONA\n");
		printf("5) ASIGNAR ZONA A CENSAR\n");
		printf("6) CARGA DE DATOS\n");
		printf("7) MOSTRAR CENSISTAS\n");
		printf("8) MOSTRAR ZONAS\n");
		printf("9) SALIR\n");

		if(getInt(&opcionMenuPrincipal, "Por favor, ingrese una opcion\n", "La opcion Ingresada no es valida, intente nuevamente\n", 1, 9, 3)==0){

			switch(opcionMenuPrincipal){
			case 1:
				if(getString("Por favor, ingrese el nombre del censista: \n", "Ha habido un error, intente nuevamente\n", nombreCensista, 32, 3) == 0 &&
					getString("Por favor, ingrese el apellido del censista: \n", "Ha habido un error, intente nuevamente\n", apellidoCensista, 32, 3) == 0 &&
					getInt(&diaNacimientoCensista, "Ingrese dia de nacimiento: \n", "Precio fuera de parametros, intente nuevamente \n", 1, 31, 3) == 0 &&
					getInt(&mesNacimientoCensista, "Ingrese mes de nacimiento: \n", "Precio fuera de parametros, intente nuevamente \n", 1, 12, 3) == 0 &&
					getInt(&anioNacimientoCensista, "Ingrese anio de nacimiento: \n", "Precio fuera de parametros, intente nuevamente \n", 1900, 2005, 3) == 0 &&
					getInt(&edadCensista, "Ingrese la edad del censista: \n", "Precio fuera de parametros, intente nuevamente \n", 18, 65, 3) == 0 &&
					getString("Ingrese la localidad donde reside el censista: \n", "Ha habido un error, intente nuevamente\n", localidadCencista, 32, 3) == 0 &&
					getString("Ingrese el nombre de la calle donde reside el censista: \n", "Ha habido un error, intente nuevamente\n", calleCensista, 32, 3) == 0 &&
					getString("Ingrese el numero de la calle donde reside el censista: \n", "Ha habido un error, intente nuevamente\n", numeroCalleCensista, 32, 3) == 0){

					if(altaCensista(censistas, MAX_CENSISTAS, idCensista, nombreCensista, apellidoCensista, diaNacimientoCensista,
							mesNacimientoCensista, anioNacimientoCensista, edadCensista, localidadCencista, calleCensista, numeroCalleCensista)==0){
						idCensista++;
					}
				}
				break;
			case 2:
				if(getInt(&idCensistaSeleccionado, "Ingrese el ID del censista\n", "\n", 100, MAX_CENSISTAS, 3)==0){
					indexCensistaSeleccionado = buscarIndexCensistaPorId(censistas, MAX_CENSISTAS, idCensistaSeleccionado);
					if(indexCensistaSeleccionado != -1){
						printf("------------------MODIFICAR CENSISTA-----------------\n");
						printf("1) NOMBRE\n");
						printf("2) APELLIDO\n");
						printf("3) DIA DE NACIMIENTO\n");
						printf("4) MES DE NACIMIENTO\n");
						printf("5) ANIO DE NACIMIENTO\n");
						printf("6) EDAD\n");
						printf("7) DIRECCION: CALLE\n");
						printf("8) DIRECCION: NUMERO\n");
						printf("9) DIRECCION: LOCALIDAD\n");
						printf("10) MENU ANTERIOR\n");
						mostrarUnCensista(censistas[indexCensistaSeleccionado]);
						if(getInt(&opcionMenuModificaciones, "Por favor, ingrese una opcion\n", "La opcion Ingresada no es valida, intente nuevamente\n", 1, 10, 3)==0 &&
								getString ("Ingrese el nuevo dato", "Error, intente nuevamente", nuevoDato, 32, 3) == 0 &&
								modificarCensista(&censistas[indexCensistaSeleccionado], nuevoDato, opcionMenuModificaciones) == 0){
								printf("Censista modificado\n");
								mostrarUnCensista(censistas[indexCensistaSeleccionado]);
						}
					}
				}


				break;
			case 3:
				if(hayCensistas(censistas, MAX_CENSISTAS) == 0 && mostrarCensistas(censistas, MAX_CENSISTAS) == 0 &&
						getInt(&auxiliarId, "Ingrese el ID del cencista que desea remover\n", "No existe el censista\n", 100, MAX_CENSISTAS, 3) == 0 &&
						bajaCensista(censistas, MAX_CENSISTAS, auxiliarId, "Desea eliminar este censista?\n") == 0){
					printf("Se ha liberado al censista satisfactoriamente.\n");
				}
				else{
					printf("Ha habido un error. Intente nuevamente\n");
				}
				break;
			case 4:
				if(getString("Por favor, el nombre de la localidad de la zona: \n", "Ha habido un error, intente nuevamente\n", localidadZona, 32, 3) == 0 &&
						getString("Indique la primer calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle1Zona, 32, 3) == 0 &&
						getString("Indique la segunda calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle2Zona, 32, 3) == 0 &&
						getString("Indique la tercera calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle3Zona, 32, 3) == 0 &&
						getString("Indique la cuarta calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle4Zona, 32, 3) == 0 &&
						altaZona(zonas, MAX_ZONAS, idZona, localidadZona, calle1Zona, calle2Zona, calle3Zona, calle4Zona) == 0){
					printf("Se ha dado de alta la zona satisfactoriamente\n");
				}

				break;
			case 5:
				if(getInt(&idCensistaSeleccionado, "Ingrese el ID del censista", "", 100, MAX_CENSISTAS, 3)==0){
					indexCensistaSeleccionado = buscarIndexCensistaPorId(censistas, MAX_CENSISTAS, idCensistaSeleccionado);
					if(indexCensistaSeleccionado != -1 &&
							censistas[indexCensistaSeleccionado].estado == LIBERADO &&
							getInt(&idZonaSeleccionada, "Ingrese el ID de la zona", "", 500, MAX_ZONAS, 3)==0){
						indexZonaSeleccionada = buscarIndexZonaPorId(zonas, MAX_ZONAS, idZonaSeleccionada);
						if(indexZonaSeleccionada != -1){
							censistas[indexCensistaSeleccionado].zonaAsignada = idZonaSeleccionada;
							censistas[indexCensistaSeleccionado].estado = ACTIVO;
							zonas[indexZonaSeleccionada].censistaId = censistas[indexCensistaSeleccionado].id;
							printf("Al cencista %s %s se le ha asignado la zona %d\n", censistas[indexCensistaSeleccionado].nombre, censistas[indexCensistaSeleccionado].apellido, censistas[indexCensistaSeleccionado].zonaAsignada);
							printf("Localidad: %s\n", zonas[indexZonaSeleccionada].localidad);
						}
					}
				}

				break;
			case 6:
				if(hayZonas(zonas, MAX_ZONAS) == 0 &&
						hayCensistas(censistas, MAX_CENSISTAS) == 0 &&
						getInt(&idZonaSeleccionada, "Ingrese el ID de la zona: \n", "\n", 0, 10000, 3) == 0){
					indexZonaSeleccionada = buscarIndexZonaPorId(zonas, MAX_ZONAS, idZonaSeleccionada);
					if(indexZonaSeleccionada != -1 &&
							getInt(&censadosInSituCargados, "Ingrese los censados in situ: \n", "\n", 0, 1000, 3) == 0 &&
							getInt(&censadosVirtualesCargados, "Ingrese los censados virtuales: \n", "\n", 0, 1000, 3) == 0 &&
							getInt(&censadosAusentesCargados, "Ingrese los ausentes: \n", "\n", 0, 1000, 3) == 0 &&
							cargarDatos(&zonas[indexZonaSeleccionada], censadosInSituCargados, censadosVirtualesCargados, censadosAusentesCargados) == 0){

						indexCensistaSeleccionado = buscarIndexCensistaPorId(censistas, MAX_CENSISTAS, zonas[indexZonaSeleccionada].censistaId);
						censistas[indexCensistaSeleccionado].estado = LIBERADO;
						printf("Censados cargados satisfactoriamente\n");
					}
					else{
						printf("Ha habido error. Intente nuevamente\n");
					}
				}
				else{
					printf("Ha habido error. Intende nuevamente\n");
				}

				break;
			case 7:
				if(hayCensistas(censistas, MAX_CENSISTAS) == 0 && mostrarCensistas(censistas, MAX_CENSISTAS) == 0){
					printf("Listado de censistas\n");
				}
				break;
			case 8:
				if(hayZonas(zonas, MAX_ZONAS)==0 && mostrarZonas(zonas, MAX_ZONAS) == 0){
					printf("Listado de zonas\n");
				}
				break;
			case 9:
				break;
			}
		}
	}while(opcionMenuPrincipal != 9);





	return EXIT_SUCCESS;
}