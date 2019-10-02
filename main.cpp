#include <iostream>
#include <vector>
#include <cassert>

#include "tables.h"

using namespace std;

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

// index from 0
uint64_t get_index(uint64_t num, uint64_t i) {
    return (num & ((uint64_t)1 << (63 - i))) >> (63 - i);
}

uint64_t set_index(uint64_t num, uint64_t i, uint64_t new_bit) {
    uint64_t last_ind = get_index(num, i);
    if (last_ind == new_bit) {
        return num;
    } else if (last_ind == 1) {
        return num - ((uint64_t)1 << (63 - i));
    } else {
        return num | ((uint64_t)1 << (63 - i));
    }
}

void print_num(uint64_t num) {
    for (uint64_t i = 0; i < 64; ++i) {
        std::cout << get_index(num, i);
    }
    std::cout << "\n";
}

uint64_t current_c;
uint64_t current_d;

uint64_t expand(uint64_t key) {
    key = key << 8;

    uint64_t expanded = 0;

    size_t pos = 0;
    size_t cnt1 = 0;
    for (size_t i = 0; i < 56; ++i) {
        bool val = get_index(key, i);

        if (val) {
            ++cnt1;
        }

        if (pos % 8 == 0) {
            expanded = set_index(expanded, pos, cnt1 % 2 ? 0 : 1);
            cnt1 = 0;
            ++pos;
        }

        expanded = set_index(expanded, pos, val);
        ++pos;
    }

    return expanded;
}

uint64_t key_ip(vector<size_t> t, uint64_t key) {
    uint64_t ret = 0;

    for (int i = 0; i < 28; ++i) {
        ret = set_index(ret, i, get_index(key, t[i]));
    }

    return ret;
}

void conversion_key(uint64_t key) {
    uint64_t expanded_key = expand(key);

    current_c = key_ip(KEY_IP_C, expanded_key);
    current_d = key_ip(KEY_IP_D, expanded_key);

    cerr << "expanded key:\n";
    print_num(key);
}

// index from 1
uint64_t update_with_shift(uint64_t t, size_t index) {
    // t is "10001...000000"
    uint64_t old_t = t;
    t = t << COUNT_OF_SHIFTS_FOR_CD[index - 1];

    if (COUNT_OF_SHIFTS_FOR_CD[index - 1] == 1) {
        t = set_index(t, 27, get_index(old_t, 0));
    } else {
        t = set_index(t, 26, get_index(old_t, 0));
        t = set_index(t, 27, get_index(old_t, 1));
    }

    return t;
}

vector<uint64_t> keys(17);

// index from 1 to 16
void generate_key(size_t index) {
    current_c = update_with_shift(current_c, index);
    current_d = update_with_shift(current_d, index);

    cout << index << " c and d:\n";
    print_num(current_c);
    print_num(current_d);
    cout << endl;

    uint64_t key = 0;

    for (int i = 0; i < 48; ++i) {
        size_t pos = KEY_TRANSPOSITION[i];

        --pos;
        bool val;

        if (pos < 28) {
            val = get_index(current_c, pos);
        } else {
            val = get_index(current_d, pos - 28);
        }

        key = set_index(key, i, val);
    }

    keys[index] = key;
}

void get_all_keys() {
    for (int i = 1; i <= 16; ++i) {
        generate_key(i);
    }
}

int main() {
    std::cout << "Enter message - not negative integer less then 2^64\n" <<
                 "and key - not negative integer less then 2^56.";

    uint64_t message, key;
    //cin >> message;
    cin >> key;

    assert(key < ((uint64_t)1 << 56));

    conversion_key(key);

    cout << "c and d:\n";
    print_num(current_c);
    print_num(current_d);

    cout << "keys:\n";

    get_all_keys();
    print_num(keys[16]);



    return 0;
}