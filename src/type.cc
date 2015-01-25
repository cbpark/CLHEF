#include "type.h"

namespace lhef {
const std::string EventInfo::show() const {
    std::string evinfo_str =
        "EventInfo {nup=" + std::to_string(nup)    +
        ",idprup="        + std::to_string(idprup) +
        ",xwgtup="        + std::to_string(xwgtup) +
        ",scalup="        + std::to_string(scalup) +
        ",aqedup="        + std::to_string(aqedup) +
        ",aqcdup="        + std::to_string(aqcdup) + "}";
    return evinfo_str;
}

std::istream& operator>>(std::istream& is, EventInfo& evinfo) {
    is >> evinfo.nup
       >> evinfo.idprup
       >> evinfo.xwgtup
       >> evinfo.scalup
       >> evinfo.aqedup
       >> evinfo.aqcdup;
    return is;
}

double TransMomentumSq(const Particle& p) {
    return p.pup[0] * p.pup[0] + p.pup[1] * p.pup[1];
}

bool Particle::operator<(const Particle& rhs) const {
    return TransMomentumSq(*this) < TransMomentumSq(rhs);
}

const std::string Particle::show() const {
    std::string p_str =
        "Particle {idup=" + std::to_string(idup)          +
        ",istup="         + std::to_string(istup)         +
        ",mothup=("       + std::to_string(mothup.first)  +
        ","               + std::to_string(mothup.second) + ")" +
        ",icolup=("       + std::to_string(icolup.first)  +
        ","               + std::to_string(icolup.second) + ")" +
        ",pup=(";

    for (const auto &momentum : pup) {
        p_str += std::to_string(momentum) + ",";
    }
    p_str.pop_back();

    p_str = p_str + ")" +
        ",vtimup=" + std::to_string(vtimup) +
        ",spinup=" + std::to_string(spinup) + "}";

    return p_str;
}

std::istream& operator>>(std::istream& is, Particle& p) {
    is >> p.idup
       >> p.istup
       >> p.mothup.first >> p.mothup.second
       >> p.icolup.first >> p.icolup.second
       >> p.pup[0] >> p.pup[1] >> p.pup[2] >> p.pup[3] >> p.pup[4]
       >> p.vtimup
       >> p.spinup;
    return is;
}

const std::string show(const Particles& ps) {
    std::string ps_str = "[";
    for (const auto &p : ps) {
        ps_str += p.show() + ",";
    }
    ps_str.pop_back();
    ps_str += "]";
    return ps_str;
}

const std::string show(const EventEntry& entry) {
    std::string entry_str = "[";
    for (const auto& e : entry) {
        entry_str +=
            "(" + std::to_string(e.first) +
            "," + e.second.show()         + "),";
    }
    entry_str.pop_back();
    entry_str += "]";
    return entry_str;
}

const std::string LHEFEvent::show() const {
    std::string ev_str = "LHEFEvent (";
    ev_str += event_.first.show() + "," + lhef::show(event_.second) + ")";
    return ev_str;
}
}  // namespace lhef
