#include <algorithm>
#include <functional>
#include <utility>
#include "lhef.h"

namespace lhef {
Particles InitialStates(const LHEFEvent& lhe) {
    Particles initialstates;
    auto ps = lhe.event.second;
    std::for_each(ps.cbegin(), ps.cend(),
                  [&] (const std::pair<int, Particle>& pmap) {
                      Particle p = pmap.second;
                      if (p.mothup.first == 1) {
                          initialstates.push_back(p);
                      }
                  });
    return initialstates;
}

Particles FinalStates(const LHEFEvent& lhe) {
    Particles finalstates;
    auto ps = lhe.event.second;
    std::for_each(ps.cbegin(), ps.cend(),
                  [&] (const std::pair<int, Particle>& pmap) {
                      Particle p = pmap.second;
                      if (p.istup == 1) {
                          finalstates.push_back(p);
                      }
                  });

    return finalstates;
}
}  // namespace lhef
