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
 * @file    Led_Timer_int.c
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

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

#include "MKL46Z4.h"

void delay(uint32_t milliseconds) {
    uint32_t count = milliseconds * 1000;

    while (count != 0) {
        count--;
    }
}

void TPM0_IRQHandler(void) {
    if (TPM0->STATUS & TPM_STATUS_TOF_MASK) {  // Verifica si la interrupción fue causada por el desbordamiento del temporizador
        TPM0->STATUS |= TPM_STATUS_TOF_MASK;  // Limpia el flag de desbordamiento del temporizador
        PTE->PTOR = (1 << 29);  // Invierte el estado del PIN18 del PORTB (LED rojo)
    }
}

int main(void) {
	SIM->SCGC5 |= 1<<13;  // Habilita el reloj para el PORTB
    SIM->SCGC6 |= (1 << 24);  // Habilita el reloj para el TPM0
    PORTE->PCR[29] |= (1<<8);  // Configura el PIN18 del PORTB como salida

    TPM0->SC = 0;  // Detiene el temporizador
    TPM0->CNT = 0;  // Reinicia el contador del temporizador
    TPM0->MOD = 32768;  // Establece el valor de desbordamiento para generar una interrupción cada 1 segundo
    TPM0->SC = TPM_SC_TOIE_MASK | TPM_SC_CMOD(1);  // Habilita la interrupción por desbordamiento y comienza el temporizador

    NVIC_EnableIRQ(TPM0_IRQn);  // Habilita la interrupción del TPM0

    while (1) {
        // El programa se ejecutará principalmente en la interrupción, por lo que no hay necesidad de hacer nada aquí.
    }
}
