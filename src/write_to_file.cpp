#include <iostream>
#include <string>
#include <fstream>
#include <tbb/concurrent_hash_map.h>


void write_to_file (const tbb::concurrent_hash_map<std::string, double> &map) {
    std::ofstream output_by_alph_file("../result.txt");

    if (!output_by_alph_file.is_open()) {
        std::cerr << "File opening error" << std::endl;
        return;
    }

    for (const auto &x: map) {
        output_by_alph_file << x.first << " - " << x.second << std::endl;
    }

    output_by_alph_file.close();
}

