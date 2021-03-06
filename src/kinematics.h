/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef CLHEF_SRC_KINEMATICS_H_
#define CLHEF_SRC_KINEMATICS_H_

#include <cmath>
#include <string>

namespace lhef {
struct Px {
    double value;
    Px() : value(0.0) {}
    explicit Px(double v) : value(v) {}
};

struct Py {
    double value;
    Py() : value(0.0) {}
    explicit Py(double v) : value(v) {}
};

struct Pz {
    double value;
    Pz() : value(0.0) {}
    explicit Pz(double v) : value(v) {}
};

struct Energy {
    double value;
    Energy() : value(0.0) {}
    explicit Energy(double v) : value(v) {}
};

double cosTheta(const Px &px, const Py &py, const Pz &pz);

double pseudoRapidity(const Px &px, const Py &py, const Pz &pz);

class FourMomentum {
private:
    Px px_;
    Py py_;
    Pz pz_;
    Energy e_;

public:
    FourMomentum() : px_(0), py_(0), pz_(0), e_(0) {}
    FourMomentum(const Energy &e, const Px &px, const Py &py, const Pz &pz)
        : px_(px), py_(py), pz_(pz), e_(e) {}

    double px() const { return px_.value; }
    double py() const { return py_.value; }
    double pz() const { return pz_.value; }
    double energy() const { return e_.value; }

    double pt() const { return std::hypot(px(), py()); }
    double phi() const {
        return px_.value == 0 && py_.value == 0 ? 0 : std::atan2(py_.value,
                                                                 px_.value);
    }
    double eta() const { return pseudoRapidity(px_, py_, pz_); }
    double mass() const {
        double m2 = e_.value * e_.value - px_.value * px_.value -
                    py_.value * py_.value - pz_.value * pz_.value;
        return m2 < 0 ? -std::sqrt(-m2) : std::sqrt(m2);
    }
};

std::string show(const FourMomentum &p);

double deltaPhi(const FourMomentum &p1, const FourMomentum &p2);

double deltaR(const FourMomentum &p1, const FourMomentum &p2);
}  // namespace lhef

#endif  // CLHEF_SRC_KINEMATICS_H_
