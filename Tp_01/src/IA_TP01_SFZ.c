/*
 ============================================================================
 Name        : Tp_Info_AFZ.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Tp informatica
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CANT_LINEAS	2	//PARA PROBAR
#define CANT_CARACT 6

//Creamos los estados
typedef enum{
	Reposo_Archivo,
	Generar_Archivo,
	Cargar_Archivo,
	Procesar_Linea_Archivo
}Est_Archivos_t;

typedef enum{
	Reposo_Linea,
	Procesar_Linea,
	Ordenar_Linea,
	Mostrar_Linea
}Est_Linea_t;

//Cada elemento de la lista
typedef struct Nodo{
	uint16_t frecuencia;
	char letra;
	struct Nodo *sgt;
}TNodo;

//Lista de las estructuras enlazadas
typedef struct LE{
	TNodo *final;
	TNodo *inicio;
	int tam;
}TLE_lista;

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

//Reordenamos la lista
void Reordenar_Lista(TLE_lista *lista);

//Creamos una funcion que maneje los estados
void Estados(int *est_archivo,int *est_linea);

int main(void) {

	setbuf(stdout,0);
	int Estado_archivo=Generar_Archivo,Estado_linea=Reposo_Linea;

	char prueba[]={'a','d','b','a','b','l'};

	TLE_lista *lista=CrearLista();		//Creamos la lista de los nodos

	//Incializacion de la lista
	Init_lista(lista);

	//Inserta el primer nodo
	if(Insertar_en_ListaVacia(lista, prueba[0])==0); //Continua si fue bien creado

	for(int i=1;i<CANT_CARACT;i++){
		Insertar_en_FinLista(lista, lista -> final, prueba[i]);
	}

	Imprimir_Lista(lista);

	Reordenar_Lista(lista);

	printf("\n");
	Imprimir_Lista(lista);

//	while(1){
//		Estados(&Estado_archivo,&Estado_linea);
//	}

	return EXIT_SUCCESS;
}

void Estados(int *est_archivo,int *est_linea){
	switch(*est_archivo){
		case Reposo_Archivo:
		{
			break;
		}
		case Generar_Archivo:
		{
			*est_archivo = Cargar_Archivo;
		}
		case Cargar_Archivo:
		{
			//Condicion para que cambie
			*est_archivo = Procesar_Linea_Archivo;
		}
		case Procesar_Linea_Archivo:
		{
			*est_archivo = 0;
			//est_archivo = Procesar_Linea_Archivo;
			*est_linea = Procesar_Linea;
		}
		default: break;
	}
	switch(*est_linea){
		case Reposo_Linea:
		{
			break;
		}
		case Procesar_Linea:
		{
			*est_linea = Ordenar_Linea;
		}
		case Ordenar_Linea:
		{
			*est_linea = Mostrar_Linea;
		}
		case Mostrar_Linea:
		{
			*est_linea = Reposo_Linea;
			*est_archivo = Procesar_Linea_Archivo;
			//Debemos liberar la memoria --> Free
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

void Imprimir_Lista(TLE_lista *lista){
	TNodo *p=NULL;

	p=lista->inicio;

	//Recorremos de izquierda a derecha el puntero al siguiente nodo
	while(p!=NULL){
		printf("%c \t",p->letra);
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

	//Dado que solmente recorremos en un sentido hay que
	//movernos uno a la vez e ir comparando

	//Ordenamiento lexico
//	while(actual -> sgt != NULL){
//		siguiente = actual -> sgt;
//
//		while(siguiente != NULL){
//			if(actual -> letra > siguiente -> letra){
//				l = siguiente -> letra;
//				freq = siguiente -> frecuencia;
//
//				siguiente -> letra = actual -> letra;
//				siguiente -> frecuencia = actual -> frecuencia;
//
//				actual -> letra = l;
//				actual -> frecuencia = freq;
//			}
//			siguiente = siguiente -> sgt;
//		}
//		actual = actual -> sgt;
//		siguiente = actual -> sgt;
//	}

	printf("\n");
	Imprimir_Lista(lista);

	//Ordenamiento de frecuencias
	while(actual -> sgt != NULL){
		siguiente = actual -> sgt;

		while(siguiente != NULL){
			if(actual -> frecuencia > siguiente -> frecuencia){
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
