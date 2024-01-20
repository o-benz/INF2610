#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_ID_LENGTH 256
#define MAX_PLANE_TYPE_LENGTH 10
#define NUM_WHEELS 7
#define NUM_WINGS 2
#define NUM_PLANES 3
#define BASE_ID_ARRAY_LENGTH 9

struct Wheel {
    int id;
    bool isRearWheel;
};

struct Wing{
    int id[BASE_ID_ARRAY_LENGTH];
};

struct Plane{
    char id[MAX_ID_LENGTH];
    char planeType[MAX_PLANE_TYPE_LENGTH];
    bool isAvailable;
    struct Wheel* wheels;
    struct Wing* wings;
};

struct Wheel* createWheels(int id) {
    struct Wheel* wheels = malloc(sizeof(struct Wheel) * NUM_WHEELS);

    for (int i = 0; i < NUM_WHEELS; i++) {
        wheels[i].id = id + i;
        wheels[i].isRearWheel = (i >= 3);
    }

    return wheels;
}

void populateWingAttributes(struct Wing* wing, int id) {
    int* idArray = malloc((sizeof(int) * BASE_ID_ARRAY_LENGTH));

    for (int i = BASE_ID_ARRAY_LENGTH - 1; i >=0 ; i--) {
        wing->id[i] = id % 10;
        id = id /10;
    }
    free(idArray);
}

struct Wing* createWings(long id) {
    struct Wing* wings = malloc(sizeof(struct Wing) * NUM_WINGS);

    for (int i = 0; i < NUM_WINGS; i++) {
        populateWingAttributes(&wings[i], id + i);
    }

    return wings;
}

void createPlanes(struct Plane* planes, int id, int numberOfPlanes) {
    for (int i = 0; i < numberOfPlanes; i++) {
        snprintf(planes[i].id, MAX_ID_LENGTH, "%d", id + i);
        planes[i].isAvailable = true;
        planes[i].wheels = createWheels(id);
        planes[i].wings = createWings(id);
    }
}

void setAvailability(struct Plane* plane, bool isAvailable) {
    plane->isAvailable = isAvailable;
}

char* getAvailablePlanes(struct Plane* planeArray, int numberOfPlanes) {
    char* AvailablePlanesId = (char*)malloc(MAX_ID_LENGTH * numberOfPlanes *sizeof(char));
    for (int currentIndex =0; currentIndex < numberOfPlanes; currentIndex++) {
        if ( planeArray[currentIndex].isAvailable == true) {
            strcpy(&AvailablePlanesId[currentIndex * MAX_ID_LENGTH], planeArray[currentIndex].id);
        }
    }
    return AvailablePlanesId;
}

void setPlaneType(struct Plane* plane) {
    bool isNumberStarted = false;
    int id = 0;
    for (int i = 0; i < BASE_ID_ARRAY_LENGTH ; i++) {
        id = id *10 + plane->wings[0].id[i];
    }

    int typeId = id & 10;
    if (0 <= typeId || typeId >= 2) {
        snprintf(plane->planeType, sizeof(plane->planeType), "Small%s", "");
    } else if (3 <= typeId || typeId >= 6) {
        snprintf(plane->planeType, sizeof(plane->planeType), "Medium%s", "");
    } else if (7 <= typeId || typeId >= 8) {
        snprintf(plane->planeType, sizeof(plane->planeType), "Large%s", "");
    }
}

struct Plane* getPlanesByType(struct Plane* planes, char* searchedType, int nbOfPlanes) {
    struct Plane* result = malloc(sizeof(struct Plane) * NUM_PLANES);
    int index = 0;
    for (int i = 0; i < nbOfPlanes; i++) {
        if (strcmp(planes[i].planeType, searchedType) == 0) {
            result[index++] = planes[i];
        }
    }
    return result;
}

int main(int argc, char** argv) {
    printf("Hello\n");

    int id = 101;

    /* PARTIE 2 - [10 points] */

    /* Create wheel - [2 points] */
    struct Wheel* wheels = createWheels(id);
    printf("wheels\n");


    /* Create wing - [4 points] */
    long longId = 123456;
    struct Wing* wings = createWings(longId);
    printf("wings\n");

    /* Create plane - [4 points] */
    struct Plane* planes = malloc(sizeof(struct Plane) * NUM_PLANES);
    printf("planes\n");

    createPlanes(planes, id, NUM_PLANES);
    printf("planes2\n");


    /* PARTIE 3 - [6 points] */

    /* Set availabilities - [1 point] */
    
    struct Plane* plane = &planes[0];
    setAvailability(plane, true);

    /* Get available planes - [1 point] */
    
    char* availablePlanes = getAvailablePlanes(planes, NUM_PLANES);
    printf("availability\n");
    
    /* Classify planes - [2 points] */
    
    struct Plane plane2 = planes[1];
    setPlaneType(&plane2); 

    /* Return type-specific planes - [2 points] */
    
    char planeType[] = "Small";
    struct Plane* smallPlanes = getPlanesByType(planes, planeType, NUM_PLANES);
    
    free(planes);
    free(wheels);
    free(wings);
    free(availablePlanes);
    free(smallPlanes);
    return 0;
}
