/* INF2610 - TP1
/ Matricule 1 : 2244082
/ Matricule 2 : 2209249
*/
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h> 
#include <stdbool.h>

#define MAX_ID_LENGTH 256
#define MAX_PLANE_TYPE_LENGTH 10
#define NUM_WHEELS 4
#define NUM_WINGS 2
#define NUM_PLANES 3

struct Wheel {
    int id;
    bool isRearWheel;
};

struct Wing {
    int id[NUM_WINGS];
};

struct Plane {
    char id[MAX_ID_LENGTH];
    char planeType[MAX_PLANE_TYPE_LENGTH];
    bool isAvailable;
    struct Wheel wheels[NUM_WHEELS];
    struct Wing wings[NUM_WINGS];
};


int main(int argc, char** argv) {
    printf("Hello\n");

    int id = 1;

    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    /*
    Wheel[] wheels;
    wheels = createWheels(id);    
    */

    /* Create wing - [4 points] */
    /*
    long longId = 1;
    Wing[] wings;
    wings = createWings(longId);
    */

    /* Create plane - [4 points] */
    /*
    int numberOfPlanes = NUM_PLANES;
    Plane* planes = malloc(sizeof(Plane) * numberOfPlanes);
    createPlanes(planes, *id, NUM_PLANES);
    */

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    /*
    Plane plane = planes[0];
    setAvailability(plane, true);
    */

    /* Get available planes - [1 point] */
    /*
    getAvailablePlanes(planes, numberOfPlanes);
    */

    /* Classify planes - [2 points] */
    /*
    Plane plane = planes[1];
    setPlaneType(plane);
    */

    /* Return type-specific planes - [2 points] */
    /*
    char planeType[] = "Small";
    getPlanesByType(planes, planeType, NUM_PLANES);
    */
}
