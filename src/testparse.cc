/*
 * Copyright (c) 2014 Chan Beom Park
 */

#include "lhefevent.h"
#include <fstream>
#include <iostream>
#include <string>

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
        std::cerr << "-- cannot open input file \"" << argv[1] << "\".\n";
        return 1;
    }

    std::string evstr;
    while (true) {
        evstr = lhef::EventStr(&filename);
        if (evstr.empty()) {
            break;
        } else {
            std::cout << evstr << '\n';
        }
    }

    filename.close();
}
