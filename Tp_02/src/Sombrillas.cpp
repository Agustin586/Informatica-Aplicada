/*
 * Sombrillas.cpp
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#include "Sombrillas.h"

Sombrillas::Sombrillas() {
	// TODO Auto-generated constructor stub

}

Sombrillas::Sombrillas(uint8_t dias_, bool est, uint8_t id_): dias(dias_),estacionamiento(est), id(id_){}

Sombrillas::~Sombrillas() {
	// TODO Auto-generated destructor stub
	cout<<"Se borró el objeto"<<endl;
}

float Sombrillas::Calculo_costo() const {
	if(this->estacionamiento)
		return this->dias * this->costo_fijo + (this->dias * this->costo_extra);
	else return this->dias * this->costo_fijo;
}
