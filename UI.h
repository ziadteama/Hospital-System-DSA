// UI.h
#ifndef UI_H
#define UI_H

#include "LinkedQueue.h"
#include "priQueue.h"
#include "ArrayStack.h"
#include "Patient.h"
#include "Resource.h"

class UI {
public:
    // Get file names and mode from user (if needed)
    static int getOperationMode();
    static std::string getInputFileName();
    static std::string getOutputFileName();

    // Print full system state each timestep
    static void printSystemStatus(
        int currentTime,
        const LinkedQueue<Patient*>& allPatients,
        const priQueue<Patient*>& inTreatment,
        const ArrayStack<Patient*>& finishedPatients,
        const LinkedQueue<Resource*>& eDevices,
        const LinkedQueue<Resource*>& uDevices,
        const LinkedQueue<Resource*>& xRooms,
        const LinkedQueue<Patient*>& eWaiting,
        const LinkedQueue<Patient*>& uWaiting,
        const LinkedQueue<Patient*>& xWaiting,
        const priQueue<Patient*>& latePatients,
        const priQueue<Patient*>& earlyPatients
    );

    // Optional helpers
    static void printPatientList(const LinkedQueue<Patient*>& list, const std::string& title, int limit = 10);
    static void printDeviceList(const LinkedQueue<Resource*>& list, const std::string& label);
};

#endif
