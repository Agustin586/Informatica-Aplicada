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

//Cada elemento de la lista
//typedef struct Nodo{
//	uint16_t frecuencia;
//	char letra;
//	struct Nodo *sgt;
//}TNodo;

//Lista de las estructuras enlazadas
//typedef struct LE{
//	TNodo *final;
//	TNodo *inicio;
//	int tam;
//}TLE_lista;

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

volatile uint8_t fin_programa = 0;

int main(void){
	srand(time(NULL));

	setbuf(stdout,0);

	int Estado_archivo,Estado_linea;

	//char prueba[]={'a','d','b','a','b','l'};

	TLE_lista *lista=CrearLista();		//Creamos la lista de los nodos
	Tarchivo_dato *psArchivo;			//pointer struct Archivo

	strcpy(psArchivo -> nombre_archivo,"datos.txt");

	//Incializacion de la lista
	Init_lista(lista);

	//Inserta el primer nodo
//	if(Insertar_en_ListaVacia(lista, prueba[0])==0); //Continua si fue bien creado
//
//	for(int i=1;i<CANT_CARACT;i++){
//		Insertar_en_FinLista(lista, lista -> final, prueba[i]);
//	}
//
//	Imprimir_Lista(lista);
//
//	Reordenar_Lista(lista);
//
//	printf("\n");
//	Imprimir_Lista(lista);

	//Inicializamos los estados con los procesos iniciales
	Init_estados(&Estado_archivo, &Estado_linea);

	//Bucle que se repite hasta leer todas las lineas
	while(1){
		if(!fin_programa)	Estados(&Estado_archivo,&Estado_linea,psArchivo,lista);
		else 				break;
	}

	return EXIT_SUCCESS;
}

void Init_estados(int *est_archivos,int *est_linea){

	*est_archivos = Generar_Archivo;
	*est_linea = Reposo_Linea;

	return;
}

void Estados(int *est_archivo,int *est_linea,Tarchivo_dato *archivo,TLE_lista *lista){
	switch(*est_archivo){
		//No se hace nada queda en vacío
		case Reposo_Archivo:{
			break;
		}
		case Generar_Archivo:{
			printf("Generamos el archivo aleatorio");
			Generar_archivo();

			*est_archivo = Total_Linea_Archivo;
			break;
		}
		//Esta no realiza nada --> la dejo para ver si puedo meter algo
		//sino la saco
		case Total_Linea_Archivo:{
			LeerLinea_archivo(archivo);

			*est_archivo = Procesar_Linea_Archivo;
			break;
		}
		case Procesar_Linea_Archivo:{
			Linea_archivo(archivo);

			*est_archivo = Reposo_Archivo;	//Espera que se procese la linea
			*est_linea = Procesar_Linea;	//Procesa la linea en otro estado dedica a eso
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
			break;
		}
		case Procesar_Linea:{
			Procesar_LineaArchivo(archivo,lista);

			*est_linea = Ordenar_Linea;
			break;
		}
		case Ordenar_Linea:{

			*est_linea = Mostrar_Linea;
			break;
		}
		case Mostrar_Linea:{

			if(archivo -> total_lineas != archivo -> lineas_procesadas){
				*est_linea = Reposo_Linea;				//Vuelve a esperar a que se lea la siguiente linea
				*est_archivo = Procesar_Linea_Archivo;	//Vuelve a procesarla
			}
			else{
				*est_archivo = Fin_Archivo;
			}
			//Debemos liberar la memoria --> Free
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

	free((sup_nodo -> frecuencia));
	free((sup_nodo -> letra));
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
	TNodo *actual,*intercambio,*t;
	int dA=0,dI=1;

	actual = lista->inicio;

<<<<<<< HEAD
<<<<<<< HEAD
	dA = 0;	//Distancia del nodo actual al inicio

	while(actual->sgt != NULL){
		intercambio = actual->sgt;
=======
=======
>>>>>>> parent of 9336bb9 (Programa finalizado)
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
>>>>>>> parent of 9336bb9 (Programa finalizado)

		dI = dA+1;	//Distancia del nodo actual al de intercambio
		if(dI>lista->tam)	dI = lista->tam;

		t = lista->inicio;
//		for(int i=0;i<dI;i++){
//			t = t->sgt;
//		}

		while(t->sgt != NULL){
			if((actual->frecuencia < intercambio->frecuencia)||((actual->frecuencia == intercambio->frecuencia)&&(actual->letra > intercambio->letra))){
				TNodo *p1=lista->inicio,*p2=lista->inicio,*p3=lista->inicio,*p4=lista->inicio;

				for(int i=0;i<dI+1;i++){
					if(i<dI-1)	p1 = p1->sgt;
					if(i<dI+1)	p2 = p2->sgt;
					if(i<dA-1)	p3 = p3->sgt;
					if(i<dA+1)	p4 = p4->sgt;
				}

				//Actual y Inicio+(dA+dI)+1
				if(p2 == lista->final)	actual->sgt=NULL,lista->final = actual;
				else	actual->sgt = p2;

				//Inicio+(dA+dI)-1 y Actual
				p1->sgt = actual;

				//Inicio+(dA)-1 y intercambio
				if(p3 == lista->inicio)	lista->inicio = intercambio;
				else	p3->sgt = intercambio;

				//Intercambio y Inicio+(dA)+1
				intercambio->sgt = p4;
			}
			intercambio = intercambio->sgt;
			t = t->sgt;
			dI++;
			if(dI>lista->tam)	dI = lista->tam;
		}
<<<<<<< HEAD
		actual = actual->sgt;
		intercambio = actual->sgt;
		dA++;
	}
=======
		actual = actual -> sgt;
		siguiente = actual -> sgt;
		}
<<<<<<< HEAD
>>>>>>> parent of 9336bb9 (Programa finalizado)

//	//Ordenamiento de frecuencias
//	while(actual -> sgt != NULL){
//		siguiente = actual -> sgt;
//
//		while(siguiente != NULL){
//			if((actual->frecuencia < siguiente->frecuencia)||
//			((actual->frecuencia == siguiente->frecuencia)&&(actual->letra> siguiente->letra))
//				){
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
=======
>>>>>>> parent of 9336bb9 (Programa finalizado)

	return;
}
