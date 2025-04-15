// Enums.h
#ifndef ENUMS_H
#define ENUMS_H

enum class PatientType {
    Normal,
    Recovering
};

enum class TreatmentType {
    Electrotherapy,
    UltrasoundTherapy,
    GymExercises
};

enum class PatientStatus {
    Early,
    Late,
    Waiting,
    InTreatment
};

#endif
