#include "parser.h"
#include <sstream>
#include <string>

namespace lhef {
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

Event ParseEvent(std::istream *is) {
    std::string evstr = EventStr(is);

    Event lhe;
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
        lhe.set_event(evinfo, entry);
    } else {
        lhe(Event::EventStatus::Empty);
    }
    return lhe;
}
}  // namespace lhef
