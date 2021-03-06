#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Censista.h"
#include "Zona.h"
#include "Informes.h"
#include "UTN.h"

//defines de censistas
#define ACTIVO 1
#define INACTIVO 2
#define LIBERADO 3

//defines de zonas
#define PENDIENTE 0
#define FINALIZADO 1

#define MAX_CENSISTAS 1000
#define MAX_ZONAS 1000

int main(void) {
	setbuf(stdout, NULL);


	//Variables para la carga de censistas
	Censista censistas[MAX_CENSISTAS];
	int idCensista = 100;
	char nombreCensista[32];
	char apellidoCensista[32];
	int diaNacimientoCensista;
	int mesNacimientoCensista;
	int anioNacimientoCensista;
	int edadCensista;
	char calleCensista[32];
	char numeroCalleCensista[32];


	//Variables para la carga de zonas
	Zona zonas[MAX_ZONAS];
	int idZona = 500;
	int localidadZona;
	char calle1Zona[32];
	char calle2Zona[32];
	char calle3Zona[32];
	char calle4Zona[32];


	//Variables utilizadas para seleccionar y encontrar zonas y/o censistas
	int idCensistaSeleccionado;
	int indexCensistaSeleccionado;
	int idZonaSeleccionada;
	int indexZonaSeleccionada;


	//Variable donde se cargan los nuevos datos a modificar
	char nuevoDato[32];


	//Variables utilizadas para realizar la carga de datos de una zona
	int censadosInSituCargados;
	int censadosVirtualesCargados;
	int censadosAusentesCargados;


	//Opciones de los menus
	int opcionMenuPrincipal;
	int opcionMenuModificaciones;
	int opcionMenuInformes;

	//Localidades
	char localidades[5][32] = {"BOEDO", "CABALLITO", "FLORES", "PARQUE CHACABUCO", "ALMAGRO"};


	//Variables utilizadas para informes
	int contadorCensistasActivosConZonaPendiente;
	int indexLocalidadConMasAusentes;
	int indexCensistaConZonaMasCensada;


	hardcodearCensistas(censistas);
	hardcodearZonas(zonas);


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
		printf("9) MENU INFORMES\n");
		printf("10) SALIR\n");

		if(getInt(&opcionMenuPrincipal, "Por favor, ingrese una opcion\n", "La opcion Ingresada no es valida, intente nuevamente\n", 1, 10, 3)==0){
			switch(opcionMenuPrincipal){


			case 1://---------------------ALTA CENSISTA-----------------------------
				//**Se silicitan los datos necesarios para dar el alta. Se valida que no hayan habido errores en la carga.
				//**En caso de no haber errores, se da el alta, se muestra al censista nuevo y se aumenta en 1 la variable idCensista
				if(getString("Por favor, ingrese el nombre del censista: \n", "Ha habido un error, intente nuevamente\n", nombreCensista, 32, 3) == 0 &&
					getString("Por favor, ingrese el apellido del censista: \n", "Ha habido un error, intente nuevamente\n", apellidoCensista, 32, 3) == 0 &&
					getInt(&diaNacimientoCensista, "Ingrese dia de nacimiento: \n", "Fuera de parametros, intente nuevamente \n", 1, 31, 3) == 0 &&
					getInt(&mesNacimientoCensista, "Ingrese mes de nacimiento: \n", "Fuera de parametros, intente nuevamente \n", 1, 12, 3) == 0 &&
					getInt(&anioNacimientoCensista, "Ingrese anio de nacimiento: \n", "Fuera de parametros, intente nuevamente \n", 1900, 2005, 3) == 0 &&
					getInt(&edadCensista, "Ingrese la edad del censista: \n", "Fuera de parametros, intente nuevamente \n", 18, 100, 3) == 0 &&
					getString("Ingrese el nombre de la calle donde reside el censista: \n", "Ha habido un error, intente nuevamente\n", calleCensista, 32, 3) == 0 &&
					getString("Ingrese el numero de la calle donde reside el censista: \n", "Ha habido un error, intente nuevamente\n", numeroCalleCensista, 32, 3) == 0){

					if(altaCensista(censistas, MAX_CENSISTAS, idCensista, nombreCensista, apellidoCensista, diaNacimientoCensista,
							mesNacimientoCensista, anioNacimientoCensista, edadCensista,  calleCensista, numeroCalleCensista)==0){
						indexCensistaSeleccionado = buscarIndexCensistaPorId(censistas, MAX_CENSISTAS, idCensista);
						mostrarUnCensista(censistas[indexCensistaSeleccionado]);
						idCensista++;
					}
				}
				break;


			case 2://---------------------MODIFICAR CENSISTA-----------------------------
				//**Se valida que hayan censistas y se solicita un ID. Se valida si existe un censista con ese ID
				//**En caso de que exista el censista, se solicita que campo se desea modificar
				//**Se solicita que se cargue el nuevo dato en la variable nuevoDato
				//**El nuevo dato se valida en la funcion modificarCensista, que recibe como parametro solo el censista a modificar (no el array entero)
				//**Se carga el dato nuevo en el campo correspondiente y se muestra al censista
				if(hayCensistas(censistas, MAX_CENSISTAS) == 0 && getInt(&idCensistaSeleccionado, "Ingrese el ID del censista\n", "\n", 100, MAX_CENSISTAS, 3)==0){
					indexCensistaSeleccionado = buscarIndexCensistaPorId(censistas, MAX_CENSISTAS, idCensistaSeleccionado);

					if(indexCensistaSeleccionado != -1){

						mostrarUnCensista(censistas[indexCensistaSeleccionado]);
						do{
							printf("------------------MODIFICAR CENSISTA-----------------\n");
							printf("1) NOMBRE\n");
							printf("2) APELLIDO\n");
							printf("3) DIA DE NACIMIENTO\n");
							printf("4) MES DE NACIMIENTO\n");
							printf("5) ANIO DE NACIMIENTO\n");
							printf("6) EDAD\n");
							printf("7) DIRECCION: CALLE\n");
							printf("8) DIRECCION: NUMERO\n");
							printf("9) MENU ANTERIOR\n");
							if(getInt(&opcionMenuModificaciones, "Por favor, ingrese una opcion\n", "La opcion Ingresada no es valida, intente nuevamente\n", 1, 9, 3)==0 &&
									getString ("Ingrese el nuevo dato:  ", "Error, intente nuevamente\n", nuevoDato, 32, 3) == 0 &&
									modificarCensista(&censistas[indexCensistaSeleccionado], nuevoDato, opcionMenuModificaciones) == 0){
									printf("Censista modificado\n");
									mostrarUnCensista(censistas[indexCensistaSeleccionado]);
							}
						}while(opcionMenuModificaciones!=9);
					}
				}
				break;



			case 3://---------------------BAJA CENSISTA-----------------------------
				//**Valida que hayan censistas y muestra la lista
				//**Se solicita el ID de un censista. En la funcion bajaCensista se valida que sea un ID existente y se realiza una pregunta de confirmacion
				//**Si el usuario responde 'S' o 's' se da de baja al censista.
				//**Si no tiene zonas asignadas--> censistas.isEmpty = EMPTY // Si tiene zonas asignadas--> censistas.estado = INACTIVO
				if(hayCensistas(censistas, MAX_CENSISTAS) == 0 && mostrarCensistas(censistas, MAX_CENSISTAS) == 0 &&
						getInt(&idCensistaSeleccionado, "Ingrese el ID del cencista que desea remover\n", "No existe el censista\n", 100, MAX_CENSISTAS, 3) == 0 &&
						bajaCensista(censistas, MAX_CENSISTAS, idCensistaSeleccionado, "Desea eliminar este censista?\n") == 0){
					printf("Se ha liberado al censista satisfactoriamente.\n");
				}
				else{
					printf("Ha habido un error. Intente nuevamente\n");
				}
				break;



			case 4://---------------------ALTA ZONA-----------------------------
				//**Se silicitan los datos necesarios para dar el alta. Se valida que no hayan habido errores en la carga.
				//**En caso de no haber errores, se da el alta de la zona
				if(getInt(&localidadZona, "Ingrese la localidad:\n1)BOEDO\n2)CABALLITO\n3)FLORES\n4)PARQUE CHACABUCO\n5)ALMAGRO",
								"Fuera de parametros, intente nuevamente \n", 1, 5, 3) == 0 &&
						getString("Indique la primer calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle1Zona, 32, 3) == 0 &&
						getString("Indique la segunda calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle2Zona, 32, 3) == 0 &&
						getString("Indique la tercera calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle3Zona, 32, 3) == 0 &&
						getString("Indique la cuarta calle que compone la zona: \n", "Ha habido un error, intente nuevamente\n", calle4Zona, 32, 3) == 0 &&
						altaZona(zonas, MAX_ZONAS, idZona, localidadZona, calle1Zona, calle2Zona, calle3Zona, calle4Zona) == 0){
					printf("Se ha dado de alta la zona satisfactoriamente\n");
				}

				break;



			case 5://---------------------ASIGNAR CENSISTA A ZONA-----------------------------
				//**Se valida que se hayan cargado zonas y censistas. Luego se solicita el ID de un censista y de una zona
				//**Se valida que el censista exista y este liberado
				//**Se valida que la zona exista y no este finalizada
				//**En censistas:
				//***Se asigna a zonaAsignada el ID de la zona
				//***Se cambia su estado a ACTIVO
				//**En zonas:
				//***Se asigna a censistaId el ID del censista asignado
				//***Se cambia su estado a PENDIENTE
				if(hayCensistas(censistas, MAX_CENSISTAS) == 0 && hayZonas(zonas, MAX_ZONAS) == 0 &&
						getInt(&idCensistaSeleccionado, "Ingrese el ID del censista", "", 100, MAX_CENSISTAS, 3)==0){
					indexCensistaSeleccionado = buscarIndexCensistaPorId(censistas, MAX_CENSISTAS, idCensistaSeleccionado);
					if(indexCensistaSeleccionado != -1 &&
							censistas[indexCensistaSeleccionado].estado == LIBERADO &&
							getInt(&idZonaSeleccionada, "Ingrese el ID de la zona", "", 500, MAX_ZONAS, 3)==0){
						indexZonaSeleccionada = buscarIndexZonaPorId(zonas, MAX_ZONAS, idZonaSeleccionada);
						if(indexZonaSeleccionada != -1 && zonas[indexZonaSeleccionada].estado != FINALIZADO){
							censistas[indexCensistaSeleccionado].zonaAsignadaId = idZonaSeleccionada;
							censistas[indexCensistaSeleccionado].estado = ACTIVO;
							zonas[indexZonaSeleccionada].censistaId = censistas[indexCensistaSeleccionado].id;
							zonas[indexZonaSeleccionada].estado = PENDIENTE;
							printf("Al cencista %s %s se le ha asignado la zona %d\n", censistas[indexCensistaSeleccionado].nombre, censistas[indexCensistaSeleccionado].apellido, censistas[indexCensistaSeleccionado].zonaAsignadaId);
							printf("Localidad: %s\n", localidades[zonas[indexZonaSeleccionada].localidad-1]);
						}
					}
				}

				break;



			case 6://---------------------CARGA DE DATOS-----------------------------
				//**Se valida que hayan zonas cargadas y censistas cargados y se solicita el ID de una zona.
				//**Se valida que la zona exista y que tenga un censista asignado
				//**Se solicita la cantidad de censados InSitu, virtuales y ausentes de esa zona
				//***Si los datos cargados se validan correctamente:
				//****La zona cambia su estado a FINALIZADO
				//****El censista cambia su estado a LIBERADO
				if(hayZonas(zonas, MAX_ZONAS) == 0 && hayCensistas(censistas, MAX_CENSISTAS) == 0 &&
						getInt(&idZonaSeleccionada, "Ingrese el ID de la zona: \n", "\n", 0, 10000, 3) == 0){
					indexZonaSeleccionada = buscarIndexZonaPorId(zonas, MAX_ZONAS, idZonaSeleccionada);
					if(indexZonaSeleccionada != -1 && zonas[indexZonaSeleccionada].censistaId != -1 &&
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


			case 7://---------------------MOSTRAR CENSISTAS-----------------------------
				//**Valida que se hayan cargado censistas. Si hay censistas cargados los muestra
				if(hayCensistas(censistas, MAX_CENSISTAS) == 0 && mostrarCensistas(censistas, MAX_CENSISTAS) == 0){
					printf("Listado de censistas\n");
				}
				else{
					printf("Aun no se han cargado censistas\n");
				}
				break;


			case 8://---------------------MOSTRAR ZONAS-----------------------------
				//**Valida que se hayan cargado zonas. Si hay zonas cargadas las muestra
				if(hayZonas(zonas, MAX_ZONAS)==0 && mostrarZonas(zonas, MAX_ZONAS, localidades) == 0){
					printf("Listado de zonas\n");
				}
				break;


			case 9://---------------------MENU INFORMES-----------------------------
				if(hayCensistas(censistas, MAX_CENSISTAS) == 0 && hayZonas(zonas, MAX_ZONAS)==0){
					do{
						printf("------------------MENU INFORMES-----------------\n");
						printf("1) CENSISTAS ACTIVOS CON ZONAS PENDIENTES\n");
						printf("2) CENSITAS POR ZONA\n");
						printf("3) LOCALIDAD CON MAS AUSENTES\n");
						printf("4) CENSISTA CON ZONA MAS CENSADA\n");
						printf("5) PROMEDIO DE CENSOS POR CENSISTA Y ZONA\n");
						printf("6) MENU ANTERIOR\n");
						if(getInt(&opcionMenuInformes, "Por favor, ingrese una opcion\n", "La opcion Ingresada no es valida, intente nuevamente\n", 1, 6, 3)==0){

							switch(opcionMenuInformes){
							case 1:
								if(contarCensistasActivosPendientes(censistas, MAX_CENSISTAS, zonas, MAX_ZONAS, &contadorCensistasActivosConZonaPendiente)==0){
									printf("CENSISTAS ACTIVOS CON ZONAS PENDIENTES: %d\n", contadorCensistasActivosConZonaPendiente);
								}
								break;
							case 2:
								break;
							case 3:
								if(buscarLocalidadConMasAusentes(zonas, MAX_ZONAS, &indexLocalidadConMasAusentes, 5) == 0){
									if(indexLocalidadConMasAusentes != -1){
										printf("LOCALIDAD CON MAS AUSENTES: %s\n", localidades[indexLocalidadConMasAusentes]);
									}
									else{
										printf("Aun no se han cargado datos suficientes.\n");
									}
								}
								break;
							case 4:
								if(censistaConZonaMasCensada(censistas, MAX_CENSISTAS, zonas, MAX_ZONAS, &indexCensistaConZonaMasCensada) == 0){
									if(indexCensistaConZonaMasCensada != -1){
										printf("El censista con la zona mas censada es %s %s \n", censistas[indexCensistaConZonaMasCensada].nombre, censistas[indexCensistaConZonaMasCensada].apellido);
									}
									else{
										printf("Aun no se han cargado datos suficientes.\n");
									}

								}
								break;
							case 5:
								break;
							case 6:
								break;

							}
						}
					}while(opcionMenuInformes!=6);

			}
			break;


			case 10://---------------------SALIR-----------------------------
				break;

			}

		}
	}while(opcionMenuPrincipal != 10);





	return EXIT_SUCCESS;
}
