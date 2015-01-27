#include "lhef.h"
#include <algorithm>
#include <functional>

namespace lhef {
Particles SelectParticlesBy(std::function<bool(const Particle&)> pred,
                            const LHEFEvent& lhe) {
    Particles ps;
    auto entry = lhe.particle_entries();
    for (const auto& e : entry) {
        auto p = e.second;
        if (pred(p)) {
            ps.push_back(p);
        }
    }
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
    return std::find(pid.cbegin(), pid.cend(), p.idup) != pid.cend();
}

Particles ParticlesOf(const ParticleID& pid, const LHEFEvent& lhe) {
    auto pred = [&pid] (const Particle& p) {
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
    auto mo_line = p.mothup.first;
    auto entry = lhe.particle_entries();
    if (entry.find(mo_line) == entry.end()) {  // mother particle not found
        return entry.at(1);
    } else {
        return entry.at(mo_line);
    }
}

Particle Ancestor(const Particle& p, const LHEFEvent& lhe) {
    auto mother = Mother(p, lhe);
    return mother.mothup.first == 1? mother : Ancestor(mother, lhe);
}

Particles Daughters(int pline, const LHEFEvent& lhe) {
    auto pred = [pline] (const Particle& p) {
        return p.mothup.first == pline;
    };
    return SelectParticlesBy(pred, lhe);
}

bool IsInMotherLines(int pline, const Particle& p, const LHEFEvent& lhe) {
    auto mo_line = p.mothup.first;
    if (mo_line == 1) {
        return false;
    } else if (mo_line == pline) {
        return true;
    } else {
        auto direct_mother = Mother(p, lhe);
        return IsInMotherLines(pline, direct_mother, lhe);
    }
}

Particles FinalDaughters(int pline, const LHEFEvent& lhe) {
    Particles finalstates = FinalStates(lhe);
    auto pos = std::remove_if(finalstates.begin(), finalstates.end(),
                              [pline, &lhe] (const Particle& p) {
                                  return !IsInMotherLines(pline, p, lhe);
                              });
    finalstates.erase(pos, finalstates.end());
    return finalstates;
}
}  // namespace lhef
