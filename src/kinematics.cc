/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#include "kinematics.h"
#include <cmath>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif  // HAVE_CONFIG_H
#ifdef HAVE_ROOT
#include "TLorentzVector.h"
#endif  // HAVE_ROOT

namespace lhef {
#ifdef HAVE_ROOT
TLorentzVector mkLorentzVector(const Energy &e, const Px &px, const Py &py,
                               const Pz &pz) {
    return {px.value, py.value, pz.value, e.value};
}

double invariantMass(const Energy &e, const Px &px, const Py &py,
                     const Pz &pz) {
    const TLorentzVector v4 = mkLorentzVector(e, px, py, pz);
    return v4.M();
}
#else
double invariantMass(const Energy &e, const Px &px, const Py &py,
                     const Pz &pz) {
    const double m2 = e.value * e.value - px.value * px.value -
                      py.value * py.value - pz.value * pz.value;
    return m2 < 0 ? -std::sqrt(-m2) : std::sqrt(m2);
}
#endif  // HAVE_ROOT
}  // namespace lhef
