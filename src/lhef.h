#ifndef SRC_LHEF_H_
#define SRC_LHEF_H_

#include <ostream>
#include <vector>
#include "lhefevent.h"

namespace lhef {
using Particles = std::vector<Particle>;
std::ostream& operator<<(std::ostream& os, const Particles& ps);

Particles StableParticles(const LHEFEvent& lhe);
}  // namespace lhef

#endif  // SRC_LHEF_H_
