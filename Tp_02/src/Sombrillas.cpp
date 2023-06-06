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

Sombrillas::Sombrillas(unsigned short dias_, bool est, unsigned short id_): dias(dias_),estacionamiento(est), id(id_){}

Sombrillas::~Sombrillas() {
	// TODO Auto-generated destructor stub
	cout<<"Se borró el objeto"<<endl;
}

float Sombrillas::Calculo_costo() const {
	if(this->estacionamiento)
		return this->dias * this->costo_fijo + (this->dias * this->costo_extra);
	else return this->dias * this->costo_fijo;
}

void Sombrillas::vMostrardatos_Sombrilla(void) {
	cout<<"Id: "<<this->id<<" \t Dias alquilados: "<<this->dias<<" \t Estacionamiento: ";
	if(this->estacionamiento)	cout<<"Si"<<endl;
	else						cout<<"No"<<endl;
}
