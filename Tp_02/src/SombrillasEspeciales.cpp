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

SombrillasEspeciales::SombrillasEspeciales(uint8_t dias_, bool est, uint8_t id_, uint8_t repo_extras) : Sombrillas(dias_,est,id_) {
	this->cant_reposeras = repo_extras;
}

SombrillasEspeciales::~SombrillasEspeciales() {
	// TODO Auto-generated destructor stub
}

float SombrillasEspeciales::Calculo_costo() const {
	return 1.4 * Sombrillas::Calculo_costo() + (this->cant_reposeras * 0.3333 * Sombrillas::getDias() * Sombrillas::costo_extra);
}
