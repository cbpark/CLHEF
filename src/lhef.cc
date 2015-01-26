#include "lhef.h"
#include <algorithm>
#include <functional>

namespace lhef {
Particles SelectParticlesBy(std::function<bool(const Particle&)> pred,
                            const LHEFEvent& lhe) {
    Particles ps;
    auto entry = lhe.particle_entries();
    std::for_each(entry.cbegin(), entry.cend(),
                  [&] (const EventEntry::value_type& pmap) {
                      auto p = pmap.second;
                      if (pred(p)) {
                          ps.push_back(p);
                      }});
    return ps;
}

Particles InitialStates(const LHEFEvent& lhe) {
    auto pred = [] (const Particle& p) {
        return p.mothup.first == 1;
    };
    return SelectParticlesBy(pred, lhe);
}

Particles FinalStates(const LHEFEvent& lhe) {
    auto pred = [] (const Particle& p) {
        return p.istup == 1;
    };
    return SelectParticlesBy(pred, lhe);
}

bool ParticleExists(const ParticleID& pid, const Particle& p) {
    return std::any_of(pid.cbegin(), pid.cend(),
                       [&] (const int& id) {
                           return id == p.idup;
                       });
}

Particles ParticlesOf(const ParticleID& pid, const LHEFEvent& lhe) {
    auto pred = [&] (const Particle& p) {
        return ParticleExists(pid, p);
    };
    return SelectParticlesBy(pred, lhe);
}

ParticleLines ParticleLinesOf(const ParticleID& pid, const LHEFEvent& lhe) {
    ParticleLines line;
    auto entry = lhe.particle_entries();
    for (const auto& e : entry) {
        auto p = e.second;
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
    return mother.mothup.first == 1? mother : Ancestor(mother, lhe);
}

Particles Daughters(int pline, const LHEFEvent& lhe) {
    auto pred = [&] (const Particle& p) {
        return p.mothup.first == pline;
    };
    return SelectParticlesBy(pred, lhe);
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
