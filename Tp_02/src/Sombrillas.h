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
	//Construtuctor
	Sombrillas();
	Sombrillas(unsigned short dias_, bool est, unsigned short id_);
	virtual ~Sombrillas();
	virtual void vMostrardatos_Sombrilla(void) const;

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
	// ----
};

#endif /* SOMBRILLAS_H_ */
