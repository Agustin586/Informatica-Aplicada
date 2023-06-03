//============================================================================
// Name        : Tp_02.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Tp 02
//============================================================================
#include "Inicializacion.h"
using namespace std;

int main() {
	setbuf(stdout,0);

	//Creamos un objeto de tipo sombrillas
	Sombrillas s1(2,false,1);
	Sombrillas s2(2,true,2);
	SombrillasEspeciales s3(2,false,2,2);
	SombrillasEspeciales s4(2,true,2,2);

	//Menu
	Progm_est *pTProgm;
	Menu_est *pTMenu;

	Init();
	vInit_Progm(pTProgm);
	vInit_Menu(pTMenu);

	while(1){
		vProgm(pTProgm,pTMenu);
	}

	return 0;
}

void vInit(void){
	return;
}

void vInit_Progm (Progm_est *TProgm){
	*TProgm = ESPERA_SELECCION_MENU;

	return;
}

void vInit_Menu (Menu_est *TMenu){
	*TMenu = VACIO;

	return;
}

void vProgm(Progm_est *TProgm,Menu_est *TMenu){
	switch(TProgm){
	case ESPERA_SELECCION_MENU:{
		uint8_t opcion;

		cout<<"Opciones:"<<endl<<"1:Ingreso de sombrilla normal"<<"2:Ingreso de sombrilla especial"<<"3:Mostrar lista total de sombrillas"<<"4:Borrar sombrilla"<<"5:Cerrar"<<endl;
		cin>>opcion;

		while(opcion != NUEVA_SOMBRILLA_NORMAL || opcion != NUEVA_SOMBRILLA_ESPECIAL || opcion != MOSTRAR_LISTA_TOTAL_SOMBRILLAS || opcion != BORRAR_SOMBRILLA || opcion != SALIR){
			cout<<"Opciones:"<<endl<<"1:Ingreso de sombrilla"<<"2:Mostrar lista total de sombrillas"<<"3:Borrar sombrilla"<<"4:Cerrar"<<endl;
			cin>>opcion;
		}

		*TMenu = opcion;
		*TProgm = MENU;
	break;
	}
	case MENU:{
		vMenu(TMenu);

		*TProgm = ESPERA_SELECCION_MENU;
	break;
	}
	}
}

void vMenu (Menu_est *TMenu){
	switch(*TMenu){
	case VACIO:{

	break;
	}
	case NUEVA_SOMBRILLA_NORMAL:{
		//Debe verificar si antes existe lugar para poder crear una sombrilla de cualquier tipo
		// ---
		//
		vCrearSombrilla_Normal();
	break;
	}
	case NUEVA_SOMBRILLA_ESPECIAL:{
		//Debe verificar si antes existe lugar para poder crear una sombrilla de cualquier tipo
		// ---
		//


	break;
	}
	case MOSTRAR_LISTA_TOTAL_SOMBRILLAS:{

	break;
	}
	case BORRAR_SOMBRILLA:{

	break;
	}
	case SALIR:{

	break;
	}
	default:{
	break;
	}
	}
}

void vCrearSombrilla_Normal(){
	uint8_t dias;
	bool estacionamiento;

	cout<<"Dias de alquiler:"<<endl;
	cin>>dias;

	while(dias > CANT_MAX_DIAS_ALQUILER){
		cout<<"Ingrese una cantidad de dias menor a: "<<CANT_MAX_DIAS_ALQUILER<<endl;
		cout<<"Dias de alquiler:"<<endl;
		cin>>dias;
	}

	cout<<"Estacionamiento:"<<endl;
	cout<<"1:Si \t 0:No"<<endl;
	cin>>estacionamiento;

	Sombrillas somb_norm(dias,estacionamiento,Cant_Actual_Alquileres++);

	return;
}
