/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef CLHEF_SRC_LHEF_H_
#define CLHEF_SRC_LHEF_H_

#include <string>
#include "event.h"
#include "parser.h"
#include "particle.h"
#include "pid.h"

namespace lhef {
std::string openingLine();

std::string closingLine();

Particles initialStates(const Event &lhe);

Particles finalStates(const Event &lhe);

Particles particlesOf(const ParticleID &pid, const Event &lhe);

ParticleLines particleLinesOf(const ParticleID &pid, const Event &lhe);

Particle mother(const Particle &p, const Event &lhe);

Particle ancestor(const Particle &p, const Event &lhe);

Particles daughters(int pline, const Event &lhe);

Particles finalDaughters(int pline, const Event &lhe);
}  // namespace lhef

#endif  // CLHEF_SRC_LHEF_H_
