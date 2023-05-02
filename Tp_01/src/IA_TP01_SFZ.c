/*
 ============================================================================
 Name        : Tp_Info_AFZ.c
 Author      :
 Version     :
 Copyright   :
 Description : Tp informatica
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "Manejo_Archivos.h"

#define CANT_LINEAS	2	//PARA PROBAR
#define CANT_CARACT 6

//Creamos los estados
typedef enum{
	Reposo_Archivo,
	Generar_Archivo,
	Total_Linea_Archivo,
	Procesar_Linea_Archivo,
	Fin_Archivo
}Est_Archivos_t;

typedef enum{
	Reposo_Linea,
	Procesar_Linea,
	Ordenar_Linea,
	Mostrar_Linea
}Est_Linea_t;

//Inicialización de la lista
void Init_lista (TLE_lista * lista);

//Insertar en una lista vacía
int Insertar_en_ListaVacia(TLE_lista *lista, char dato);

//Inicio de la lista
int Insertar_en_FinLista(TLE_lista *lista,TNodo * actual,char dato);

//Mostrar lista enlazada
void Imprimir_Lista(TLE_lista *lista);

//Destruir lista enlazada
void Destruir_Lista(TLE_lista *lista);

//Creamos la lista
TLE_lista *CrearLista();

//Borar nodo al inicio
void Borrar_Nodo_Alinicio(TLE_lista *lista);

//Borar lista
void Destruir_Lista(TLE_lista *lista);

//Reordenamos la lista
void Reordenar_Lista(TLE_lista *lista);

//Creamos una funcion que maneje los estados
void Estados(int *est_archivo,int *est_linea,Tarchivo_dato *archivo,TLE_lista *lista);

//Inicializacion de los estados
void Init_estados(int *est_archivos,int *est_linea);
void Init_datoArchivo(Tarchivo_dato *archivo);

volatile uint8_t fin_programa = 0;

int main(void){
	srand(time(NULL));

	setbuf(stdout,0);

	int Estado_archivo,Estado_linea;
	TLE_lista *lista=CrearLista();				//Creamos la lista de los nodos
	Tarchivo_dato datos_archivo;
	Tarchivo_dato *psArchivo=&datos_archivo;	//pointer struct Archivo

	//Inicializamos los datos del archivo
	Init_datoArchivo(psArchivo);

	//Incializacion de la lista
	Init_lista(lista);

	//Inicializamos los estados con los procesos iniciales
	Init_estados(&Estado_archivo, &Estado_linea);

	//Bucle que se repite hasta leer todas las lineas
	while(1){
		if(fin_programa==0)		Estados(&Estado_archivo,&Estado_linea,psArchivo,lista);
		else if(fin_programa)	break;
	}

	return EXIT_SUCCESS;
}

void Init_datoArchivo(Tarchivo_dato *archivo){
	archivo->cont_cart = 0;
	archivo->lineas_procesadas = 0;
	archivo->nombre_archivo = "datos_aleatorios.txt";
	archivo->pos_final = 0;
	archivo->total_lineas = 0;

	return;
}

void Init_estados(int *est_archivos,int *est_linea){

	*est_archivos = Generar_Archivo;
	*est_linea = Reposo_Linea;

	return;
}

void Estados(int *est_archivo,int *est_linea,Tarchivo_dato *archivo,TLE_lista *lista){
	switch(*est_archivo){
		case Reposo_Archivo:{
			//Solamente espera
			break;
		}
		case Generar_Archivo:{
			//Generamos el archivo --> Solamente debe hacerse una vez por programa
			Generar_archivo(archivo);

			//Cambiamos de estado --> Leeremos la cantidad total de lineas
			*est_archivo = Total_Linea_Archivo;
			break;
		}
		case Total_Linea_Archivo:{
			//Leemos la cantidad de lineas del archivo e inicilizamos ciertos datos.
			CantidadTotal_Lineas_archivo(archivo);

			//Cambiamos de estado --> Procesaremos linea a linea hasta el final del archivo
			*est_archivo = Procesar_Linea_Archivo;
			break;
		}
		//Este estado deberá repetirse hasta que finalize la lectura completa del archivo
		case Procesar_Linea_Archivo:{
			//Leemos la linea solicitada y procesamos los datos correspondientes
			Linea_archivo(archivo);

			*est_archivo = Reposo_Archivo;	//Espera que se procese la linea
			*est_linea = Procesar_Linea;	//Procesa la linea en otro estado dedicado a eso
			break;
		}
		case Fin_Archivo:{
			fin_programa = 1;

			break;
		}
		default: break;
	}

	switch(*est_linea){
		case Reposo_Linea:{
			//Espera a que se tenga una linea para ser procesada
			break;
		}
		case Procesar_Linea:{
			//Leemos la linea almacenada en el puntero y luego procesamos la información
			Procesar_LineaArchivo(archivo,lista);

			//Cambiamos de estado --> Ordenamos según corresponda
			*est_linea = Ordenar_Linea;
			break;
		}
		case Ordenar_Linea:{
			Reordenar_Lista(lista);
			//Cambiamos de estado --> Mostramos por pantalla el resultado
			*est_linea = Mostrar_Linea;
			break;
		}
		case Mostrar_Linea:{
			Imprimir_Lista(lista);

			//Aca debemos liberar la memoria una vez que fue procesada la información
			free(archivo -> linea_leida);

			Destruir_Lista(lista);

			//Indica que ya proceso la linea seleccionada
			archivo -> lineas_procesadas++;

			if((archivo -> total_lineas)-1 != (archivo -> lineas_procesadas)) *est_archivo = Procesar_Linea_Archivo;
			else	*est_archivo = Fin_Archivo;

			*est_linea = Reposo_Linea;				//Vuelve a esperar a que se lea la siguiente linea
			break;
		}
		default: break;
	}

	return;
}


void Init_lista (TLE_lista * lista){
	lista -> inicio = NULL;
	lista -> final = NULL;
	lista -> tam = 0;
}


int Insertar_en_ListaVacia(TLE_lista *lista, char dato){
	TNodo *nodo;

	//Asigna memoria dinamica para el tipo nodo creado
	if ((nodo = (TNodo *) malloc (sizeof (TNodo))) == NULL)	return -1;

	//Cargamos los campos del nodo
	nodo -> letra = dato;	//Como adicional podriamos detectar si tiene la memoria suficiente para asignarlo.
	nodo -> frecuencia = 1;
	nodo -> sgt = NULL;

	lista -> inicio = nodo;
	lista -> final = nodo;
	lista -> tam = 1;

	return 0;
}

int Insertar_en_FinLista(TLE_lista *lista,TNodo * actual,char dato){
	TNodo *nodo;
	TNodo *p=NULL;

	uint8_t bandera=0;

	p=lista->inicio;

	//Deteta si existe una lista con esa letra
	while(p!=NULL){
		if(p->letra == dato){
			p -> frecuencia = p -> frecuencia + 1;
			bandera = 1;
			break;
		}
		p = p -> sgt;
	}

	//Si sale significa que no encontró una lista que contenga esa letra
	if(bandera != 1){
		//Asigna memoria dinamica para el tipo nodo creado
		if ((nodo = (TNodo *) malloc (sizeof (TNodo))) == NULL)	return -1;

		//Cargamos los campos en el primer nodo
		nodo -> letra = dato;
		nodo -> frecuencia = 1;

		//Modifica a donde apunta el nuevo nodo
		actual -> sgt = nodo;	//El nodo que ya estaba creado apunta al nuevo
		nodo -> sgt = NULL;		//El nuevo apunta a null

		//Modificamos la lista agregando elementos a la derecha
		lista -> final = nodo;
		lista -> tam++;
	}

	return 0;
}

void Borrar_Nodo_Alinicio(TLE_lista *lista){
	TNodo *sup_nodo;

	sup_nodo = lista -> inicio;
	lista -> inicio = lista -> inicio -> sgt;

	if(lista -> tam == 1)	lista -> final = NULL;

	free(sup_nodo);
	lista -> tam--;

	return;
}

void Destruir_Lista(TLE_lista *lista){
	while(lista -> tam > 0){
		Borrar_Nodo_Alinicio(lista);
	}
}

void Imprimir_Lista(TLE_lista *lista){
	TNodo *p=NULL;

	p=lista->inicio;

	printf("\n");
	//Recorremos de izquierda a derecha el puntero al siguiente nodo
	while(p!=NULL){
		printf("%c\t",p->letra);
		printf("%d\n",p->frecuencia);
		p = p -> sgt;
	}
}

TLE_lista *CrearLista(){
	TLE_lista *lista = (TLE_lista*)malloc(sizeof(TLE_lista));

	return lista;
}

void Reordenar_Lista(TLE_lista *lista){
	TNodo *actual,*siguiente;
	char l;
	int freq;

	actual = lista->inicio;

	//Ordenamiento de frecuencias
	while(actual -> sgt != NULL){
		siguiente = actual -> sgt;

		while(siguiente != NULL){
			if((actual->frecuencia < siguiente->frecuencia)||
			((actual->frecuencia == siguiente->frecuencia)&&(actual->letra> siguiente->letra))
				){
				l = siguiente -> letra;
				freq = siguiente -> frecuencia;

				siguiente -> letra = actual -> letra;
				siguiente -> frecuencia = actual -> frecuencia;

				actual -> letra = l;
				actual -> frecuencia = freq;
			}
			siguiente = siguiente -> sgt;
		}
		actual = actual -> sgt;
		siguiente = actual -> sgt;
	}

	return;
}
