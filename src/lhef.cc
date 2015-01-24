#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>
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

bool ParticleExists(const ParticleID& pid, const Particle& p) {
    auto pos = std::find(pid.cbegin(), pid.cend(), p.idup);
    if (pos == pid.end()) {
        return false;
    } else {
        return true;
    }
}

Particles ParticlesOf(const ParticleID& pid, const LHEFEvent& lhe) {
    Particles pars;
    auto entry = lhe.particle_entries();
    std::for_each(entry.cbegin(), entry.cend(),
                  [&] (const std::pair<int, Particle>& pmap) {
                      Particle p = pmap.second;
                      if (ParticleExists(pid, p)) {
                          pars.push_back(p);
                      }
                  });
    return pars;
}

ParticleLines ParticleLinesOf(const ParticleID& pid, const LHEFEvent& lhe) {
    std::vector<int> line;
    auto entry = lhe.particle_entries();
    for (const auto& e : entry) {
        Particle p = e.second;
        if (ParticleExists(pid, p)) {
            line.push_back(e.first);
        }
    }
    return line;
}

Particle Mother(const Particle& p, const LHEFEvent& lhe) {
    int mo_line = p.mothup.first;
    auto entry = lhe.particle_entries();
    auto mo_pos = entry.find(mo_line);
    if (mo_pos == entry.end()) {  // mother particle not found
        return entry.at(1);
    } else {
        return entry.at(mo_line);
    }
}

Particle Ancestor(const Particle& p, const LHEFEvent& lhe) {
    Particle mother = Mother(p, lhe);
    if (mother.mothup.first == 1) {
        return mother;
    } else {
        return Ancestor(mother, lhe);
    }
}

Particles Daughters(int pline, const LHEFEvent& lhe) {
    Particles daughters;
    auto entry = lhe.particle_entries();
    std::for_each(entry.cbegin(), entry.cend(),
                  [&] (const std::pair<int, Particle>& pmap) {
                      Particle p = pmap.second;
                      if (p.mothup.first == pline) {
                          daughters.push_back(p);
                      }
                  });
    return daughters;
}

bool IsInMotherLine(int pline, const Particle& p, const LHEFEvent& lhe) {
    if (p.mothup.first == 1) {
        return false;
    } else if (p.mothup.first == pline) {
        return true;
    } else {
        Particle direct_mother = Mother(p, lhe);
        return IsInMotherLine(pline, direct_mother, lhe);
    }
}

Particles FinalDaughters(int pline, const LHEFEvent& lhe) {
    Particles finalstates = FinalStates(lhe);
    auto pos = std::remove_if(finalstates.begin(), finalstates.end(),
                              [&] (const Particle& p) {
                                  return !IsInMotherLine(pline, p, lhe);
                              });
    finalstates.erase(pos, finalstates.end());
    return finalstates;
}
}  // namespace lhef
