/*
 * ColeccionAlquiler.cpp
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#include "ColeccionAlquiler.h"

ColeccionAlquiler::ColeccionAlquiler() {
	// TODO Auto-generated constructor stub

}

ColeccionAlquiler::ColeccionAlquiler(uint8_t total) {
	this->cant_total = total;

	for(int i=0;i<total;i++){
		p_somb[i] = new Sombrillas();
	}
}

ColeccionAlquiler::~ColeccionAlquiler() {
	// TODO Auto-generated destructor stub
	delete [] p_somb;
}

void ColeccionAlquiler::Insertar(const Sombrillas &somb_, bool especial) {
	//Verifica si hay lugar
	if(Sombrillas::Cant_activas < this->cant_total)
	{
		//Verifico que tipo de sombrilla cargo
		if(especial)
			{p_somb[Sombrillas::Cant_activas]->cant_reposeras= somb_->cant_reposeras;}

		p_somb[Sombrillas::Cant_activas] ->id= somb_->id;
		p_somb[Sombrillas::Cant_activas] ->dias= somb_->dias;
		p_somb[Sombrillas::Cant_activas] ->estacionamiento= somb_->estacionamiento;

		Sombrillas::Cant_Activas ++;
	}
}

void ColeccionAlquiler::Eliminar(uint8_t id_, bool especial) {
	for(int i=0;i < this->cant_total;i++){
		if((p_somb[i]->id) == id_){
			p_somb[i]->id = p_somb[Sombrillas::Cant_Activas]->id;
			p_somb[i]->dias=p_somb[Sombrillas::Cant_Activas] ->dias;
			p_somb[i]->estacionamiento=p_somb[Sombrillas::Cant_Activas] ->estacionamiento;

			if(especial){
				p_somb[i] ->cant_reposeras=p_somb[Sombrillas::Cant_Activas] ->cant_reposeras;
			}

			Sombrillas::Cant_Activas--;
		}
	}
}

float ColeccionAlquiler::Total_Alquiler(uint8_t min_dias) {
}












/*
 ColeccionAlquiler::ColeccionAlquiler(uint8_t total) {
	this->Total= total;
	for(int i=0,i<total,i++)
		p_somb[i]=new Sombrillas(sizeof(Sombrillas));
}



ColeccionAlquiler::~ColeccionAlquiler() {
	// TODO Auto-generated destructor stub
}
uint8_t ColeccionAlquiler::getTotal(){
	return Total;
}
void ColeccionAlquiler::Insertar(const Sombrillas &somb_, bool especial) {
	if(Sombrillas::Cant_activas < this->Total)
	{
		if(especial)
			{p_somb[Sombrillas::Cant_activas] ->cant_reposeras= somb_->cant_reposeras;}

		p_somb[Sombrillas::Cant_activas] ->id= somb_->id;
		p_somb[Sombrillas::Cant_activas] ->dias= somb_->dias;
		p_somb[Sombrillas::Cant_activas] ->estacionamiento= somb_->estacionamiento;
		Sombrillas::Cant_Activas ++;
	}
}

void ColeccionAlquiler::Eliminar(uint8_t id_, bool especial) {
	for(int i=0,i<this->Total,i++)
	{	if(p_somb[i] ->id==id_)
			{p_somb[i] ->id=p_somb[Sombrillas::Cant_Activas] ->id;
			p_somb[i] ->dias=p_somb[Sombrillas::Cant_Activas] ->dias;
			p_somb[i] ->estacionamiento=p_somb[Sombrillas::Cant_Activas] ->estacionamiento;

			if(especial)
			{p_somb[i] ->cant_reposeras=p_somb[Sombrillas::Cant_Activas] ->cant_reposeras;}
			Sombrillas::Cant_Activas--;
			}
	}
}

float ColeccionAlquiler::Total_Alquiler(uint8_t min_dias) {
	float sumador=0;
		for(int i=0;i<Sombrillas::Cant_Activas,i++)
			{	if(min_dias < p_somb[i]->dias)
					sumador += p_somb[i]->Calculo_costo();
		}
		return sumador;
}
 */
