// XTreatment.cpp

#include "XTreatment.h"
#include "Scheduler.h"

XTreatment::XTreatment(int duration)
    : Treatment(TreatmentType::GymExercises, duration) {}

bool XTreatment::canAssign(Scheduler& scheduler) {
    return scheduler.getNextXRoom() != nullptr;
}

void XTreatment::moveFromAllToWait(Scheduler& scheduler, Patient* patient) {
    scheduler.addToXWaiting(patient);
}
