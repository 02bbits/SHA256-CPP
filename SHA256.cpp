#include "SHA256.h"
#include <bitset>
#include <string>
#include <vector>

std::vector<std::bitset<8>> stringToBinary(const std::string str) {
    std::vector<std::bitset<8>> result;

    for (char c : str) {
        result.push_back(std::bitset<8>(c));
    }

    return result;
}

std::vector<std::bitset<8>> pad(std::vector<std::bitset<8>> message, int n) {
    int end = message.size() < 56 ? 56 : 64;

    if (n == 1) {
        message.push_back(std::bitset<8>(10000000));
    }

    for (int start = message.size(); start < end; start++) {
        message.push_back(std::bitset<8>(0));
    }

    if (message.size() > 56) {
        std::vector<std::bitset<8>> messageTemp(message.begin() + end, message.end());
        auto message2 = pad(messageTemp, n + 1);
        message.insert(message.end(), message2.begin(), message2.end());
    }
    
    
    return message;
}