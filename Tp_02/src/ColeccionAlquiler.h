/*
 * ColeccionAlquiler.h
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#ifndef COLECCIONALQUILER_H_
#define COLECCIONALQUILER_H_

#include <stdint.h>
#include "Sombrillas.h"

class ColeccionAlquiler {
private:
	// vector <Sombrillas*> coleccion_sombrillas;
	//
	Sombrillas* p_somb[5];
	uint8_t cant_total;
public:
	ColeccionAlquiler();
	ColeccionAlquiler(uint8_t total);
	virtual ~ColeccionAlquiler();

	void ColeccionAlquiler::Insertar(const Sombrillas &somb_, bool especial) ;
	void ColeccionAlquiler::Eliminar(uint8_t id_, bool especial);
	float Total_Alquiler(uint8_t min_dias);

	uint8_t getCantTotal() const {
		return cant_total;
	}
};

#endif /* COLECCIONALQUILER_H_ */
