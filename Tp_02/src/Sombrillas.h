/*
 * Sombrillas.h
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#ifndef SOMBRILLAS_H_
#define SOMBRILLAS_H_

#include <iostream>
#include <cstdint>
#include <stdbool.h>

using namespace std;

class Sombrillas {
protected:
	int dias;
	bool estacionamiento;
	int id;
public:
	static int Cant_activas;
	static int costo_fijo;
	static int costo_extra;
	//Construtuctor y destructor
	Sombrillas();
	Sombrillas(int dias_, bool est, int id_);
	virtual ~Sombrillas();

	// Gets y sets
	int getDias() const {
		return dias;
	}

	bool isEstacionamiento() const {
		return estacionamiento;
	}

	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}
	// ----

	// Métodos
	virtual float Calculo_costo() const;
	virtual void vMostrardatos_Sombrilla(void) const;
	// ----
};

#endif /* SOMBRILLAS_H_ */
