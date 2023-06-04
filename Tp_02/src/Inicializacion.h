#ifndef INICIALIZACION_H_
#define INICIALIZACION_H_

// Inclusiones
#include <iostream>
#include <conio.h>
#include "Sombrillas.h"
#include "SombrillasEspeciales.h"
#include "ColeccionAlquiler.h"

uint8_t Sombrillas::costo_fijo = 200;
uint8_t Sombrillas::costo_extra = 100;

/* Macros de utilidad */
#define CANT_MAX_DIAS_ALQUILER	30
#define CANT_MAX_ALQUILERES	50

/* Variables de uso en main */

//Incializaciones básicas
void vInit(void);

// Menu
typedef enum{
	VACIO,
	NUEVA_SOMBRILLA_NORMAL,
	NUEVA_SOMBRILLA_ESPECIAL,
	MOSTRAR_LISTA_TOTAL_SOMBRILLAS,
	BORRAR_SOMBRILLA,
	SALIR
}Menu_est;

typedef enum{
	ESPERA_SELECCION_MENU,
	MENU
}Progm_est;

void vInit_Progm (Progm_est *TProgm);
void vInit_Menu (Menu_est *TMenu);
void vProgm(Progm_est *TProgm,Menu_est *TMenu,ColeccionAlquiler &lista_);
void vMenu (Menu_est *TMenu,ColeccionAlquiler &lista_);

/* Variables y funciones realcionadas con la clase Sombrilla */
void vCrearSombrilla_Normal();

/* Variables y funciones realcionadas con la clase SombrillaEspecial */
void vCrearSombrilla_Especial();

/* Variables y funciones realcionadas con la clase ColeccionAlquiler */
uint8_t Cant_Actual_Alquileres = 0;
void vMostrar_ColeccionAlquileres();


#endif /* INICIALIZACION_H_ */

/*
 * Lista de variables:
 *
 * *pTMenu: utilizada para ubicar donde se encuentra el menu del usuario
 *
 * */
