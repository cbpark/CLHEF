#include <algorithm>
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

Particle Mother(Particle p, const LHEFEvent& lhe) {
    int mo_line = p.mothup.first;
    auto ps = lhe.event.second;
    auto mo_pos = ps.find(mo_line);
    if (mo_pos == ps.end()) {  // mother particle not found.
        Particle empty_par;
        return empty_par;
    } else {
        return ps.at(mo_line);
    }
}
}  // namespace lhef
