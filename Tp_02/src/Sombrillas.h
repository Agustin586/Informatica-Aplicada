/*
 * Sombrillas.h
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#ifndef SOMBRILLAS_H_
#define SOMBRILLAS_H_

#include <iostream>
#include <stdint.h>
#include <stdbool.h>

using namespace std;

class Sombrillas {
private:
	uint8_t dias;
	bool estacionamiento;
	uint8_t id;
public:
	static uint8_t cant_ocupada;
	static uint8_t costo_fijo;
	static uint8_t costo_extra;
	//Construtuctor
	Sombrillas();
	Sombrillas(uint8_t dias_,bool est,uint8_t id_);
	virtual ~Sombrillas();

	// Gets y sets
	uint8_t getDias() const {
		return dias;
	}

	bool isEstacionamiento() const {
		return estacionamiento;
	}

	uint8_t getId() const {
		return id;
	}

	void setId(uint8_t id) {
		this->id = id;
	}
	// ----

	// Métodos
	virtual float Calculo_costo() const;
	// ----
};

#endif /* SOMBRILLAS_H_ */
