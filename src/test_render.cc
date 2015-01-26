#include <iostream>
#include <vector>
#include "type.h"

int main() {
    lhef::EventInfo evinfo(12, 0,
                           0.2504000E-03, 0.1859065E+03,
                           0.7546771E-02, 0.1168023E+00);

    lhef::Particles ps;
    ps.push_back(lhef::Particle(21, -1, 0, 0, 501, 502,
                                0.00000000000E+00, 0.00000000000E+00,
                                0.60610394285E+02, 0.60610394285E+02,
                                0.00000000000E+00, 0., -1.));
    ps.push_back(lhef::Particle(21, -1, 0, 0, 502, 503,
                                0.00000000000E+00, 0.00000000000E+00,
                                -0.56770401776E+03, 0.56770401776E+03,
                                0.00000000000E+00, 0., -1.));
    ps.push_back(lhef::Particle(-6, 2, 1, 2, 0, 503,
                                -0.45926782514E+02, -0.44824776005E+02,
                                -0.23401002797E+03, 0.29886773829E+03,
                                0.17447837088E+03, 0., 0.));
    ps.push_back(lhef::Particle(-24, 2, 3, 3, 0, 0,
                                -0.76461069853E+02, -0.96784120001E+01,
                                -0.22537898176E+03, 0.25128418480E+03,
                                0.80050541847E+02, 0., 0.));
    ps.push_back(lhef::Particle(6, 2, 1, 2, 501, 0,
                                0.45926782514E+02, 0.44824776005E+02,
                                -0.27308359550E+03, 0.32944667375E+03,
                                0.17274817168E+03, 0., 0.));
    ps.push_back(lhef::Particle(24, 2, 5, 5, 0, 0,
                                0.61324315926E+02, 0.90069150727E+02,
                                -0.18480823476E+03, 0.22895405317E+03,
                                0.79954682114E+02, 0., 0.));
    ps.push_back(lhef::Particle(5, 1, 5, 5, 501, 0,
                                -0.15397533412E+02, -0.45244374722E+02,
                                -0.88275360737E+02, 0.10049262058E+03,
                                0.46999998093E+01, 0., -1.));
    ps.push_back(lhef::Particle(-11, 1, 6, 6, 0, 0,
                                0.13410537059E+02, 0.46106119786E+01,
                                -0.94980636541E+02, 0.96033439826E+02,
                                0.00000000000E+00, 0., 1.));
    ps.push_back(lhef::Particle(12, 1, 6, 6, 0, 0,
                                0.47913778867E+02, 0.85458538748E+02,
                                -0.89827598219E+02, 0.13292061335E+03,
                                0.00000000000E+00, 0., -1.));
    ps.push_back(lhef::Particle(-5, 1, 3, 3, 0, 503,
                                0.30534287339E+02, -0.35146364005E+02,
                                -0.86310462169E+01, 0.47583553494E+02,
                                0.46999998093E+01, 0., 1.));
    ps.push_back(lhef::Particle(13, 1, 4, 4, 0, 0,
                                -0.70229326315E+02, 0.17944688553E+02,
                                -0.10480376160E+03, 0.12742840566E+03,
                                0.00000000000E+00, 0., -1.));
    ps.push_back(lhef::Particle(-14, 1, 4, 4, 0, 0,
                                -0.62317435380E+01, -0.27623100553E+02,
                                -0.12057522016E+03, 0.12385577914E+03,
                                0.00000000000E+00, 0., 1.));

    lhef::EventEntry entry;
    int i = 1;
    for (const auto& p : ps) {
        entry.insert({i, p});
        ++i;
    }

    lhef::LHEFEvent ev(evinfo, entry);
    std::cout << "-- Rendering LHEF Event ...\n";
    std::cout << ev << '\n';
    std::cout << "-- Rendering done.\n";
}