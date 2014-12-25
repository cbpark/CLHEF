#include "lhefevent.h"
#include <iostream>
#include <sstream>
#include <string>

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

std::ostream& operator<<(std::ostream& os, const EventEntry& ps) {
    os << "[";
    for (auto p : ps.particles) {
        os << "(" << p.first
           << "," << p.second << "),";
    }
    os << "\b]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Event& e) {
    os << "Event ("
       << e.event.first << ","
       << e.event.second << ")";
    return os;
}

void SkipTillEventLine(std::istream *is) {
    std::string line;
    while (std::getline(*is, line)
           && line.find("<event") == std::string::npos) {
        continue;
    }
}

std::string EventStr(std::istream *is) {
    SkipTillEventLine(is);

    std::string event_line(""), line;
    while (std::getline(*is, line)) {
        if (line.find("</event") == std::string::npos) {
            if (line.front() == '#') {  // comment line
                continue;
            } else {
                event_line += line + '\n';
            }
        } else {
            break;
        }
    }
    return event_line;
}

Event Parse(std::istream *is) {
    std::string evstr = EventStr(is);

    Event ev;
    if (!evstr.empty()) {
        std::istringstream iss(evstr);
        EventInfo einfo;
        iss >> einfo.nup
            >> einfo.idprup
            >> einfo.xwgtup
            >> einfo.scalup
            >> einfo.aqedup
            >> einfo.aqcdup;

        Particle p;
        EventEntry entry;
        for (int i = 0; i < einfo.nup; ++i) {
            int linenum;
            iss >> linenum
                >> p.idup
                >> p.istup
                >> p.mothup.first >> p.mothup.second
                >> p.icolup.first >> p.icolup.second
                >> p.pup[0] >> p.pup[1] >> p.pup[2] >> p.pup[3] >> p.pup[4]
                >> p.vtimup
                >> p.spinup;
            entry.particles.insert({linenum, p});
        }
        ev.event = std::make_pair(einfo, entry);
        ev(Event::kFill);
    } else {
        ev(Event::kEmpty);
    }

    return ev;
}
}  // namespace lhef
