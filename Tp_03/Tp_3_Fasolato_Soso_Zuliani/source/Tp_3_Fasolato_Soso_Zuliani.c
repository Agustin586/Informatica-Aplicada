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

	SIM->SCGC5 |= (1<<11);
	PORTC->PCR[3] |= (1<<8);
	PTC->PDDR &= ~(1<<3);				// Configura como entrada
	PORTC->PCR[3] |= (1<<1);			// Habilita la resistencia pull up en PE
	PORTC->PCR[3] |= (1<<0);			// Selecciona la pull up

	return;
}

void vMef_Init(Mef_est* estado) {
	*estado = est_INIT;

	return;
}

void vMef(Mef_est* estado,int* Temp,int* Delay,bool* Bandera1) {
	switch(*estado){
		case est_INIT:
		{
			V_OFF
			(*Temp) = TEMP_MAX;
			*Bandera1 = false;
			(*Delay) = DELAY;

			if(SENSOR)	*estado = est_SENSOR1;
			break;
		}
		case est_SENSOR1:
		{
			vEst_Sensor1(Temp,Delay,Bandera1);

			if((*Bandera1) && SENSOR) {
				*estado = est_SENSOR2;
				(*Bandera1) = !(*Bandera1);
				(*Delay) = DELAY;
			}
			break;
		}
		case est_SENSOR2:
		{
			vEst_Sensor2(Temp,Delay,Bandera1);

			if(!SENSOR) *estado = est_INIT,!(*Bandera1);
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
	else {
		V_TOGGLE
	}

	vAntirrebote(Delay,Bandera);

	return;
}

void vEst_Sensor2(int* Temp,int* Delay,bool* Bandera) {
	if((*Temp) > T_MIN) {
		V_ON
	}
	else {
		V_OFF
	}

	vAntirrebote(Delay,Bandera);

	return;
}

void vAntirrebote(int* Delay,bool* Bandera) {
	if((*Delay) != 0 && !(*Bandera))	(*Delay)--;
	else {
		(*Bandera) = !(*Bandera);
	}

	return;
}
