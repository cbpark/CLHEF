#ifndef SRC_TYPE_H_
#define SRC_TYPE_H_

#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace lhef {
struct EventInfo {
    // Number of particle entries in the event.
    int nup = 0;
    // ID of the process for the event.
    int idprup = 0;
    // Event weight.
    double xwgtup = 0.0;
    // Scale of the event in GeV.
    double scalup = 0.0;
    // The QED coupling \alpha_{QED} used for the event.
    double aqedup = 0.0;
    // The QCD coupling \alpha_{QCD} used for the event.
    double aqcdup = 0.0;

    EventInfo() { }
    EventInfo(int _nup, int _idprup,
              double _xwgtup, double _scalup, double _aqedup, double _aqcdup)
        : nup(_nup), idprup(_idprup),
          xwgtup(_xwgtup), scalup(_scalup), aqedup(_aqedup), aqcdup(_aqcdup) { }

    friend std::istream& operator>>(std::istream& is, EventInfo& evinfo);
    friend std::ostream& operator<<(std::ostream& os, const EventInfo& evinfo);
};

const std::string show(const EventInfo& evinfo);

struct Particle {
    // Particle ID according to Particle Data Group convention.
    int idup = 0;
    // Status code.
    int istup = 0;
    // Index of first and last mother.
    std::pair<int, int> mothup{0, 0};
    // Integer tag for the color flow line passing through the
    // (anti-)color of the particle.
    std::pair<int, int> icolup{0, 0};
    // Lab frame momentum (P_x, P_y, P_z, E, M) of particle in GeV.
    std::array<double, 5> pup{{0.0, 0.0, 0.0, 0.0, 0.0}};
    // Invariant lifetime (distance from production to decay) in mm.
    double vtimup = 0.0;
    // Consine of the angle between the spin-vector of particle and the
    // three-momentum of the decaying particle, specified in the lab frame.
    double spinup = 0.0;

    Particle() { }
    Particle(int _idup, int _istdup,
             int _mothup1, int _mothup2, int _icolup1, int _icolup2,
             double _pup1, double _pup2, double _pup3,
             double _pup4, double _pup5, double _vtimup, double _spinup)
        : idup(_idup), istup(_istdup),
          mothup({_mothup1, _mothup2}), icolup({_icolup1, _icolup2}),
          pup({{_pup1, _pup2, _pup3, _pup4, _pup5}}),
          vtimup(_vtimup), spinup(_spinup) { }

    bool operator<(const Particle& rhs) const;
    bool operator>(const Particle& rhs) const;
    friend std::istream& operator>>(std::istream& is, Particle& p);
    friend std::ostream& operator<<(std::ostream& os, const Particle& p);
};

const std::string show(const Particle& p);

using Particles = std::vector<Particle>;
const std::string show(const Particles& ps);

using EventEntry = std::unordered_map<int, Particle>;
const std::string show(const EventEntry& entry);

class Event {
public:
    enum class EventStatus {Empty, Fill};

private:
    EventStatus status_;
    std::pair<EventInfo, EventEntry> event_;

public:
    explicit Event(EventStatus s = EventStatus::Empty) : status_(s) { }
    Event(const EventInfo& evinfo, const EventEntry& ev)
        : status_(EventStatus::Fill), event_({evinfo, ev}) { }

    void set_event(const EventInfo& evinfo, const EventEntry& entry) {
        status_ = EventStatus::Fill;
        event_ = std::make_pair(evinfo, entry);
    }
    EventInfo event_info() const {
        return event_.first;
    }
    EventEntry particle_entries() const {
        return event_.second;
    }
    bool empty() const {
        return status_ == EventStatus::Empty;
    }
    void operator()(const EventStatus& s) {
        status_ = s;
    }

    friend std::ostream& operator<<(std::ostream& os, const Event& ev);
};

const std::string show(const Event& ev);

using ParticleID = std::vector<int>;

using ParticleLines = std::vector<int>;
}  // namespace lhef

#endif  // SRC_TYPE_H_
