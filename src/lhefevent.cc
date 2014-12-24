/*
 * Copyright (c) 2014 Chan Beom Park
 */

#include "lhefevent.h"
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
       << "pup=(";
    for (auto momentum : p.pup) {
        os << momentum << ",";
    }
    os.seekp(-1, std::ios_base::cur);
    os << ")"
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
    os.seekp(-1, std::ios_base::cur);
    os << "]";
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

std::string EventLines(std::istream *is) {
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
}  // namespace lhef
