#include <stdio.h>
#include <math.h>
#include "vector.h"

Vector3 addVectors(Vector3 a, Vector3 b){
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

Vector3 subtractVectors(Vector3 a, Vector3 b){
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

Vector3 scaleVector(Vector3 a, double scalar){
	a.x *= scalar;
	a.y *= scalar;
	a.z *= scalar;
	return a;
}

double getVectorMagnitude(Vector3 a){
	return sqrt(pow(a.x, 2)+pow(a.y, 2)+pow(a.z, 2));
}

Vector3 normaliseVector(Vector3 a){
	a = scaleVector(a, 1/getVectorMagnitude(a));
	return a;
}

Vector3 getVectorFromUser(){
	Vector3 ret = {0,0,0};
	double test;
	printf("X: ");
	scanf("%lf", &(ret.x));
	printf("Y: ");
	scanf("%lf", &(ret.y));
	printf("Z: ");
	scanf("%lf", &(ret.z));
	return ret;
}
