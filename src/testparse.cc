#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include "lhef.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: testparse input\n"
                  << "    - input: Input file in "
                  << "Les Houches Event File format\n";
        return 1;
    }

    std::ifstream filename(argv[1]);
    if (!filename) {
        std::cerr << "-- Cannot open input file \"" << argv[1] << "\".\n";
        return 1;
    } else {
        std::cout << "-- Reading \"" << argv[1] << "\" ...\n";
    }

    lhef::LHEFEvent lhe = lhef::ParseEvent(&filename);
    lhef::Particles initstates;
    lhef::Particles finalstates;
    lhef::Particles leptons;
    lhef::ParticleID is_lepton = {11, -11, 13, -13};
    lhef::Particle lep_anc;
    lhef::ParticleLines toplines;
    lhef::ParticleID is_top = {6, -6};
    lhef::Particles daughters_of_top;
    int num_eve = 0;
    for ( ; !lhe.empty(); lhe = lhef::ParseEvent(&filename)) {
        ++num_eve;
        std::cout << "-- Event number: " << num_eve << '\n'
                  << lhe.show() << '\n';
        initstates = lhef::InitialStates(lhe);
        std::cout << "---- Initial-state particles:\n"
                  << lhef::show(initstates) << '\n';
        finalstates = lhef::FinalStates(lhe);
        std::cout << "---- Final-state particles:\n"
                  << lhef::show(finalstates) << '\n';
        leptons = lhef::ParticlesOf(is_lepton, lhe);
        std::cout << "---- Leptons:\n" << lhef::show(leptons) << '\n';
        lep_anc = lhef::Ancestor(leptons.front(), lhe);
        std::cout << "---- Ancestor of one lepton:\n" << lep_anc.show() << '\n';
        toplines = lhef::ParticleLinesOf(is_top, lhe);
        std::cout << "---- Lines of top quarks:\n";
        std::copy(toplines.cbegin(), toplines.cend(),
                  std::ostream_iterator<int>(std::cout, " "));
        std::cout << '\n';
        daughters_of_top = lhef::FinalDaughters(toplines.front(), lhe);
        std::cout << "---- Daughters of one top quark:\n"
                  << lhef::show(daughters_of_top) << '\n';
    }

    std::cout << "-- " << num_eve << " events parsed.\n";
    filename.close();
}
