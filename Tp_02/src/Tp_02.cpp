//============================================================================
// Name        : Tp_02.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Tp 02
//============================================================================
#include <cstdint>
#include "Inicializacion.h"
using namespace std;

int main() {
	setbuf(stdout,0);

	//Menu
	Progm_est TProgm, *pTProgm = &TProgm;
	Menu_est TMenu, *pTMenu = &TMenu;

	int iTotal_Lista_Sombrilla;

	//Ingreso de la cantidad total de sombrillas
	cout<<"Ingrese la cantidad total de sombrillas"<<endl;
	cin>>iTotal_Lista_Sombrilla;
	ColeccionAlquiler OCCA_Lista_Sombrillas(iTotal_Lista_Sombrilla);	//siglas OCCA: Objeto clase ColeccionAlquiler

	vInit();
	vInit_Progm(pTProgm);
	vInit_Menu(pTMenu);

	while(1){
		vProgm(pTProgm,pTMenu,OCCA_Lista_Sombrillas);

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

void vProgm(Progm_est *TProgm,Menu_est *TMenu,ColeccionAlquiler &csLista_Sombrilla){
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
		vMenu(TMenu,csLista_Sombrilla);

		*TProgm = ESPERA_SELECCION_MENU;
		if(*TMenu != SALIR)	*TMenu = VACIO;	//Vuelve a inicalizarlo en caso de no terminar el programa

	break;
	}
	}
}

void vMenu (Menu_est *TMenu,ColeccionAlquiler &csLista_Sombrilla){
	switch(*TMenu){
	case VACIO:{
		//Se queda esperando
	break;
	}
	case NUEVA_SOMBRILLA_NORMAL:{
		//Debe verificar si antes existe lugar para poder crear una sombrilla de cualquier tipo
		// ---
		//
		if((csLista_Sombrilla.getUsCantActualSombrillas() + 1) < (csLista_Sombrilla.getCantTotal()))
			vCrearSombrilla_Normal(csLista_Sombrilla);
		else
			cout<<"No existen sombrillas suficientes."<<endl;
	break;
	}
	case NUEVA_SOMBRILLA_ESPECIAL:{
		//Debe verificar si antes existe lugar para poder crear una sombrilla de cualquier tipo
		// ---
		//
		if((csLista_Sombrilla.getUsCantActualSombrillas() + 1) < (csLista_Sombrilla.getCantTotal()))
			vCrearSombrilla_Especial(csLista_Sombrilla);
		else
			cout<<"No existen sombrillas suficientes."<<endl;
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

void vCrearSombrilla_Normal(ColeccionAlquiler &csLista_Sombrilla){
	int dias;
	bool estacionamiento;

	cout<<"-----------------------------------------------------------"<<endl;

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

	//Aumentamos la cantidad actual de sombrillas
	csLista_Sombrilla.setUsCantActualSombrillas(csLista_Sombrilla.getUsCantActualSombrillas() + 1);
	cout<<csLista_Sombrilla.getUsCantActualSombrillas();

	//Creamos un objeto de tipo sombrilla normal
	Sombrillas somb_norm(dias,estacionamiento,csLista_Sombrilla.getUsCantActualSombrillas());

	//Insertamos dicho objeto en nuestro vector polimórfico
	csLista_Sombrilla.vInsertar(somb_norm);

	//Mostramos si se cargó
	csLista_Sombrilla.vMostrar_Lista_Alquiler();

	cout<<"-----------------------------------------------------------"<<endl;

	return;
}

void vCrearSombrilla_Especial(ColeccionAlquiler &csLista_Sombrilla){
	unsigned short usRepo_extras,dias;
	bool estacionamiento;

	cout<<"-----------------------------------------------------------"<<endl;
	cout<<"Ingrese la cantidad de reposeras extras:"<<endl;
	cin>>usRepo_extras;

	//No necesita verificación dado que siempre suele haber suficientes reposeras

	cout<<"Dias de alquiler:"<<endl;
	cin>>dias;

	while(dias > CANT_MAX_DIAS_ALQUILER){
		cout<<"Ingrese una cantidad de dias menor a: "<<CANT_MAX_DIAS_ALQUILER<<endl;
		cout<<"Dias de alquiler:"<<endl;
		cin>>dias;

		cout<<endl<<dias<<endl;
	}

	cout<<"Estacionamiento:"<<endl;
	cout<<"1:Si \t 0:No"<<endl;
	cin>>estacionamiento;

	//Aumentamos la cantidad actual de sombrillas
	csLista_Sombrilla.setUsCantActualSombrillas(csLista_Sombrilla.getUsCantActualSombrillas()+1);
	cout<<csLista_Sombrilla.getUsCantActualSombrillas();

	//Creamos la sombrilla especial
	SombrillasEspeciales SombEspecial(dias,estacionamiento,csLista_Sombrilla.getUsCantActualSombrillas(),usRepo_extras);

	//Insertamos dicho objeto en nuestro vector polimórfico
	csLista_Sombrilla.vInsertar(SombEspecial);

	//Mostramos si se cargó
	csLista_Sombrilla.vMostrar_Lista_Alquiler();

	return;
}
