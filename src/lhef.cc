#include <algorithm>
#include <utility>
#include "lhef.h"

namespace lhef {
std::ostream& operator<<(std::ostream& os, const Particles& ps) {
    os << '[';
    for (auto p : ps) {
        os << p << ',';
    }
    os << "\b]";
    return os;
}

Particles StableParticles(const LHEFEvent& lhe) {
    Particles stable_pars;
    auto ps = lhe.event.second;
    std::for_each(ps.cbegin(), ps.cend(),
                  [&] (const std::pair<int, Particle>& pmap) {
                      Particle p = pmap.second;
                      if (p.istup == 1) {
                          stable_pars.push_back(p);
                      }
                  });

    return stable_pars;
}
}  // namespace lhef
