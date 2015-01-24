#include "type.h"

namespace lhef {
std::ostream& operator<<(std::ostream& os, const EventInfo& evinfo) {
    os << "EventInfo {nup=" << evinfo.nup
       << ",idprup=" << evinfo.idprup
       << ",xwgtup=" << evinfo.xwgtup
       << ",scalup=" << evinfo.scalup
       << ",aqedup=" << evinfo.aqedup
       << ",aqcdup=" << evinfo.aqcdup << "}";
    return os;
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

std::ostream& operator<<(std::ostream& os, const Particle& p) {
    os << "Particle {idup=" << p.idup
       << ",istup=" << p.istup
       << ",mothup=(" << p.mothup.first << "," << p.mothup.second << ")"
       << ",icolup=(" << p.icolup.first << "," << p.icolup.second << ")"
       << ",pup=(";
    for (auto momentum : p.pup) {
        os << momentum << ",";
    }
    os << "\b)"
       << ",vtimup=" << p.vtimup
       << ",spinup=" << p.spinup << "}";
    return os;
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

std::ostream& operator<<(std::ostream& os, const Particles& ps) {
    os << '[';
    for (auto p : ps) {
        os << p << ',';
    }
    os << "\b]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const EventEntry& entry) {
    os << "[";
    for (auto e : entry) {
        os << "(" << e.first
           << "," << e.second << "),";
    }
    os << "\b]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const LHEFEvent& lhe) {
    os << "LHEFEvent ("
       << lhe.event_info() << ","
       << lhe.particle_entries() << ")";
    return os;
}
}  // namespace lhef
