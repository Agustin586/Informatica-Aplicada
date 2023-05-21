/*
 * Point3D.h
 *
 *  Created on: 12 may. 2023
 *      Author: LABDSI-04
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include <iostream>
#include <time.h>
using namespace std;

class Point3D {
private:
	int x,y,z;

	void shitfX(int tx);
	void shiftY(int ty);
	void shiftZ(int tz);
public:
	//Constructores
	Point3D();
	Point3D(int x1,int y1,int z1);
	Point3D(int low,int high);

	virtual ~Point3D();
	Point3D(const Point3D &other);

	//Gets y sets
	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	int getZ() const {
		return z;
	}

	void setZ(int z) {
		this->z = z;
	}

	//Funciones propias de la clase
	bool equals(Point3D &q);
	bool equals(int x1,int y1,int z1);
	Point3D translate(int tx,int ty,int tz);
	int distanceOrigin();
	int distanceToPoint(Point3D &q);
	int scalarProduct(Point3D q);
	void MostrarCoordenada(void);
};

#endif /* POINT3D_H_ */
