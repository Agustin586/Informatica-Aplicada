#ifndef MANEJO_ARCHIVOS_H
#define MANEJO_ARCHIVOS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define CANT_MAX_CARACTERES	96
#define RANGO_CARACTER_MIN	32
#define RANGO_CARACTER_MAX	128
#define RANGO_LINEA_MIN		1
#define RANGO_LINEA_MAX		20
#define RANGO_CANT_CARACTERES_MIN	0
#define RANGO_CANT_CARACTERES_MAX	100
#define REPETICION	100

typedef struct{
	FILE *archivo_;
	uint16_t total_lineas;
	uint16_t lineas_procesadas;
	int pos_final;
	char *nombre_archivo;
	char *linea_leida;
}Tarchivo_dato;

//Genera valores aleatorios
int Valor_aleatorio(int min,int max);

//Genera la cadena aleatoria
void Cadena_aleatoria(int longitud,char destino[]);

//Carga todo en el archivo
void Generar_archivo(void);

//Leemos el archivo linea por linea
void LeerLinea_archivo(Tarchivo_dato *archivo);
void Linea_archivo(Tarchivo_dato *archivo);

#endif //MANEJO_ARCHIVOS_H