#ifndef COR_VECTOR
#define COR_VECTOR

typedef struct{
	double x;
	double y;
	double z;
} Vector3;

Vector3 addVectors(Vector3 a, Vector3 b);
Vector3 subtractVectors(Vector3 a, Vector3 b);
Vector3 scaleVector(Vector3 a, double scalar);
double getVectorMagnitude(Vector3 a);
Vector3 normaliseVector(Vector3 a);
Vector3 getVectorFromUser();

#endif
