#include "type.h"

namespace lhef {
std::istream& operator>>(std::istream& is, EventInfo& evinfo) {
    is >> evinfo.nup
       >> evinfo.idprup
       >> evinfo.xwgtup
       >> evinfo.scalup
       >> evinfo.aqedup
       >> evinfo.aqcdup;
    return is;
}

const std::string show(const EventInfo& evinfo) {
    std::string evinfo_str =
        "EventInfo {nup=" + std::to_string(evinfo.nup)    +
        ",idprup="        + std::to_string(evinfo.idprup) +
        ",xwgtup="        + std::to_string(evinfo.xwgtup) +
        ",scalup="        + std::to_string(evinfo.scalup) +
        ",aqedup="        + std::to_string(evinfo.aqedup) +
        ",aqcdup="        + std::to_string(evinfo.aqcdup) + "}";
    return evinfo_str;
}

double TransMomentumSq(const Particle& p) {
    return p.pup[0] * p.pup[0] + p.pup[1] * p.pup[1];
}

bool Particle::operator<(const Particle& rhs) const {
    return TransMomentumSq(*this) < TransMomentumSq(rhs);
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

const std::string show(const Particle& p) {
    std::string p_str =
        "Particle {idup=" + std::to_string(p.idup)          +
        ",istup="         + std::to_string(p.istup)         +
        ",mothup=("       + std::to_string(p.mothup.first)  +
        ","               + std::to_string(p.mothup.second) + ")" +
        ",icolup=("       + std::to_string(p.icolup.first)  +
        ","               + std::to_string(p.icolup.second) + ")" +
        ",pup=(";

    for (const auto &momentum : p.pup) {
        p_str += std::to_string(momentum) + ",";
    }
    p_str.pop_back();

    p_str = p_str + ")" +
        ",vtimup=" + std::to_string(p.vtimup) +
        ",spinup=" + std::to_string(p.spinup) + "}";

    return p_str;
}

const std::string show(const Particles& ps) {
    std::string ps_str = "[";
    for (const auto &p : ps) {
        ps_str += show(p) + ",";
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
            "," + show(e.second)         + "),";
    }
    entry_str.pop_back();
    entry_str += "]";
    return entry_str;
}

const std::string show(const LHEFEvent& ev) {
    std::string ev_str = "LHEFEvent (";
    ev_str +=
        show(ev.event_info())       + "," +
        show(ev.particle_entries()) + ")";
    return ev_str;
}
}  // namespace lhef
