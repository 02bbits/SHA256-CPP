#ifndef SHA256_H
#define SHA256_H

#include <string>
#include <vector>
#include <bitset>

std::vector<std::bitset<8>> stringToBinary(const std::string str);

std::vector<std::bitset<8>> pad(std::vector<std::bitset<8>> message, int n = 1);

#endif
