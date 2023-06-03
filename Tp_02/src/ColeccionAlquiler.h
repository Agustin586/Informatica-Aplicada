/*
 * ColeccionAlquiler.h
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#ifndef COLECCIONALQUILER_H_
#define COLECCIONALQUILER_H_

#include <stdint.h>
#include <vector>
#include <algorithm>
#include "Sombrillas.h"

class ColeccionAlquiler {
private:
	vector <Sombrillas> Lista_Sombrillas;
	uint8_t cant_total;
public:
	ColeccionAlquiler();
	ColeccionAlquiler(uint8_t total_somb);	//Inicializa con la cantidad total de sombrillas
	virtual ~ColeccionAlquiler();

	void vInsertar(const Sombrillas &MSombrilla, bool especial);
	void vEliminar(uint8_t id_, bool especial);
//	float fTotal_Alquiler(uint8_t min_dias);
	void vMostrar_Lista_Alquiler(void);

	uint8_t getCantTotal() const {
		return cant_total;
	}
};

#endif /* COLECCIONALQUILER_H_ */
