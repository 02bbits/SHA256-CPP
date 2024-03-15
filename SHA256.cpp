#include "SHA256.h"
#include <bitset>
#include <string>

std::string stringToBinary(const std::string str) {
    std::string result;

    for (char c : str) {
        result += std::bitset<8>(c).to_string();
    }

    return result;
}
