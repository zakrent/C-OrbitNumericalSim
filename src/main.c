//#define DEBUG
#define EXIT_ON_CRASH

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "body.h"
#include "vector.h"

int main(){
	Body* current = malloc(2*sizeof(Body));
	Body* previous = malloc(2*sizeof(Body));
	Body body1 = {{0,0,0}, {0,0,0}, 5e24, 0, 0, 0};
	Body body2 = {{0,0,0}, {6771e3,0,0}, 1, 0, 0, 0};

	printf("Input position state vector[m]: \n");
	body2.pos = getVectorFromUser(); 
	printf("Input velocity state vector[m/s]: \n");
	body2.vel = getVectorFromUser();
	printf("Input solar cross-sectional area [m^2]: ");
	scanf("%lf", &(body2.solarCrossSection));
	printf("Input atmospheric cross-sectional area [m^2]: ");
	scanf("%lf", &(body2.atmoCrossSection));
	printf("Input drag coefficient: ");
	scanf("%lf", &(body2.dragCoefficient));

	printf("Input solar directional unit vector: \n");
	Vector3 solarDirection = normaliseVector(getVectorFromUser());
	
	double ApIndex, F10Emission;

	printf("Input Ap index: ");
	scanf("%lf", &(ApIndex));
	printf("Input 10.7 cm solar radio flux[sfu]: ");
	scanf("%lf", &(F10Emission));

	printf("Output to file? [Y/N]: ");
	char answer;
	do{
		scanf("%c", &answer);
	}while(answer != 'y' && answer != 'Y' && answer != 'n' && answer !='N');
	int outputToFile = (answer == 'Y' || answer == 'y');	

	FILE* outputFile;
	if(outputToFile){
		outputFile = fopen("log.txt", "w+");
	}

	previous[0] = body1;
	previous[1] = body2;
	current[0] = body1;
	current[1] = body2;

	double dt = 1;
	double distanceSinceLastPrint = 0;
	while(1){
		current[1] = getBodyAfterGravUpdate(previous[1], previous[0], dt);
		current[1] = getBodyAfterSolarWindUpdate(current[1], solarDirection, dt);
		current[1] = getBodyAfterDragUpdate(current[1], ApIndex, F10Emission, dt);
		current[1] = getBodyAfterPosUpdate(current[1], dt);

		double dSmax = getVectorMagnitude(scaleVector(current[1].vel, dt));
		
#ifdef DEBUG
		printf("%f %f %f %f %f\n", dt, dSmax, distanceSinceLastPrint, current[1].pos.x, previous[1].pos.x);
#endif
		if(dSmax > 5){
			dt /= dSmax/5;
		}
		else if(dSmax < 4 && dSmax != 0){
			dt *= 4/dSmax;
		}
		else if(dSmax == 0){
			dt *= 1.1;
		}
		else{
			distanceSinceLastPrint += dSmax;
			Body* temp = current; //can't xor swap without cast
			current = previous;
			previous = temp;
		}
#ifndef DEBUG
		if(distanceSinceLastPrint > 1e3){
			distanceSinceLastPrint = 0;
			printf("%f %f %f\n", 
					current[1].pos.x,
					current[1].pos.y,
					current[1].pos.z);
			if(outputToFile){
				fprintf(outputFile, "%f %f %f\n", 
						current[1].pos.x,
						current[1].pos.y,
						current[1].pos.z);
			}
		}
#endif
	}
	free(current);
	free(previous);
	return 0;
}
