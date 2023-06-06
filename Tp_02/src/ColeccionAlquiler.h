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
	vector <Sombrillas> *Lista_Sombrillas;
	int cant_total;
	int usCantActual_Sombrillas=0;
public:
	ColeccionAlquiler();
	ColeccionAlquiler(int total_somb);	//Inicializa con la cantidad total de sombrillas
	virtual ~ColeccionAlquiler();

	void vInsertar(const Sombrillas &MSombrilla);
	void vEliminar(int id_, bool especial);
//	float fTotal_Alquiler(int min_dias);
	void vMostrar_Lista_Alquiler(void);

	int getCantTotal() const {
		return cant_total;
	}

	int getUsCantActualSombrillas() const {
		return usCantActual_Sombrillas;
	}

	void setUsCantActualSombrillas(int usCantActualSombrillas) {
		usCantActual_Sombrillas = usCantActualSombrillas;
	}
};

#endif /* COLECCIONALQUILER_H_ */
