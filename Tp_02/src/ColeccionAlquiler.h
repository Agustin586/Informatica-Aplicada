/*
 * ColeccionAlquiler.h
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#ifndef COLECCIONALQUILER_H_
#define COLECCIONALQUILER_H_

#define TIPO_SOMB_NORMAL	0
#define TIPO_SOMB_ESPECIAL	1

#include <cstdint>
#include <vector>
#include <algorithm>
#include "Sombrillas.h"

class ColeccionAlquiler {
private:
	vector <Sombrillas*> Lista_Sombrillas;	//Definimos un vector polimórfico
	int cant_total;							//Cantidad total de sombrillas
	int usCantActual_Sombrillas=0;			//Cantidad actual de sombrillas
public:
	ColeccionAlquiler();
	ColeccionAlquiler(int total_somb);	//Inicializa con la cantidad total de sombrillas
	virtual ~ColeccionAlquiler();

	void vInsertar(Sombrillas* MSombrilla);
	void vEliminar(int id_);
	float fTotalPlazo_Alquiler(int min_dias);
	void vMostrar_Lista_Alquiler(void);
	bool bVerificar_Id(int id_);

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
