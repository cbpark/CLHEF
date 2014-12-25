#ifndef SRC_LHEFEVENT_H_
#define SRC_LHEFEVENT_H_

#include <array>
#include <cmath>
#include <ostream>
#include <unordered_map>
#include <string>
#include <utility>

namespace lhef {
struct EventInfo {
    int nup;
    int idprup;
    double xwgtup;
    double scalup;
    double aqedup;
    double aqcdup;

    friend std::ostream& operator<<(std::ostream& os, const EventInfo& evinfo);
};

struct Particle {
    int idup;
    int istup;
    std::pair<int, int> mothup;
    std::pair<int, int> icolup;
    std::array<double, 5> pup;
    double vtimup;
    double spinup;

    double p_transverse() const {
        return std::sqrt(pup[0] * pup[0] + pup[1] * pup[1]);
    }
    bool operator<(const Particle& rhs) const {
        return p_transverse() < rhs.p_transverse();
    }
    friend std::ostream& operator<<(std::ostream& os, const Particle& p);
};

struct EventEntry {
    std::unordered_map<int, Particle> particles;

    friend std::ostream& operator<<(std::ostream& os, const EventEntry& ps);
};

class Event {
public:
    enum EventStatus {kEmpty, kFill};
private:
    EventStatus status_;
public:
    std::pair<EventInfo, EventEntry> event;

    explicit Event(EventStatus s = kEmpty) : status_(s) { }
    bool empty() const {
        return (status_ == kEmpty? true : false);
    }
    void operator()(EventStatus s) {
        status_ = s;
    }
    friend std::ostream& operator<<(std::ostream& os, const Event& e);
};

Event Parse(std::istream *is);
}  // namespace lhef

#endif  // SRC_LHEFEVENT_H_
