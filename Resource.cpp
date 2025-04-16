// Resource.cpp

#include "Resource.h"
#include <iostream>

Resource::Resource(int id, TreatmentType type, int capacity)
    : id(id), type(type), capacity(capacity), currentLoad(0) {}

int Resource::getID() const {
    return id;
}

TreatmentType Resource::getType() const {
    return type;
}

int Resource::getCapacity() const {
    return capacity;
}

int Resource::getCurrentLoad() const {
    return currentLoad;
}

bool Resource::isAvailable() const {
    return currentLoad < capacity;
}

void Resource::assign() {
    if (currentLoad < capacity)
        currentLoad++;
}

void Resource::release() {
    if (currentLoad > 0)
        currentLoad--;
}

// Print: e.g., R5_Electrotherapy[1/1]
std::ostream& operator<<(std::ostream& os, const Resource& r) {
    os << "R" << r.id << "_";
    switch (r.type) {
        case TreatmentType::Electrotherapy:
            os << "Electrotherapy";
            break;
        case TreatmentType::UltrasoundTherapy:
            os << "Ultrasound";
            break;
        case TreatmentType::GymExercises:
            os << "Gym";
            break;
    }
    os << "[" << r.currentLoad << "/" << r.capacity << "]";
    return os;
}
