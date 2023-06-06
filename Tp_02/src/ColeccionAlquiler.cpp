/*
 * ColeccionAlquiler.cpp
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#include "ColeccionAlquiler.h"

ColeccionAlquiler::ColeccionAlquiler() {
}

ColeccionAlquiler::ColeccionAlquiler(uint8_t total_somb) {
	this->cant_total = total_somb;
}

ColeccionAlquiler::~ColeccionAlquiler() {
//	for(uint8_t i=0;i<Lista_Sombrillas.size();i++){
//		delete Lista_Sombrillas[i];
//	}
}

void ColeccionAlquiler::vInsertar(const Sombrillas &MSombrilla) {
	Lista_Sombrillas.push_back(MSombrilla);	//Insertamos la sombrilla en el vector
}

void ColeccionAlquiler::vEliminar(uint8_t id_, bool especial) {
	for(uint8_t i=0;i<Lista_Sombrillas.size();i++){
		Lista_Sombrillas.erase(Lista_Sombrillas.begin()+i);	//Borra el que se encuentra en la posicion i
	}
}

//float ColeccionAlquiler::fTotal_Alquiler(uint8_t min_dias) {
//
//}

void ColeccionAlquiler::vMostrar_Lista_Alquiler(void) {
	cout<<endl<<"|Lista Sombrillas|"<<endl;
	for(uint8_t i=0;i<Lista_Sombrillas.size();i++){
		Lista_Sombrillas[i].vMostrardatos_Sombrilla();
	}
	cout<<endl;
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
void ColeccionAlquiler::vInsertar(const Sombrillas &somb_, bool especial) {
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

void ColeccionAlquiler::vEliminar(uint8_t id_, bool especial) {
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

float ColeccionAlquiler::fTotal_Alquiler(uint8_t min_dias) {
	float sumador=0;
		for(int i=0;i<Sombrillas::Cant_Activas,i++)
			{	if(min_dias < p_somb[i]->dias)
					sumador += p_somb[i]->Calculo_costo();
		}
		return sumador;
}
 */
