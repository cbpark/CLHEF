/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef CLHEF_SRC_PARTICLE_H_
#define CLHEF_SRC_PARTICLE_H_

#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "kinematics.h"

namespace lhef {
class Particle {
private:
    // Particle ID according to Particle Data Group convention.
    int idup_ = 0;
    // Status code.
    int istup_ = 0;
    // Index of first and last mother.
    std::pair<int, int> mothup_ = {0, 0};
    // Integer tag for the color flow line passing through the
    // (anti-)color of the particle.
    std::pair<int, int> icolup_ = {0, 0};
    // Lab frame momentum (P_x, P_y, P_z, E, M) of particle in GeV.
    std::array<double, 5> pup_ = {{0.0, 0.0, 0.0, 0.0, 0.0}};
    // Invariant lifetime (distance from production to decay) in mm.
    double vtimup_ = 0.0;
    // Consine of the angle between the spin-vector of particle and the
    // three-momentum of the decaying particle, specified in the lab frame.
    double spinup_ = 0.0;

public:
    Particle() {}
    Particle(const Energy &e, const Px &px, const Py &py, const Pz &pz) {
        const double m = invariantMass(e, px, py, pz);
        pup_ = {{px.value, py.value, pz.value, e.value, m}};
    }
    Particle(int idup, int istdup, int mothup1, int mothup2, int icolup1,
             int icolup2, double pup1, double pup2, double pup3, double pup4,
             double pup5, double vtimup, double spinup)
        : idup_(idup),
          istup_(istdup),
          mothup_({mothup1, mothup2}),
          icolup_({icolup1, icolup2}),
          pup_({{pup1, pup2, pup3, pup4, pup5}}),
          vtimup_(vtimup),
          spinup_(spinup) {}

    int pid() const { return idup_; }
    int status() const { return istup_; }
    std::pair<int, int> mother() const { return mothup_; }
    double px() const { return pup_[0]; }
    double py() const { return pup_[1]; }
    double pz() const { return pup_[2]; }
    double energy() const { return pup_[3]; }
    double mass() const { return pup_[4]; }
    double pt() const { return std::hypot(pup_[0], pup_[1]); }
    double decayLength() const { return vtimup_; }

    friend std::string show(const Particle &p);

    friend bool operator<(const Particle &lhs, const Particle &rhs) {
        return lhs.pt() < rhs.pt();
    }
    friend bool operator>(const Particle &lhs, const Particle &rhs) {
        return rhs < lhs;
    }
    Particle &operator+=(const Particle &rhs);
    Particle &operator-=(const Particle &rhs);
    friend Particle operator+(Particle lhs, const Particle &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Particle operator-(Particle lhs, const Particle &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend std::istream &operator>>(std::istream &is, Particle &p);
    friend std::ostream &operator<<(std::ostream &os, const Particle &p);
};

std::string show(const Particle &p);

using Particles = std::vector<Particle>;
std::string show(const Particles &ps);

using ParticleID = std::vector<int>;

using ParticleLines = std::vector<int>;
}  // namespace lhef

#endif  // CLHEF_SRC_PARTICLE_H_
