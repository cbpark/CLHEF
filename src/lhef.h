#ifndef SRC_LHEF_H_
#define SRC_LHEF_H_

#include "event.h"
#include "parser.h"
#include "particle.h"
#include "pdg_numbering.h"
#include <string>

namespace lhef {
std::string openingLine();

std::string closingLine();

Particles initialStates(const Event& lhe);

Particles finalStates(const Event& lhe);

Particles particlesOf(const ParticleID& pid, const Event& lhe);

ParticleLines particleLinesOf(const ParticleID& pid, const Event& lhe);

Particle mother(const Particle& p, const Event& lhe);

Particle ancestor(const Particle& p, const Event& lhe);

Particles daughters(int pline, const Event& lhe);

Particles finalDaughters(int pline, const Event& lhe);
}  // namespace lhef

#endif  // SRC_LHEF_H_
