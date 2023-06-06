/*
 * ColeccionAlquiler.cpp
 *
 *  Created on: 3 jun. 2023
 *      Author: aguat
 */

#include "ColeccionAlquiler.h"

ColeccionAlquiler::ColeccionAlquiler() {
}

ColeccionAlquiler::ColeccionAlquiler(int total_somb) {
	this->cant_total = total_somb;
}

ColeccionAlquiler::~ColeccionAlquiler() {
//	for(int i=0;i<Lista_Sombrillas.size();i++){
//		delete Lista_Sombrillas[i];
//	}
}

void ColeccionAlquiler::vInsertar(const Sombrillas &MSombrilla) {
//	Lista_Sombrillas.push_back(MSombrilla);	//Insertamos la sombrilla en el vector
	Lista_Sombrillas->push_back(MSombrilla);
}

void ColeccionAlquiler::vEliminar(int id_, bool especial) {
	for(unsigned int i=0;i<Lista_Sombrillas->size();i++){
		Lista_Sombrillas->erase(Lista_Sombrillas->begin()+i);	//Borra el que se encuentra en la posicion i
	}
}

//float ColeccionAlquiler::fTotal_Alquiler(int min_dias) {
//float sumador=0;
//for(int i=0;i<Sombrillas::Cant_Activas,i++)
//	{	if(min_dias < p_somb[i]->dias)
//			sumador += p_somb[i]->Calculo_costo();
//}
//return sumador;
//}

void ColeccionAlquiler::vMostrar_Lista_Alquiler(void) {
	cout<<endl<<"|Lista Sombrillas|"<<endl;
	for(unsigned int i=0;i<Lista_Sombrillas->size();i++){
		Lista_Sombrillas[i].vMostrardatos_Sombrilla();
	}
	cout<<endl;
}
