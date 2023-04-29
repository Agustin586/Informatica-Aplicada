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
#define RANGO_LINEA_MAX		10
#define RANGO_CANT_CARACTERES_MIN	0
#define RANGO_CANT_CARACTERES_MAX	20
#define REPETICION	100

typedef struct{
	FILE *archivo_;
	uint16_t total_lineas;
	uint16_t lineas_procesadas;
	int pos_final;
	char *nombre_archivo;
	char *linea_leida;
	uint16_t cont_cart;
}Tarchivo_dato;

typedef struct Nodo{
	uint16_t frecuencia;
	char letra;
	struct Nodo *sgt;
}TNodo;

typedef struct LE{
	TNodo *final;
	TNodo *inicio;
	int tam;
}TLE_lista;

//Genera valores aleatorios
int Valor_aleatorio(int min,int max);

//Genera la cadena aleatoria
void Cadena_aleatoria(int longitud,char destino[]);

//Carga todo en el archivo
void Generar_archivo(void);

//Leemos el archivo linea por linea
void LeerLinea_archivo(Tarchivo_dato *archivo);
void Linea_archivo(Tarchivo_dato *archivo);

//Procesar la linea leida
void Procesar_LineaArchivo(Tarchivo_dato *archivo,TLE_lista *lista);

void Imprimir_Lista(TLE_lista *lista);
void Destruir_Lista(TLE_lista *lista);
int Insertar_en_ListaVacia(TLE_lista *lista, char dato);
int Insertar_en_FinLista(TLE_lista *lista,TNodo * actual,char dato);

#endif //MANEJO_ARCHIVOS_H