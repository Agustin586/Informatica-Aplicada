/*
 * Point3D.cpp
 *
 *  Created on: 12 may. 2023
 *      Author: LABDSI-04
 */

#include "Point3D.h"

Point3D::Point3D() {
	// TODO Auto-generated constructor stub
	x = 0;
	y = 0;
	z = 0;
}

Point3D::~Point3D() {
	// TODO Auto-generated destructor stub
}

Point3D::Point3D(int low, int high) {
	srand (time(NULL));

	x = rand() % high + low;
	y = rand() % high + low;
	z = rand() % high + low;
}

Point3D::Point3D(int x1, int y1, int z1) {
	x = x1;
	y = y1;
	z = z1;
}

Point3D::Point3D(const Point3D &other) {
	// TODO Auto-generated constructor stub

}

bool Point3D::equals(Point3D &q) {
	return ((x==q.x)&&(y==q.y)&&(z==q.z));
}

bool Point3D::equals(int x1, int y1, int z1) {
}

void Point3D::shitfX(int tx) {
}

void Point3D::shiftY(int ty) {
}

void Point3D::shiftZ(int tz) {
}

void Point3D::MostrarCoordenada(void) {
	cout << "(" << x << "," << y << "," << z << ")" << endl;
}
