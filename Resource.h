// Resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include "Enums.h"
#include <iostream>

class Resource {
private:
    int id;
    TreatmentType type;
    int capacity;        // Only applicable for GymExercises
    int currentLoad;     // How many patients are currently using it

public:
    Resource(int id, TreatmentType type, int capacity = 1);

    int getID() const;
    TreatmentType getType() const;

    bool isAvailable() const;
    void assign();
    void release();

    int getCapacity() const;
    int getCurrentLoad() const;

    friend std::ostream& operator<<(std::ostream& os, const Resource& r);
};

#endif
