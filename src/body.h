#include <math.h>
#include "vector.h"
#define G 6.673e-11
#define C 299792458
#define SOLAR_CONSTANT 1370
#define EARTH_RADIUS 6371e3

typedef struct{
	Vector3 vel;
	Vector3 pos;
	double mass;
	double solarCrossSection;
	double atmoCrossSection;
	double dragCoefficient;
} Body;

Body getBodyAfterGravUpdate(Body target, Body source, double dt);
Body getBodyAfterDragUpdate(Body target, double ApIndex, double F10Emission, double dt);
Body getBodyAfterSolarWindUpdate(Body target, Vector3 solarDirection, double dt);
Body getBodyAfterPosUpdate(Body target, double dt);
