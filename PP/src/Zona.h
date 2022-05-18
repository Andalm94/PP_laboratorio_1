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
  char localidad[32];
  Calles callesDeZona;
  int estado;
  Censados censadosPorZona;
  int isEmpty;
} typedef Zona;


int inicializarZonas(Zona* list, int len);

int altaZona(Zona* list, int len, int id, char localidad[], char calle1[], char calle2[], char calle3[], char calle4[]);


int buscarIndexLibreZona(Zona* list, int len, int * index);

int buscarIndexZonaPorId(Zona* list, int len, int id);

int mostrarUnaZona(Zona zonaSeleccionada);

int mostrarZonas(Zona * list, int len);

int cargarDatos(Zona *zonaSeleccionada, int censadosInSitu, int censadosVirtuales, int censadosAusentes);

int hayZonas(Zona* list, int len);

#endif
