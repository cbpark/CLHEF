#ifndef SRC_KINEMATICS_H_
#define SRC_KINEMATICS_H_

namespace lhef {
struct Px {
    double value;
    explicit Px(double v) : value(v) { }
};

struct Py {
    double value;
    explicit Py(double v) : value(v) { }
};

struct Pz {
    double value;
    explicit Pz(double v) : value(v) { }
};

struct Energy {
    double value;
    explicit Energy(double v) : value(v) { }
};

double InvariantMass(const Energy& e, const Px& px, const Py& py, const Pz& pz);
}  // namespace lhef

#endif  // SRC_KINEMATICS_H_
