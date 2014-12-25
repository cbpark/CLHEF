#include <fstream>
#include <iostream>
#include "lhef.h"

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

    lhef::Event eve;
    int num_eve = 0;
    while (true) {
        eve = lhef::Parse(&filename);

        if (!eve.empty()) {
            ++num_eve;
            std::cout << eve << '\n';
        } else {
            break;
        }
    }

    std::cout << "-- " << num_eve << " events parsed.\n";

    filename.close();
}
