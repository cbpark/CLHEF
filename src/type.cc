#include "type.h"
#include <iomanip>
#include <ios>
#include <map>

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

std::ostream& operator<<(std::ostream& os, const EventInfo& evinfo) {
    std::streamsize ss = os.precision();
    os << std::setw(2) << evinfo.nup
       << ' ' << std::setw(3) << evinfo.idprup
       << std::setprecision(7) << std::scientific << std::uppercase
       << ' ' << std::setw(14) << evinfo.xwgtup
       << ' ' << std::setw(14) << evinfo.scalup
       << ' ' << std::setw(14) << evinfo.aqedup
       << ' ' << std::setw(14) << evinfo.aqcdup;
    os.precision(ss);
    return os;
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

std::ostream& operator<<(std::ostream& os, const Particle& p) {
    os << ' ' << std::setw(8) << p.idup
       << ' ' << std::setw(4) << p.istup
       << ' ' << std::setw(4) << p.mothup.first
       << ' ' << std::setw(4) << p.mothup.second
       << ' ' << std::setw(4) << p.icolup.first
       << ' ' << std::setw(4) << p.icolup.second;

    std::streamsize ss = os.precision();

    os << std::setprecision(11) << std::scientific << std::uppercase;
    for (const auto& momentum : p.pup) {
        os << ' ' << std::setw(18) << momentum;
    }

    os << std::fixed << std::setprecision(0)
       << ' ' << std::setw(1) << p.vtimup << '.'
       << ' ' << std::setw(2) << p.spinup << '.';
    os.precision(ss);

    return os;
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

std::ostream& operator<<(std::ostream& os, const LHEFEvent& ev) {
    os << "<event>\n"
       << ev.event_.first << '\n';

    // EventEntry is unordered_map. It has to be ordered.
    std::map<int, Particle> entry_ordered(ev.event_.second.cbegin(),
                                          ev.event_.second.cend());
    for (const auto& entry : entry_ordered) {
        os << entry.second << '\n';
    }

    os << "</event>";
    return os;
}

const std::string show(const LHEFEvent& ev) {
    std::string ev_str = "LHEFEvent (";
    ev_str +=
        show(ev.event_info())       + "," +
        show(ev.particle_entries()) + ")";
    return ev_str;
}
}  // namespace lhef
