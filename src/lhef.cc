#include "lhef.h"
#include <algorithm>
#include <functional>
#include <string>
#include <utility>

namespace lhef {
std::string openingLine() { return "<LesHouchesEvents version=\"1.0\">"; }

std::string closingLine() { return "</LesHouchesEvents>"; }

Particles selectParticlesBy(std::function<bool(const Particle&)> pred,
                            const Event& lhe) {
    Particles ps;
    auto entry = lhe.particleEntries();
    for (const auto& e : entry) {
        auto particle = e.second;
        if (pred(particle)) ps.push_back(std::move(particle));
    }
    return ps;
}

Particles initialStates(const Event& lhe) {
    auto pred = [](const Particle& p) { return p.mother().first == 1; };
    return selectParticlesBy(pred, lhe);
}

Particles finalStates(const Event& lhe) {
    auto pred = [](const Particle& p) { return p.status() == 1; };
    return selectParticlesBy(pred, lhe);
}

bool particleExists(const ParticleID& pid, const Particle& p) {
    return std::find(pid.cbegin(), pid.cend(), p.pid()) != pid.cend();
}

Particles particlesOf(const ParticleID& pid, const Event& lhe) {
    auto pred = [&pid](const Particle& p) { return particleExists(pid, p); };
    return selectParticlesBy(pred, lhe);
}

ParticleLines particleLinesOf(const ParticleID& pid, const Event& lhe) {
    ParticleLines line;
    auto entry = lhe.particleEntries();
    for (const auto& e : entry) {
        auto particle = e.second;
        if (particleExists(pid, particle)) line.push_back(std::move(e.first));
    }
    return line;
}

Particle mother(const Particle& p, const Event& lhe) {
    auto mo_line = p.mother().first;
    auto entry = lhe.particleEntries();
    if (entry.find(mo_line) == entry.end()) {  // mother particle not found
        return entry.at(1);
    } else {
        return entry.at(mo_line);
    }
}

Particle ancestor(const Particle& p, const Event& lhe) {
    auto m = mother(p, lhe);
    return m.mother().first == 1 ? m : ancestor(m, lhe);
}

Particles daughters(int pline, const Event& lhe) {
    auto pred = [pline](const Particle& p) {
        return p.mother().first == pline;
    };
    return selectParticlesBy(pred, lhe);
}

bool isInMotherLines(int pline, const Particle& p, const Event& lhe) {
    auto mo_line = p.mother().first;
    if (mo_line == 1) {
        return false;
    } else if (mo_line == pline) {
        return true;
    } else {
        auto direct_mother = mother(p, lhe);
        return isInMotherLines(pline, direct_mother, lhe);
    }
}

Particles finalDaughters(int pline, const Event& lhe) {
    Particles finalstates = finalStates(lhe);
    auto pos = std::remove_if(finalstates.begin(), finalstates.end(),
                              [pline, &lhe](const Particle& p) {
                                  return !isInMotherLines(pline, p, lhe);
                              });
    finalstates.erase(pos, finalstates.end());
    return finalstates;
}
}  // namespace lhef
