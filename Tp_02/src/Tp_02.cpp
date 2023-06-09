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
	ColeccionAlquiler ObjLista_Sombrillas(iTotal_Lista_Sombrilla);	//siglas OCCA: Objeto clase ColeccionAlquiler

	vInit();
	vInit_Progm(pTProgm);
	vInit_Menu(pTMenu);

	while(1){
		vProgm(pTProgm,pTMenu,ObjLista_Sombrillas);

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

		cout<<"Opciones:"<<endl<<"1:Ingreso de sombrilla normal\n"<<"2:Ingreso de sombrilla especial\n"<<"3:Mostrar lista total de sombrillas\n"<<"4:Costo en un plazo de dias\n"<<"5:Borrar sombrilla\n"<<"6:Cerrar"<<endl<<endl;
		cout<<"Opcion: ";
		cin>>opcion;

		*TMenu = (Menu_est)opcion;

		while(*TMenu != NUEVA_SOMBRILLA_NORMAL && *TMenu != NUEVA_SOMBRILLA_ESPECIAL && *TMenu != MOSTRAR_LISTA_TOTAL_SOMBRILLAS && *TMenu != BORRAR_SOMBRILLA && *TMenu != SALIR && *TMenu != COSTO_PLAZO_DIAS){
			cout<<endl<<"Ingreso un dato equivocado, ingrese de nuevo"<<endl<<endl;
			cout<<"Opciones:"<<endl<<"1:Ingreso de sombrilla normal\n"<<"2:Ingreso de sombrilla especial\n"<<"3:Mostrar lista total de sombrillas\n"<<"4:Costo en un plazo de dias\n"<<"5:Borrar sombrilla\n"<<"6:Cerrar"<<endl<<endl;
			cout<<"Opcion: ";
			cin>>opcion;

			*TMenu = (Menu_est)opcion;
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
		/*
		 * Aca debe ir la condición de si tiene o no espacio, yo puse otra condición porque no entendia
		 * el enunciado pero fijense como es. Solamente hay que cambiar la condción del if
		 * en este y el que sigue abajo. Quiero mis cariñosasss !!!
		 * */
		if((csLista_Sombrilla.getUsCantActualSombrillas() + 1) <= (csLista_Sombrilla.getCantTotal())){
			vCrearSombrilla_Normal(csLista_Sombrilla);
			csLista_Sombrilla.setUsCantActualSombrillas(csLista_Sombrilla.getUsCantActualSombrillas()+1);
		}
		else{
			cout << "No existen sombrillas suficientes." << endl;
			cout << "-----------------------------------------------------------" << endl;
		}


	break;
	}
	case NUEVA_SOMBRILLA_ESPECIAL:{
		if((csLista_Sombrilla.getUsCantActualSombrillas() + 1) <= (csLista_Sombrilla.getCantTotal())){
			vCrearSombrilla_Especial(csLista_Sombrilla);
			csLista_Sombrilla.setUsCantActualSombrillas(csLista_Sombrilla.getUsCantActualSombrillas()+1);
		}
		else{
			cout << "No existen sombrillas suficientes." << endl;
			cout << "-----------------------------------------------------------" << endl;
		}

	break;
	}
	case MOSTRAR_LISTA_TOTAL_SOMBRILLAS:{
		cout << "-----------------------------------------------------------" << endl;

		csLista_Sombrilla.vMostrar_Lista_Alquiler();

		cout << "-----------------------------------------------------------" << endl;
	break;
	}
	case COSTO_PLAZO_DIAS:{
		int plazo_dias;

		cout << "-----------------------------------------------------------" << endl;

		cout << "Plazo de dias: " << endl;
		cin >> plazo_dias;

		cout << "Costo: " << csLista_Sombrilla.fTotalPlazo_Alquiler(plazo_dias) << endl << endl;

		cout << "-----------------------------------------------------------" << endl;
	break;
	}
	case BORRAR_SOMBRILLA:{
		int id;
		cout << "-----------------------------------------------------------" << endl;

		cout << "Ingrese el Id a borrar:" << endl;
		cin >> id;

		while(!csLista_Sombrilla.bVerificar_Id(id)){
			if(id == 0)	break;	//Sale del menu, es decir no quiere borrar nada
			cout << "Ingrese un id que exista: " << endl;
			cin >> id;
		}

		csLista_Sombrilla.vEliminar(id);
		csLista_Sombrilla.setUsCantActualSombrillas(csLista_Sombrilla.getUsCantActualSombrillas()-1);

		cout << endl;

		cout << "-----------------------------------------------------------" << endl;
	break;
	}
	case SALIR:{
		cout << "Programa finalizado" << endl;
		csLista_Sombrilla.~ColeccionAlquiler();

	break;
	}
	default:{
	break;
	}
	}
}

void vCrearSombrilla_Normal(ColeccionAlquiler &csLista_Sombrilla){
	int dias,id_somb;
	bool estacionamiento;

	cout << "-----------------------------------------------------------" << endl;

	//Ingresa el id de la sombrilla
	cout << "Id Sombrilla:" << endl;
	cin >> id_somb;

	//Debe verificar que esa id no se encuentre ya cargada
	while(bVerificar_Id_Somb(csLista_Sombrilla,id_somb)){
		cout << "Esta sombrilla ya fue creada, ingrese otra diferente." << endl;
		cin >> id_somb;
	}

	cout << "Dias de alquiler:" << endl;
	cin >> dias;

	while(dias > CANT_MAX_DIAS_ALQUILER){
		cout << "Ingrese una cantidad de dias menor a: " << CANT_MAX_DIAS_ALQUILER << endl;
		cout << "Dias de alquiler:" << endl;
		cin >> dias;
	}

	cout << "Estacionamiento:" << endl;
	cout << "1:Si \t 0:No" << endl;
	cin >> estacionamiento;

	//Creamos un objeto de tipo sombrilla normal
	Sombrillas *Somb_Norm = new Sombrillas(dias,estacionamiento,id_somb);

	//Insertamos dicho objeto en nuestro vector polimórfico
	csLista_Sombrilla.vInsertar(Somb_Norm);

	cout<<"-----------------------------------------------------------"<<endl;

	return;
}

void vCrearSombrilla_Especial(ColeccionAlquiler &csLista_Sombrilla){
	int id_somb;
	unsigned short usRepo_extras,dias;
	bool estacionamiento;

	cout << "-----------------------------------------------------------" << endl;
	//Ingresa el id de la sombrilla
	cout << "Id Sombrilla:" << endl;
	cin >> id_somb;

	//Debe verificar que esa id no se encuentre ya cargada
	while(bVerificar_Id_Somb(csLista_Sombrilla,id_somb)){
		cout << "Esta sombrilla ya fue creada, ingrese otra diferente." << endl;
		cin >> id_somb;
	}

	//Cargamos la cantidad de dias
	cout << "Dias de alquiler:" << endl;
	cin >> dias;

	while(dias > CANT_MAX_DIAS_ALQUILER){
		cout << "Ingrese una cantidad de dias menor a: " << CANT_MAX_DIAS_ALQUILER << endl;
		cout << "Dias de alquiler:" << endl;
		cin >> dias;

		cout << endl << dias << endl;
	}

	cout << "Estacionamiento:" << endl;
	cout << "1:Si \t 0:No" << endl;
	cin >> estacionamiento;

	cout << "Ingrese la cantidad de reposeras extras:" << endl;
	cin >> usRepo_extras;

	//Creamos la sombrilla especial
	SombrillasEspeciales* SombEspecial = new SombrillasEspeciales(dias,estacionamiento,id_somb,usRepo_extras);

	//Insertamos dicho objeto en nuestro vector polimórfico
	csLista_Sombrilla.vInsertar(SombEspecial);

	return;
}

bool bVerificar_Id_Somb(ColeccionAlquiler &csLista_Sombrilla,int id){
	if(csLista_Sombrilla.bVerificar_Id(id))	return true;
	else	return false;
}
