#include "event.h"
#include <iomanip>
#include <ios>
#include <map>

using std::to_string;

namespace lhef {
std::ostream& operator<<(std::ostream& os, const GlobalInfo& info) {
    os << "<init>\n";

    auto ss = os.precision();
    os << std::setw(9) << info.idbmup.first
       << std::setw(9) << info.idbmup.second
       << std::setprecision(11) << std::scientific << std::uppercase
       << std::setw(19) << info.ebmup.first
       << std::setw(19) << info.ebmup.second;
    os.precision(ss);
    os << std::setw(2) << info.pdfgup.first
       << std::setw(2) << info.pdfgup.second
       << std::setw(6) << info.pdfsup.first
       << std::setw(6) << info.pdfsup.second
       << std::setw(2) << info.idwtup
       << std::setw(3) << info.nprup << '\n';

    auto xsecup_it = info.xsecup.begin();
    auto xerrup_it = info.xerrup.begin();
    auto xmaxup_it = info.xmaxup.begin();
    auto lprup_it = info.lprup.begin();
    for ( ; xsecup_it != info.xsecup.end() &&
              xerrup_it != info.xerrup.end() &&
              xmaxup_it != info.xmaxup.end() &&
              lprup_it != info.lprup.end();
          ++xsecup_it, ++xerrup_it, ++xmaxup_it, ++lprup_it) {
        os << std::setprecision(11) << std::scientific << std::uppercase
           << std::setw(19) << *xsecup_it
           << std::setw(19) << *xerrup_it
           << std::setw(19) << *xmaxup_it;
        os.precision(ss);
        os << std::setw(4) << *lprup_it << '\n';
    }

    os << "</init>";
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

std::ostream& operator<<(std::ostream& os, const EventInfo& evinfo) {
    auto ss = os.precision();
    os << std::setw(2)  << evinfo.nup
       << std::setw(4)  << evinfo.idprup
       << std::setprecision(7) << std::scientific << std::uppercase
       << std::setw(15) << evinfo.xwgtup
       << std::setw(15) << evinfo.scalup
       << std::setw(15) << evinfo.aqedup
       << std::setw(15) << evinfo.aqcdup;
    os.precision(ss);
    return os;
}

const std::string show(const EventInfo& evinfo) {
    std::string evinfo_str =
        "EventInfo {nup=" + to_string(evinfo.nup)    +
        ",idprup="        + to_string(evinfo.idprup) +
        ",xwgtup="        + to_string(evinfo.xwgtup) +
        ",scalup="        + to_string(evinfo.scalup) +
        ",aqedup="        + to_string(evinfo.aqedup) +
        ",aqcdup="        + to_string(evinfo.aqcdup) + "}";
    return evinfo_str;
}

const std::string show(const EventEntry& entry) {
    std::string entry_str = "[";
    for (const auto& e : entry) {
        entry_str += "(" + to_string(e.first) + "," + show(e.second) + "),";
    }
    entry_str.pop_back();
    entry_str += "]";
    return entry_str;
}

std::ostream& operator<<(std::ostream& os, const Event& ev) {
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

const std::string show(const Event& ev) {
    std::string ev_str = "Event (";
    ev_str += show(ev.event_.first) + "," + show(ev.event_.second) + ")";
    return ev_str;
}
}  // namespace lhef
