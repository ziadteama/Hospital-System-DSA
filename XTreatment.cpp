// XTreatment.cpp

#include "XTreatment.h"
#include "Scheduler.h"

XTreatment::XTreatment(int duration)
    : Treatment(TreatmentType::GymExercises, duration) {}

bool XTreatment::canAssign(Scheduler& scheduler) {
    return scheduler.getNextXRoom() != nullptr;
}

void XTreatment::moveFromAllToWait(Scheduler& scheduler, Patient* patient) {
    if (!patient) {
        std::cout << "[ERROR] XTreatment tried to move a null patient to waitlist!\n";
        return;
    }
    scheduler.addToXWaiting(patient);
}

