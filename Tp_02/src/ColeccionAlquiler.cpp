/*
 * ColeccionAlquiler.cpp
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#include "ColeccionAlquiler.h"
#include "Sombrillas.h"
#include "SombrillasEspeciales.h"

ColeccionAlquiler::ColeccionAlquiler() {
}

ColeccionAlquiler::ColeccionAlquiler(int total_somb) {
	this->cant_total = total_somb;
}

ColeccionAlquiler::~ColeccionAlquiler() {
	for(unsigned int i=0;i<Lista_Sombrillas.size();i++){
		delete Lista_Sombrillas[i];
	}
}

void ColeccionAlquiler::vInsertar(Sombrillas* MSombrilla) {
	Lista_Sombrillas.push_back(MSombrilla);	//Inserta el objeto de tipo Sombrilla o Sombrilla Especial en el vector.
}

void ColeccionAlquiler::vEliminar(int id_) {
	for(unsigned int i=0;i<Lista_Sombrillas.size();i++){
		if(Lista_Sombrillas.at(i)->getId()==id_)	delete(Lista_Sombrillas[i]),Lista_Sombrillas.erase(Lista_Sombrillas.begin()+i);	//Borra el que se encuentra en la posicion i
	}
}

float ColeccionAlquiler::fTotalPlazo_Alquiler(int min_dias) {
	float sumador=0;

	for(unsigned int i=0;i<Lista_Sombrillas.size();i++){
		if(Lista_Sombrillas[i]->getDias() >= min_dias){
			SombrillasEspeciales* Somb_especial = dynamic_cast <SombrillasEspeciales*> (Lista_Sombrillas[i]);
			if(Somb_especial)
				sumador += Somb_especial->Calculo_costo();
			else
				sumador += Lista_Sombrillas[i]->Calculo_costo();
		}
	}
	return sumador;
}

void ColeccionAlquiler::vMostrar_Lista_Alquiler(void) {
	cout<<endl<<"|Lista Sombrillas|"<<endl;

	//Relizo un bucle donde recorro hasta el tamaño del vector dinamico
	for(unsigned int i = 0;i<Lista_Sombrillas.size();i++){
		//Hago un casteo dinamico para ver si se trata de un objeto de tipo SombrillaEspecial
		SombrillasEspeciales* Somb_Especial = dynamic_cast <SombrillasEspeciales*> (Lista_Sombrillas[i]);

		if(Somb_Especial){
			Somb_Especial->vMostrardatos_Sombrilla();
		}
		else{
			Lista_Sombrillas[i]->vMostrardatos_Sombrilla();
			cout << endl;
		}
	}

	cout<<endl;
}

bool ColeccionAlquiler::bVerificar_Id(int id_) {
	for(unsigned int i=0;i<Lista_Sombrillas.size();i++){
		if(Lista_Sombrillas[i]->getId() == id_)	return true;
	}
	return false;
}
