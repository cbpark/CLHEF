/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef SRC_KINEMATICS_H_
#define SRC_KINEMATICS_H_

#include <cmath>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif  // HAVE_CONFIG_H
#ifdef HAVE_ROOT
#include "TLorentzVector.h"
#endif  // HAVE_ROOT

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

#ifdef HAVE_ROOT
inline TLorentzVector mkLorentzVector(const Energy &e, const Px &px,
                                      const Py &py, const Pz &pz) {
    return {px.value, py.value, pz.value, e.value};
}

inline double invariantMass(const Energy &e, const Px &px, const Py &py,
                            const Pz &pz) {
    const TLorentzVector v4 = mkLorentzVector(e, px, py, pz);
    return v4.M();
}
#else
inline double invariantMass(const Energy &e, const Px &px, const Py &py,
                            const Pz &pz) {
    const double m2 = e.value * e.value - px.value * px.value -
                      py.value * py.value - pz.value * pz.value;
    return m2 < 0 ? -std::sqrt(-m2) : std::sqrt(m2);
}
#endif  // HAVE_ROOT
}  // namespace lhef

#endif  // SRC_KINEMATICS_H_
