/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef CLHEF_SRC_KINEMATICS_H_
#define CLHEF_SRC_KINEMATICS_H_

#include <cmath>

namespace lhef {
struct Px {
    double value;
    Px() : value(0.0) {}
    explicit Px(double v) : value(v) {}
};

struct Py {
    double value;
    Py() : value(0.0) {}
    explicit Py(double v) : value(v) {}
};

struct Pz {
    double value;
    Pz() : value(0.0) {}
    explicit Pz(double v) : value(v) {}
};

struct Energy {
    double value;
    Energy() : value(0.0) {}
    explicit Energy(double v) : value(v) {}
};

double invariantMass(const Energy &e, const Px &px, const Py &py, const Pz &pz);
}  // namespace lhef

#endif  // CLHEF_SRC_KINEMATICS_H_
