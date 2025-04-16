// Patient.cpp

#include "Patient.h"
#include <iostream>

Patient::Patient(int id, PatientType type, int appointmentTime, int arrivalTime)
    : id(id), type(type), appointmentTime(appointmentTime), arrivalTime(arrivalTime),
      status(PatientStatus::Waiting), finishTime(0), totalWaitingTime(0),
      totalTreatmentTime(0), cancelled(false), rescheduled(false) {}

int Patient::getID() const { return id; }
PatientType Patient::getType() const { return type; }
int Patient::getAppointmentTime() const { return appointmentTime; }
int Patient::getArrivalTime() const { return arrivalTime; }
PatientStatus Patient::getStatus() const { return status; }
void Patient::setStatus(PatientStatus s) { status = s; }

int Patient::getFinishTime() const { return finishTime; }
int Patient::getTotalWaitingTime() const { return totalWaitingTime; }
int Patient::getTotalTreatmentTime() const { return totalTreatmentTime; }

void Patient::incrementWaitingTime()
{
    totalWaitingTime++;
}

void Patient::setFinishTime(int time)
{
    finishTime = time;
}

void Patient::addTreatment(Treatment *treatment)
{
    if (treatment)
    {
        requiredTreatments.enqueue(treatment);
        totalTreatmentTime += treatment->getDuration();
    }
}

void Patient::advanceTreatment()
{
    Treatment *temp = nullptr;
    requiredTreatments.dequeue(temp);
    // optional: delete temp if ownership is here
}

Treatment *Patient::getNextTreatment()
{
    Treatment *next = nullptr;
    requiredTreatments.peek(next);
    return next;
}

void Patient::clearRemainingTreatments()
{
    Treatment *t = nullptr;
    while (!requiredTreatments.isEmpty())
    {
        requiredTreatments.dequeue(t);
        if (t)
            delete t; // free memory
    }
    totalTreatmentTime = 0; // ❗ <- RESET this
}

bool Patient::hasMoreTreatments() const
{
    return !requiredTreatments.isEmpty();
}

void Patient::markCancelled()
{
    cancelled = true;
}

void Patient::markRescheduled()
{
    rescheduled = true;
    totalTreatmentTime = 0;
}

bool Patient::wasCancelled() const
{
    return cancelled;
}

bool Patient::wasRescheduled() const
{
    return rescheduled;
}

LinkedQueue<Treatment *> &Patient::getTreatmentQueue()
{
    return requiredTreatments;
}

// Print: e.g., P4_Normal or P12_Recovering
std::ostream &operator<<(std::ostream &os, const Patient &p)
{
    os << "P" << p.id << "_";
    if (p.type == PatientType::Normal)
        os << "Normal";
    else
        os << "Recovering";
    return os;
}
