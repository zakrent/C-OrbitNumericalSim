#include "body.h"

//#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

Body getBodyAfterGravUpdate(Body target, Body source, double dt){
	double distance = getVectorMagnitude(subtractVectors(target.pos, source.pos));
	double accelerationMagnitude = G*source.mass/pow(distance, 2);
	Vector3 directionVector = normaliseVector(subtractVectors(source.pos, target.pos));
	Vector3 accelerationVector = scaleVector(directionVector, accelerationMagnitude);
	target.vel = addVectors(target.vel, scaleVector(accelerationVector, dt));
#ifdef DEBUG
	printf("Grav acc = %f\n", accelerationMagnitude);
#endif
	return target;
}

Body getBodyAfterSolarWindUpdate(Body target, Vector3 solarDirection, double dt){
	const double solarRadiationPressure = SOLAR_CONSTANT/C;
	Vector3 windDirection = scaleVector(solarDirection, -1);
	double accelerationMagnitude = target.solarCrossSection*solarRadiationPressure;
	Vector3 accelerationVector = scaleVector(windDirection, accelerationMagnitude);
	target.vel = addVectors(target.vel, scaleVector(accelerationVector, dt));
#ifdef DEBUG
	printf("Wind acc = %f\n", accelerationMagnitude);
#endif
	return target;
}	

double getAirDensity(double altitude, double ApIndex, double F10Emission){
	//source: http://www.spaceacademy.net.au/watch/debris/atmosmod.htm
	double p;
	if(altitude > 500000){
		//for now assume 0
		p = 0;
	}
	else if(altitude > 180000){
		double T = 900+2.5*(F10Emission-70)+1.5*ApIndex;
		double u = 27-0.012*((altitude/1000)-200);
		p = 6e-10*exp(-((altitude/1000)-175)/(T/u));
	}
	else if(altitude > 0){
		//very inaccurate isothermal model for now
		p = 1.3*exp((-altitude)/7000);
	}
	else{
		p = 0;
	}
#ifdef DEBUG
	printf("Alt = %f\n", altitude);
	printf("Density = %f\n", p);
#endif
	return p;
}

Body getBodyAfterDragUpdate(Body target, double ApIndex, double F10Emission, double dt){
	double altitude = getVectorMagnitude(target.pos)-EARTH_RADIUS;
	double velocity = getVectorMagnitude(target.vel);
	double airDensity = getAirDensity(altitude, ApIndex, F10Emission);
	double dragMagnitude = 0.5*airDensity*pow(velocity, 2)*target.dragCoefficient*target.atmoCrossSection;
	Vector3 dragDirection = normaliseVector(scaleVector(target.vel, -1));
	Vector3 accelerationVector = scaleVector(dragDirection, dragMagnitude);
	target.vel = addVectors(target.vel, scaleVector(accelerationVector, dt));
#ifdef DEBUG
	printf("Drag acc = %f\n", dragMagnitude);
#endif
	return target;
}

Body getBodyAfterPosUpdate(Body target, double dt){
	target.pos = addVectors(target.pos, scaleVector(target.vel, dt));
	return target;
}
