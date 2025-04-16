#include "Scheduler.h"
#include "UI.h"
#include <iostream>

int main() {
    Scheduler system;
    UI ui;

    int mode = UI::getOperationMode();
    std::string inputFile = UI::getInputFileName();
    std::string outputFile = UI::getOutputFileName();

    std::cout << "Reading patients from file: " << inputFile << "\n";
    system.loadPatients(inputFile);
    std::cout << "Finished loading patients.\n";

    if (!system.simulationFinished()) {
        std::cout << "Starting simulation...\n";
        if (mode == 1) {
            while (!system.simulationFinished()) {
                system.simulate(); // 1 timestep or full?
                system.printStatus();
                std::cin.get();
            }
        } else {
            system.simulate();
        }
    } else {
        std::cout << "Simulation skipped. Nothing to simulate.\n";
    }

    std::cout << "Generating output file: " << outputFile << "\n";
    system.generateOutputFile(outputFile);
    std::cout << "Done!\n";

    return 0;
}
