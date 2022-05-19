#ifndef INFORMES_H_
#define INFORMES_H_


int contarCensistasActivosPendientes(Censista* listaCensistas, int lenCensistas, Zona* listaZonas, int lenZonas, int* contadorCensistas);

int mostrarCensistasPorZona();

int buscarLocalidadConMasAusentes(Zona* listaZonas, int lenZonas, int* indexLocalidadesConMasAusentes, int cantidadLocalidades);

int censistaConZonaMasCensada(Censista* listaCensistas, int lenCensistas, Zona* listaZonas, int lenZonas, int* indexCensista);

int promedioCensosPorCensistaYZona(Censista* listaCensistas, int lenCensistas, Zona* listaZonas, int lenZonas, int* promedio);


#endif
