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

	//Menu
	Progm_est TProgm, *pTProgm = &TProgm;
	Menu_est TMenu, *pTMenu = &TMenu;

	int total_somb;

	cout<<"Ingrese la cantidad total de sombrillas"<<endl;
	cin>>total_somb;
	ColeccionAlquiler lista_total(total_somb);

	vInit();
	vInit_Progm(pTProgm);
	vInit_Menu(pTMenu);

	while(1){
		vProgm(pTProgm,pTMenu,lista_total);

		if(*pTMenu == SALIR)	break;
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

void vProgm(Progm_est *TProgm,Menu_est *TMenu,ColeccionAlquiler &lista_){
	switch(*TProgm){
	case ESPERA_SELECCION_MENU:{
		int opcion;

		cout<<"Opciones:"<<endl<<"1:Ingreso de sombrilla normal\n"<<"2:Ingreso de sombrilla especial\n"<<"3:Mostrar lista total de sombrillas\n"<<"4:Borrar sombrilla\n"<<"5:Cerrar"<<endl<<endl;
		cout<<"Opcion: ";
		cin>>opcion;

		*TMenu = (Menu_est)opcion;

		while(*TMenu != NUEVA_SOMBRILLA_NORMAL && *TMenu != NUEVA_SOMBRILLA_ESPECIAL && *TMenu != MOSTRAR_LISTA_TOTAL_SOMBRILLAS && *TMenu != BORRAR_SOMBRILLA && *TMenu != SALIR){
			cout<<endl<<"Ingreso un dato equivocado, ingrese de nuevo"<<endl<<endl;
			cout<<"Opciones:"<<endl<<"1:Ingreso de sombrilla normal\n"<<"2:Ingreso de sombrilla especial\n"<<"3:Mostrar lista total de sombrillas\n"<<"4:Borrar sombrilla\n"<<"5:Cerrar"<<endl<<endl;
			cout<<"Opcion: ";
			cin>>opcion;

			*TMenu = (Menu_est)opcion;
			cout<<*TMenu<<endl;

		}

		*TProgm = MENU;
	break;
	}
	case MENU:{
		vMenu(TMenu,lista_);

		*TProgm = ESPERA_SELECCION_MENU;
		if(*TMenu != SALIR)	*TMenu = VACIO;	//Vuelve a inicalizarlo en caso de no terminar el programa

	break;
	}
	}
}

void vMenu (Menu_est *TMenu,ColeccionAlquiler &lista_){
	switch(*TMenu){
	case VACIO:{
		//Se queda esperando
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
		//Deberia llamar a los destructores de todo por las dudas
		cout<<"Programa finalizado"<<endl;
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

	while(dias < CANT_MAX_DIAS_ALQUILER){
		cout<<"Ingrese una cantidad de dias menor a: "<<CANT_MAX_DIAS_ALQUILER<<endl;
		cout<<"Dias de alquiler:"<<endl;
		cin>>dias;
	}

	cout<<"Estacionamiento:"<<endl;
	cout<<"1:Si \t 0:No"<<endl;
	cin>>estacionamiento;

	//Creamos un objeto de tipo sombrilla normal
	Sombrillas somb_norm(dias,estacionamiento,Cant_Actual_Alquileres++);

	//Insertamos dicho objeto en nuestro vector polimórfico


	return;
}
