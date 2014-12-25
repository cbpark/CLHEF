#include <algorithm>
#include <cstdlib>
#include <utility>
#include "lhef.h"

namespace lhef {
Particles InitialStates(const LHEFEvent& lhe) {
    Particles initialstates;
    auto entry = lhe.particle_entries();
    std::for_each(entry.cbegin(), entry.cend(),
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
    auto entry = lhe.particle_entries();
    std::for_each(entry.cbegin(), entry.cend(),
                  [&] (const std::pair<int, Particle>& pmap) {
                      Particle p = pmap.second;
                      if (p.istup == 1) {
                          finalstates.push_back(p);
                      }
                  });
    return finalstates;
}

Particles ParticlesOf(const ParticleID& pid, const LHEFEvent& lhe) {
    Particles pars;
    auto entry = lhe.particle_entries();
    std::for_each(entry.cbegin(), entry.cend(),
                  [&] (const std::pair<int, Particle>& pmap) {
                      Particle p = pmap.second;
                      auto pos = std::find(pid.cbegin(), pid.cend(), p.idup);
                      if (!(pos == pid.cend())) {
                          pars.push_back(p);
                      }
                  });
    return pars;
}

Particle Mother(Particle p, const LHEFEvent& lhe) {
    int mo_line = p.mothup.first;
    auto entry = lhe.particle_entries();
    auto mo_pos = entry.find(mo_line);
    if (mo_pos == entry.end()) {  // mother particle not found
        return entry.at(1);
    } else {
        return entry.at(mo_line);
    }
}

Particle Ancestor(Particle p, const LHEFEvent& lhe) {
    Particle mother = Mother(p, lhe);
    if (mother.mothup.first == 1) {
        return mother;
    } else {
        return Ancestor(mother, lhe);
    }
}
}  // namespace lhef
