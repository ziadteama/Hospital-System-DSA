#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "LinkedQueue.h"
#include "priQueue.h"
#include "ArrayStack.h"
#include "Patient.h"
#include "Resource.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "EarlyPList.h"
#include <string>
#include "LatePList.h"

class Scheduler
{
private:
    // Master clock
    int currentTime;

    // Configuration from input
    int totalPatients;
    int cancelProbability;
    int rescheduleProbability;
    int simulationMode; // 0 = Silent, 1 = Interactive

    // Patient lists
    LinkedQueue<Patient *> allPatients;
    EarlyPList earlyPatients;
    LatePList latePatients;
    // priQueue<Patient*> latePatients;

    EU_WaitList eWaiting;
    EU_WaitList uWaiting;
    X_WaitList xWaiting;

    priQueue<Patient *> inTreatment;
    ArrayStack<Patient *> finishedPatients;

    // Resources
    LinkedQueue<Resource *> eDevices;
    LinkedQueue<Resource *> uDevices;
    LinkedQueue<Resource *> xRooms;

public:
    Scheduler();

    // Phase 2 Core Functions
    void loadPatients(const std::string &inputFileName);
    void simulate();
    bool simulationFinished() const;
    void generateOutputFile(const std::string &outputFileName);

    // Treatment and Patient Flow
    void assignResources();   // Assign patients to available resources
    void updateInTreatment(); // Update patients currently receiving treatment

    // Waitlist Helpers (called by Treatment subclasses)
    void addToEWaiting(Patient *p);
    void addToUWaiting(Patient *p);
    void addToXWaiting(Patient *p);

    // Resource Queue Access
    Resource *getNextEDevice();
    Resource *getNextUDevice();
    Resource *getNextXRoom();

    void setMode(int mode) { simulationMode = mode; }
    int getMode() const { return simulationMode; }

    void returnEDevice(Resource *r);
    void returnUDevice(Resource *r);
    void returnXRoom(Resource *r);

    void printStatus();

    // UI Access
    friend class UI;
};

#endif
