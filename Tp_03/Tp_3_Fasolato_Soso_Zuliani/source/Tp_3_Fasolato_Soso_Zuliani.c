   /*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Tp_3_Fasolato_Soso_Zuliani.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "Inicializacion.h"
#include <stdbool.h>

/*
 * @brief   Application entry point.
 */
int main(void) {
	Mef_est TEstado;
	int iTemp,iDelay;
	bool bBandera;

	vInit();
	vMef_Init(&TEstado);

    while(1) {
    	vMef(&TEstado,&iTemp,&iDelay,&bBandera);
    }

    return 0 ;
}

void vInit(void) {
	/* Configuración de pines */
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;	// Activación del clock
	SIM->SCGC5 |= 1<<13;				// Selecciona el puerto E
	PORTE->PCR[29] |= (1<<8);			// Modo gpio
	PTE->PDDR |= 1<<29;					// Setea como salida el led rojo
	PTE->PSOR |= (1<<29);				// Limpia el pin antes de activarlo

	// Verde
	SIM->SCGC5 |= 1<<12;
	PORTD->PCR[5] |= 1<<8;
	PTD->PDDR |= 1<<5;
	PTD->PSOR |= 1<<5;

	// Pulsador 1
	SIM->SCGC5 |= (1<<11);
	PORTC->PCR[3] |= (1<<8);
	PTC->PDDR &= ~(1<<3);				// Configura como entrada
	PORTC->PCR[3] |= (1<<1);			// Habilita la resistencia pull up en PE
	PORTC->PCR[3] |= (1<<0);			// Selecciona la pull up

	// Pulsador 2
	PORTC->PCR[12] |= (1<<8);			// Modo gpio
	PTC->PDDR &= ~(1<<12);				// Configura como entrada
	PORTC->PCR[12] |= (1<<1);			// Habilita la resistencia pull up en PE
	PORTC->PCR[12] |= (1<<0);			// Selecciona la pull up

	return;
}

void vMef_Init(Mef_est* estado) {
	*estado = est_INIT;

	V_OFF			// Apaga led rojo
	ENABLE_OFF		// Apaga led verde

	return;
}

void vMef(Mef_est* estado,int* Temp,int* Delay,bool* Bandera1) {
	switch(*estado){
		case est_INIT:
		{
			(*Temp) = TEMP_MAX;	// Temporizador de velocidad
			*Bandera1 = false;
			(*Delay) = DELAY;	// Temporizador para rebote de pulsadores

			// Transición
			if(SENSOR1)	*estado = est_ENABLE_ON,ENABLE_ON;
			break;
		}
		case est_ENABLE_ON:
		{
			vEst_Sensor1(Temp,Delay,Bandera1);

			if(!(*Temp))	*estado = est_INIT,ENABLE_OFF;	// Si finaliza el temporizador
			if(SENSOR2) {
				*estado = est_INFRACCION;
				V_ON;
			}
			break;
		}
		case est_INFRACCION:
		{
			vAntirrebote(Delay,Bandera1);	// Espera un tiempo

			if(!SENSOR2 && (*Bandera1)){
				*estado = est_INIT;
				V_OFF;
				ENABLE_OFF;
			}

			break;
		}
		default:
		{
			break;
		}
	}

	return;
}

void vEst_Sensor1(int* Temp,int* Delay,bool* Bandera) {
	if(*Temp != 0) {
		(*Temp)--;
	}

	return;
}

void vAntirrebote(int* Delay,bool* Bandera) {
	if((*Delay) != 0 && !(*Bandera))	(*Delay)--;
	else {
		(*Bandera) = true;
	}

	return;
}
