// UI.cpp

#include "UI.h"
#include <iostream>
using namespace std;

int UI::getOperationMode() {
    int mode;
    cout << "Select mode: (0) Silent, (1) Interactive: ";
    cin >> mode;
    return mode;
}

string UI::getInputFileName() {
    string fileName;
    cout << "Enter input file name: ";
    cin >> fileName;
    return fileName;
}

string UI::getOutputFileName() {
    string fileName;
    cout << "Enter output file name: ";
    cin >> fileName;
    return fileName;
}

void UI::printSystemStatus(
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
) {
    cout << "\nCurrent Timestep: " << currentTime << "\n";

    // ALL Patients
    cout << "===============   ALL List   ===============\n";
    cout << allPatients.GetCount() << " patients total: ";
    allPatients.print();

    // Waiting Lists
    cout << "============== Waiting Lists ==============\n";
    cout << eWaiting.GetCount() << " Electrotherapy patients: "; eWaiting.print();
    cout << uWaiting.GetCount() << " UltrasoundTherapy patients: "; uWaiting.print();
    cout << xWaiting.GetCount() << " GymExercises patients: "; xWaiting.print();

    // Early & Late Lists
    cout << "===============   Early List   ================\n";
    cout << earlyPatients.GetCount() << " patients: "; earlyPatients.print();

    cout << "===============   Late List   ================\n";
    cout << latePatients.GetCount() << " patients: "; latePatients.print();

    // Available Devices
    cout << "===============   Avail E-devices ===============\n";
    cout << eDevices.GetCount() << " Electro devices: "; eDevices.print();

    cout << "===============   Avail U-devices ===============\n";
    cout << uDevices.GetCount() << " Ultrasound devices: "; uDevices.print();

    cout << "===============   Avail X-rooms ===============\n";
    xRooms.print();

    // In Treatment
    cout << "============  In-treatment List ================\n";
    cout << inTreatment.GetCount() << " patients: "; inTreatment.print();

    // Finished
    cout << "-------------------------------------------------------\n";
    cout << finishedPatients.GetCount() << " Finished patients: "; finishedPatients.print();
}
