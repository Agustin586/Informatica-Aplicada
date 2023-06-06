/*
 * ColeccionAlquiler.h
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#ifndef COLECCIONALQUILER_H_
#define COLECCIONALQUILER_H_

#include <cstdint>
#include <vector>
#include <algorithm>
#include "Sombrillas.h"

class ColeccionAlquiler {
private:
	vector <Sombrillas> Lista_Sombrillas;
	uint8_t cant_total;
	uint8_t usCantActual_Sombrillas=0;
public:
	ColeccionAlquiler();
	ColeccionAlquiler(uint8_t total_somb);	//Inicializa con la cantidad total de sombrillas
	virtual ~ColeccionAlquiler();

	void vInsertar(const Sombrillas &MSombrilla);
	void vEliminar(uint8_t id_, bool especial);
//	float fTotal_Alquiler(uint8_t min_dias);
	void vMostrar_Lista_Alquiler(void);

	uint8_t getCantTotal() const {
		return cant_total;
	}

	uint8_t getUsCantActualSombrillas() const {
		return usCantActual_Sombrillas;
	}

	void setUsCantActualSombrillas(uint8_t usCantActualSombrillas) {
		usCantActual_Sombrillas = usCantActualSombrillas;
	}
};

#endif /* COLECCIONALQUILER_H_ */
