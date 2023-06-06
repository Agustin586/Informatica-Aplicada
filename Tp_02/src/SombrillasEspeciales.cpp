/*
 * SombrillasEspeciales.cpp
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#include "SombrillasEspeciales.h"

SombrillasEspeciales::SombrillasEspeciales() {
	// TODO Auto-generated constructor stub

}

SombrillasEspeciales::SombrillasEspeciales(int dias_, bool est, int id_, int repo_extras) : Sombrillas(dias_,est,id_) {
	this->cant_reposeras = repo_extras;
}

SombrillasEspeciales::~SombrillasEspeciales() {
	// TODO Auto-generated destructor stub
}

float SombrillasEspeciales::Calculo_costo() const {
	return 1.4 * Sombrillas::Calculo_costo() + (this->cant_reposeras * 0.3333 * Sombrillas::getDias() * Sombrillas::costo_extra);
}

void SombrillasEspeciales::vMostrardatos_Sombrilla(void) const {
	cout<<"Sombrilla especial"<<endl;
	cout<<"Id: "<<this->id<<" \t Dias alquilados: "<<this->dias<<" \t Estacionamiento: ";
	if(this->estacionamiento)	cout<<"Si";
	else						cout<<"No";
	cout<<"\t Cantidad de Reposeras:"<<this->cant_reposeras<<endl;
}
