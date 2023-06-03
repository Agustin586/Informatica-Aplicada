/*
 * SombrillasEspeciales.h
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#ifndef SOMBRILLASESPECIALES_H_
#define SOMBRILLASESPECIALES_H_

#include "Sombrillas.h"

class SombrillasEspeciales: public Sombrillas {
private:
	uint8_t cant_reposeras;
public:
	SombrillasEspeciales();
	SombrillasEspeciales(uint8_t dias_, bool est, uint8_t id_, uint8_t repo_extras);
	virtual ~SombrillasEspeciales();

	virtual float Calculo_costo() const;

	uint8_t getCantReposeras() const {
		return cant_reposeras;
	}
};

#endif /* SOMBRILLASESPECIALES_H_ */
