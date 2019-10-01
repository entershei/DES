#include <iostream>
#include <vector>
#include <fstream>

#include "tables.h"

std::vector<std::vector<size_t>> S1(4, std::vector<size_t>(16));
std::vector<std::vector<size_t>> S2(4, std::vector<size_t>(16));
std::vector<std::vector<size_t>> S3(4, std::vector<size_t>(16));
std::vector<std::vector<size_t>> S4(4, std::vector<size_t>(16));
std::vector<std::vector<size_t>> S5(4, std::vector<size_t>(16));
std::vector<std::vector<size_t>> S6(4, std::vector<size_t>(16));
std::vector<std::vector<size_t>> S7(4, std::vector<size_t>(16));
std::vector<std::vector<size_t>> S8(4, std::vector<size_t>(16));

void initialize_table(std::ifstream& in, std::vector<std::vector<size_t>>& table) {
    for (auto & i : table) {
        for (size_t & j : i) {
            in >> j;
        }
    }
}

void initialize_all_s_tables() {
    std::ifstream in("tables");
    if (in.is_open()) {
        initialize_table(in, S1);
        initialize_table(in, S2);
        initialize_table(in, S3);
        initialize_table(in, S4);
        initialize_table(in, S5);
        initialize_table(in, S6);
        initialize_table(in, S7);
        initialize_table(in, S8);
    }
    in.close();
}

int main() {
    initialize_all_s_tables();
    return 0;
}