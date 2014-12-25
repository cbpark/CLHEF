#include <sstream>
#include <string>
#include "lhefevent.h"

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

std::ostream& operator<<(std::ostream& os, const EventEntry& entry) {
    os << "[";
    for (auto e : entry) {
        os << "(" << e.first
           << "," << e.second << "),";
    }
    os << "\b]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const LHEFEvent& e) {
    os << "LHEFEvent ("
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
        } else {  // end of the event lines reached
            break;
        }
    }
    return event_line;
}

LHEFEvent ParseEvent(std::istream *is) {
    std::string evstr = EventStr(is);

    LHEFEvent lhe;
    if (!evstr.empty()) {
        std::istringstream iss(evstr);
        EventInfo evinfo;
        iss >> evinfo;

        Particle p;
        EventEntry entry;
        for (int i = 0; i < evinfo.nup; ++i) {
            iss >> p;
            entry.insert({i + 1, p});
        }
        lhe.event = std::make_pair(evinfo, entry);
        lhe(LHEFEvent::kFill);
    } else {
        lhe(LHEFEvent::kEmpty);
    }

    return lhe;
}
}  // namespace lhef
