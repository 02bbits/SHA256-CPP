#ifndef SHA256_H
#define SHA256_H

#include <string>
#include <vector>
#include <bitset>

std::vector<std::bitset<8>> stringToBinary(const std::string str);
std::vector<std::bitset<8>> pad(std::vector<std::bitset<8>> message, int n = 1);

std::bitset<32> rotr(std::bitset<32> (x), int n);
std::bitset<32> sig0(std::bitset<32> (x));
std::bitset<32> sig1(std::bitset<32> (x));

std::bitset<32> merge(std::bitset<8>(x1), std::bitset<8>(x2), std::bitset<8>(x3), std::bitset<8>(x4));
std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2, std::bitset<32> x3, std::bitset<32> x4);
std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2);
std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2, std::bitset<32> x3, std::bitset<32> x4, std::bitset<32> x5);

std::vector<std::bitset<32>> getEntrys(std::vector<std::bitset<8>> messageBlocks);
std::vector<std::bitset<8>> getBigEndian(const short ogMessageLength);
std::vector<std::vector<std::bitset<32>>> splitChunks(std::vector<std::bitset<32>> messageBlock);

#endif
