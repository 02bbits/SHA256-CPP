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

std::string pad(std::string message, int n) {
    int end = message.length() < 448 ? 448 : 512;

    if (n == 1) {
        message += "1";
    }

    for (int start = message.length(); start < end; start++) {
        message += "0";
    }

    if (message.length() > 448) {
        message += pad(message.substr(end), n + 1);
    }
    
    return message;
}
