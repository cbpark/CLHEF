#include <fstream>
#include <iostream>
#include "lhef.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: testparse input\n"
                  << "    - input: Input file in "
                  << "Les Houches Event File format\n";
        return 1;
    }

    std::ifstream filename;
    filename.open(argv[1]);
    if (!filename) {
        std::cerr << "-- Cannot open input file \"" << argv[1] << "\".\n";
        return 1;
    } else {
        std::cout << "-- Reading \"" << argv[1] << "\" ...\n";
    }

    lhef::LHEFEvent lhe;
    lhef::Particles initstates;
    lhef::Particles finalstates;
    lhef::Particles leptons;
    lhef::ParticleID is_lepton = {11, -11, 13, -13};
    lhef::Particle lep_anc;
    int num_eve = 0;
    while (true) {
        lhe = lhef::ParseEvent(&filename);

        if (!lhe.empty()) {
            ++num_eve;
            std::cout << "-- Event number: " << num_eve << '\n' << lhe << '\n';
            initstates = lhef::InitialStates(lhe);
            std::cout << "---- Initial-state particles:\n"
                      << initstates << '\n';
            finalstates = lhef::FinalStates(lhe);
            std::cout << "---- Final-state particles:\n" << finalstates << '\n';
            leptons = lhef::ParticlesOf(is_lepton, lhe);
            std::cout << "---- Leptons:\n" << leptons << '\n';
            lep_anc = lhef::Ancestor(leptons.front(), lhe);
            std::cout << "---- Ancestor of one lepton\n" << lep_anc << '\n';
        } else {
            break;
        }
    }

    std::cout << "-- " << num_eve << " events parsed.\n";
    filename.close();
}
