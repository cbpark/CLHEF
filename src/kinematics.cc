#include "kinematics.h"
#include <cmath>

namespace lhef {
double InvariantMass(const Energy& e,
                     const Px& px, const Py& py, const Pz& pz) {
    return std::sqrt(e.value * e.value - px.value * px.value
                     - py.value * py.value - pz.value * pz.value);
}
}  // namespace lhef
