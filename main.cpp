#include <iostream>
#include <vector>
#include <fstream>

#include "tables.h"

void print_vector(std::vector<std::vector<size_t>>& table) {
    std::cout << "\n";
    for (auto & i : table) {
        std::cout << "{";
        for (size_t & j : i) {
            std::cout << j << ", ";
        }
        std::cout << "},\n";
    }
}

int main() {
    print_vector(S8);
    return 0;
}