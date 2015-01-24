#ifndef SRC_TYPE_H_
#define SRC_TYPE_H_

#include <array>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace lhef {
struct EventInfo {
    // Number of particle entries in the event.
    int nup;
    // ID of the process for the event.
    int idprup;
    // Event weight.
    double xwgtup;
    // Scale of the event in GeV.
    double scalup;
    // The QED coupling \alpha_{QED} used for the event.
    double aqedup;
    // The QCD coupling \alpha_{QCD} used for the event.
    double aqcdup;

    friend std::ostream& operator<<(std::ostream& os, const EventInfo& evinfo);
    friend std::istream& operator>>(std::istream& is, EventInfo& evinfo);
};

struct Particle {
    // Particle ID according to Particle Data Group convention.
    int idup;
    // Status code.
    int istup;
    // Index of first and last mother.
    std::pair<int, int> mothup;
    // Integer tag for the color flow line passing through the
    // (anti-)color of the particle.
    std::pair<int, int> icolup;
    // Lab frame momentum (P_x, P_y, P_z, E, M) of particle in GeV.
    std::array<double, 5> pup;
    // Invariant lifetime (distance from production to decay) in mm.
    double vtimup;
    // Consine of the angle between the spin-vector of particle and the
    // three-momentum of the decaying particle, specified in the lab frame.
    double spinup;

    bool operator<(const Particle& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const Particle& p);
    friend std::istream& operator>>(std::istream& is, Particle& p);
};

using Particles = std::vector<Particle>;
std::ostream& operator<<(std::ostream& os, const Particles& ps);

using EventEntry = std::unordered_map<int, Particle>;
std::ostream& operator<<(std::ostream& os, const EventEntry& entry);

class LHEFEvent {
public:
    enum EventStatus {kEmpty, kFill};

private:
    EventStatus status_;
    std::pair<EventInfo, EventEntry> event_;

public:
    explicit LHEFEvent(EventStatus s = kEmpty) : status_(s) { }

    void set_event(const EventInfo& evinfo, const EventEntry& entry) {
        event_ = std::make_pair(evinfo, entry);
    }
    EventInfo event_info() const {
        return event_.first;
    }
    EventEntry particle_entries() const {
        return event_.second;
    }
    bool empty() const {
        return (status_ == kEmpty? true : false);
    }
    void operator()(EventStatus s) {
        status_ = s;
    }
    friend std::ostream& operator<<(std::ostream& os, const LHEFEvent& e);
};

using ParticleID = std::vector<int>;

using ParticleLines = std::vector<int>;
}  // namespace lhef

#endif  // SRC_TYPE_H_
