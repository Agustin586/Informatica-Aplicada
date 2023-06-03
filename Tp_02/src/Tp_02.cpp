//============================================================================
// Name        : Tp_02.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Tp 02
//============================================================================

#include <iostream>
#include "Sombrillas.h"
#include "SombrillasEspeciales.h"
using namespace std;

#define TRUE	1
#define FALSE	0

void Init(void);

uint8_t Sombrillas::costo_fijo = 200;
uint8_t Sombrillas::costo_extra = 100;

int main() {
	setbuf(stdout,0);

	//Creamos un objeto de tipo sombrillas
	Sombrillas s1(2,false,1);
	Sombrillas s2(2,true,2);
	SombrillasEspeciales s3(2,false,2,2);
	SombrillasEspeciales s4(2,true,2,2);

	cout<<"Costo total de sombrilla 1: "<<s1.Calculo_costo()<<endl;
	cout<<"Costo total de sombrilla 2: "<<s2.Calculo_costo()<<endl;

	cout<<endl;

	cout<<"Costo sombrilla especial s3:"<<s3.Calculo_costo()<<endl;
	cout<<"Costo sombrilla especial s3:"<<s4.Calculo_costo()<<endl;

	cout<<endl;

	Init();

//	while(1){
//		break;	//No va despues
//	}

	return 0;
}

void Init(void){


	return;
}
