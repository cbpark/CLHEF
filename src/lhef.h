#ifndef SRC_LHEF_H_
#define SRC_LHEF_H_

#include "type.h"

namespace lhef {
Particles InitialStates(const LHEFEvent& lhe);

Particles FinalStates(const LHEFEvent& lhe);

Particles ParticlesOf(const ParticleID& pid, const LHEFEvent& lhe);

Particle Mother(Particle p, const LHEFEvent& lhe);

Particle Ancestor(Particle p, const LHEFEvent& lhe);
}  // namespace lhef

#endif  // SRC_LHEF_H_
