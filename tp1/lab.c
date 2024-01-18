#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ID_LENGTH 256
#define MAX_PLANE_TYPE_LENGTH 10
#define NUM_WHEELS 7
#define NUM_WINGS 2
#define NUM_PLANES 3

struct Wheel {
    int id;
    bool isRearWheel;
};

struct Wing {
    int id[NUM_WINGS];
};

typedef struct {
    char id[MAX_ID_LENGTH];
    char planeType[MAX_PLANE_TYPE_LENGTH];
    bool isAvailable;
    struct Wheel wheels[NUM_WHEELS];
    struct Wing wings[NUM_WINGS];
} Plane;

struct Wheel* createWheels(int id) {
    struct Wheel* wheels = malloc(sizeof(struct Wheel) * NUM_WHEELS);

    for (int i = 0; i < NUM_WHEELS; i++) {
        wheels[i].id = id + i;
        wheels[i].isRearWheel = (i >= 3);
    }

    return wheels;
}

void populateWingAttributes(struct Wing* wing, int id) {
    for (int i = 1; i < MAX_PLANE_TYPE_LENGTH; i++) {
        wing->id[i] = (id % 10);
        id /= 10;
    }
}

struct Wing* createWings(long id) {
    struct Wing* wings = malloc(sizeof(struct Wing) * NUM_WINGS);

    for (int i = 0; i < NUM_WINGS; i++) {
        populateWingAttributes(&wings[i], id + i);
    }

    return wings;
}

void createPlanes(Plane* planes, int id, int numberOfPlanes) {
    for (int i = 0; i < numberOfPlanes; i++) {
        snprintf(planes[i].id, MAX_ID_LENGTH, "%d", id + i);
        planes[i].isAvailable = true;
        createWheels(id);
        createWings(id);
    }
}

void setAvailability(Plane* plane, bool isAvailable) {
    plane->isAvailable = isAvailable;
}

char* getAvailablePlanes(Plane* planeArray, int numberOfPlanes) {
    char* AvailablePlanesId = (char*)malloc(numberOfPlanes *sizeof(char));
    for (int currentIndex =0; currentIndex < numberOfPlanes; currentIndex++) {
        if ( planeArray[currentIndex].isAvailable == true) {
            //AvailablePlanesId[currentIndex] = (char)(planeArray[currentIndex].id);
            strcpy(&AvailablePlanesId[currentIndex * MAX_ID_LENGTH], planeArray[currentIndex].id);
        }
    }
    return AvailablePlanesId;
}

int main(int argc, char** argv) {
    printf("Hello\n");

    int id = 101;

    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    struct Wheel* wheels = createWheels(id);

    /* Create wing - [4 points] */
    long longId = 123456;
    struct Wing* wings = createWings(longId);

    /* Create plane - [4 points] */
    int numberOfPlanes = NUM_PLANES;
    Plane* planes = malloc(sizeof(Plane) * numberOfPlanes);
    createPlanes(planes, id, numberOfPlanes);

    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    Plane* plane = &planes[0];
    setAvailability(plane, true);
    

    /* Get available planes - [1 point] */
    
    char* availablePlanes = getAvailablePlanes(planes, numberOfPlanes);
    

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
   free(planes);
   free(wheels);
   free(wings);
   free(availablePlanes);
   return 0;
}
