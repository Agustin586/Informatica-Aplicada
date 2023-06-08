#ifndef INICIALIZACION_H_
#define INICIALIZACION_H_

// Inclusiones
#include <iostream>
#include <cstdint>
#include <conio.h>
#include "Sombrillas.h"
#include "SombrillasEspeciales.h"
#include "ColeccionAlquiler.h"

int Sombrillas::costo_fijo = 200;
int Sombrillas::costo_extra = 100;

/* Macros de utilidad */
#define CANT_MAX_DIAS_ALQUILER	30
#define CANT_MAX_ALQUILERES		50
#define CANT_SOMB_BASE_NORMAL	4
#define CANT_SOMB_BASE_ESPECIAL	6

/* Variables de uso en main */

//Incializaciones básicas
void vInit(void);

// Menu
typedef enum{
	VACIO,
	NUEVA_SOMBRILLA_NORMAL,
	NUEVA_SOMBRILLA_ESPECIAL,
	MOSTRAR_LISTA_TOTAL_SOMBRILLAS,
	COSTO_PLAZO_DIAS,
	BORRAR_SOMBRILLA,
	SALIR
}Menu_est;

typedef enum{
	ESPERA_SELECCION_MENU,
	MENU
}Progm_est;

void vInit_Progm (Progm_est *TProgm);
void vInit_Menu (Menu_est *TMenu);
void vProgm(Progm_est *TProgm,Menu_est *TMenu,ColeccionAlquiler &csLista_Sombrilla);
void vMenu (Menu_est *TMenu,ColeccionAlquiler &csLista_Sombrilla);

/* Variables y funciones relacionadas con la clase Sombrilla */
void vCrearSombrilla_Normal(ColeccionAlquiler &csLista_Sombrilla);

/* Variables y funciones realcionadas con la clase SombrillaEspecial */
void vCrearSombrilla_Especial(ColeccionAlquiler &csLista_Sombrilla);

/* Variables y funciones realcionadas con la clase ColeccionAlquiler */
int Cant_Actual_Alquileres = 0;
void vMostrar_ColeccionAlquileres();
bool bVerificar_Id_Somb(ColeccionAlquiler &csLista_Sombrilla,int id);



#endif /* INICIALIZACION_H_ */

/*
 * Lista de variables:
 *
 * *pTMenu: utilizada para ubicar donde se encuentra el menu del usuario
 *
 * */
