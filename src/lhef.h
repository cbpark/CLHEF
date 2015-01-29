#ifndef SRC_LHEF_H_
#define SRC_LHEF_H_

#include "event.h"
#include "kinematics.h"
#include "parser.h"
#include "particle.h"
#include "pdg_numbering.h"

namespace lhef {
Particles InitialStates(const Event& lhe);

Particles FinalStates(const Event& lhe);

Particles ParticlesOf(const ParticleID& pid, const Event& lhe);

ParticleLines ParticleLinesOf(const ParticleID& pid, const Event& lhe);

Particle Mother(const Particle& p, const Event& lhe);

Particle Ancestor(const Particle& p, const Event& lhe);

Particles Daughters(int pline, const Event& lhe);

Particles FinalDaughters(int pline, const Event& lhe);
}  // namespace lhef

#endif  // SRC_LHEF_H_
