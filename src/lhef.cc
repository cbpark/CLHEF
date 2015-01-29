#include "lhef.h"
#include <algorithm>
#include <functional>
#include <utility>

namespace lhef {
Particles SelectParticlesBy(std::function<bool(const Particle&)> pred,
                            const Event& lhe) {
    Particles ps;
    auto entry = lhe.particle_entries();
    for (const auto& e : entry) {
        auto p = e.second;
        if (pred(p)) {
            ps.push_back(std::move(p));
        }
    }
    return ps;
}

Particles InitialStates(const Event& lhe) {
    auto pred = [] (const Particle& p) {
        return p.mother().first == 1;
    };
    return SelectParticlesBy(pred, lhe);
}

Particles FinalStates(const Event& lhe) {
    auto pred = [] (const Particle& p) {
        return p.status() == 1;
    };
    return SelectParticlesBy(pred, lhe);
}

bool ParticleExists(const ParticleID& pid, const Particle& p) {
    return std::find(pid.cbegin(), pid.cend(), p.pid()) != pid.cend();
}

Particles ParticlesOf(const ParticleID& pid, const Event& lhe) {
    auto pred = [&pid] (const Particle& p) {
        return ParticleExists(pid, p);
    };
    return SelectParticlesBy(pred, lhe);
}

ParticleLines ParticleLinesOf(const ParticleID& pid, const Event& lhe) {
    ParticleLines line;
    auto entry = lhe.particle_entries();
    for (const auto& e : entry) {
        auto p = e.second;
        if (ParticleExists(pid, p)) {
            line.push_back(std::move(e.first));
        }
    }
    return line;
}

Particle Mother(const Particle& p, const Event& lhe) {
    auto mo_line = p.mother().first;
    auto entry = lhe.particle_entries();
    if (entry.find(mo_line) == entry.end()) {  // mother particle not found
        return entry.at(1);
    } else {
        return entry.at(mo_line);
    }
}

Particle Ancestor(const Particle& p, const Event& lhe) {
    auto mother = Mother(p, lhe);
    return mother.mother().first == 1? mother : Ancestor(mother, lhe);
}

Particles Daughters(int pline, const Event& lhe) {
    auto pred = [pline] (const Particle& p) {
        return p.mother().first == pline;
    };
    return SelectParticlesBy(pred, lhe);
}

bool IsInMotherLines(int pline, const Particle& p, const Event& lhe) {
    auto mo_line = p.mother().first;
    if (mo_line == 1) {
        return false;
    } else if (mo_line == pline) {
        return true;
    } else {
        auto direct_mother = Mother(p, lhe);
        return IsInMotherLines(pline, direct_mother, lhe);
    }
}

Particles FinalDaughters(int pline, const Event& lhe) {
    Particles finalstates = FinalStates(lhe);
    auto pos = std::remove_if(finalstates.begin(), finalstates.end(),
                              [pline, &lhe] (const Particle& p) {
                                  return !IsInMotherLines(pline, p, lhe);
                              });
    finalstates.erase(pos, finalstates.end());
    return finalstates;
}
}  // namespace lhef
