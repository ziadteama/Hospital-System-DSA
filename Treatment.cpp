// Treatment.cpp

#include "Treatment.h"

Treatment::Treatment(TreatmentType type, int duration)
    : type(type), duration(duration), assignmentTime(-1), assignedResource(nullptr) {}

TreatmentType Treatment::getType() const {
    return type;
}

int Treatment::getDuration() const {
    return duration;
}

int Treatment::getAssignmentTime() const {
    return assignmentTime;
}

void Treatment::setAssignmentTime(int time) {
    assignmentTime = time;
}

Resource* Treatment::getAssignedResource() const {
    return assignedResource;
}

void Treatment::setAssignedResource(Resource* r) {
    assignedResource = r;
}

// Print treatment type only
std::ostream& operator<<(std::ostream& os, const Treatment& t) {
    switch (t.getType()) {
        case TreatmentType::Electrotherapy:
            os << "Electrotherapy";
            break;
        case TreatmentType::UltrasoundTherapy:
            os << "UltrasoundTherapy";
            break;
        case TreatmentType::GymExercises:
            os << "GymExercises";
            break;
    }
    return os;
}
