//============================================================================
// Name        : IA_P2_EJ1.cpp
// Author      : Zuliani, Agustin
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include "Point3D.h"
using namespace std;


int main() {
	setbuf(stdout,0);

	Point3D pt1,pt2(10,-5,4),pt3(5,15);

	//Item a
	cout << "pt1:\t";
	pt1.MostrarCoordenada();
	cout << "pt2:\t";
	pt2.MostrarCoordenada();
	cout << "pt3:\t";
	pt3.MostrarCoordenada();

	return 0;
}
