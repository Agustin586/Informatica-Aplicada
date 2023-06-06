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
	int cant_reposeras;
public:
	SombrillasEspeciales();
	SombrillasEspeciales(int dias_, bool est, int id_, int repo_extras);
	virtual ~SombrillasEspeciales();

	virtual float Calculo_costo() const;
	virtual void vMostrardatos_Sombrilla(void) const;

	int getCantReposeras() const {
		return cant_reposeras;
	}
};

#endif /* SOMBRILLASESPECIALES_H_ */
