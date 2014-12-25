#ifndef SRC_LHEF_H_
#define SRC_LHEF_H_

#include <ostream>
#include <vector>
#include "type.h"

namespace lhef {
Particles StableParticles(const LHEFEvent& lhe);
}  // namespace lhef

#endif  // SRC_LHEF_H_
