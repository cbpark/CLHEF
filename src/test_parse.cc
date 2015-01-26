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
    lhef::ParticleID is_lepton = lhef::Electron;
    is_lepton.insert(is_lepton.end(), lhef::Muon.begin(), lhef::Muon.end());
    lhef::Particles leptons;
    lhef::Particle lep_anc;
    lhef::ParticleLines toplines;
    lhef::Particles daughters_of_top;
    int num_eve = 0;
    for ( ; !lhe.empty(); lhe = lhef::ParseEvent(&filename)) {
        ++num_eve;
        std::cout << "-- Event number: " << num_eve << '\n'
                  << lhef::show(lhe) << '\n';
        initstates = lhef::InitialStates(lhe);
        std::cout << "---- Initial-state particles:\n"
                  << lhef::show(initstates) << '\n';
        finalstates = lhef::FinalStates(lhe);
        std::cout << "---- Final-state particles:\n"
                  << lhef::show(finalstates) << '\n';
        leptons = lhef::ParticlesOf(is_lepton, lhe);
        std::cout << "---- Leptons:\n" << lhef::show(leptons) << '\n';
        lep_anc = lhef::Ancestor(leptons.front(), lhe);
        std::cout << "---- Ancestor of one lepton:\n"
                  << lhef::show(lep_anc) << '\n';
        toplines = lhef::ParticleLinesOf(lhef::Top, lhe);
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
