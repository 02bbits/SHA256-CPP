#ifndef SHA256_H
#define SHA256_H

#include <string>
#include <vector>
#include <bitset>

// Phases
std::vector<std::bitset<8>> stringToBinary(const std::string str);
std::vector<std::bitset<8>> pad(std::vector<std::bitset<8>> message, int n = 1);
std::vector<std::bitset<8>> getBigEndian(const short ogMessageLength);
std::vector<std::bitset<32>> getEntries(std::vector<std::bitset<8>> messageBlocks);
void schedule(std::vector<std::bitset<32>> &chunk);
std::vector<std::vector<std::bitset<32>>> splitChunks(std::vector<std::bitset<32>> messageBlock);
std::vector<std::bitset<32>> digest(std::vector<std::vector<std::bitset<32>>> chunks);

// Operators
std::bitset<32> rotr(std::bitset<32> (x), int n);
std::bitset<32> sig0(std::bitset<32> (x));
std::bitset<32> sig1(std::bitset<32> (x));
std::bitset<32> majority(std::bitset<32> a, std::bitset<32> b, std::bitset<32> c);
std::bitset<32> choose(std::bitset<32> e, std::bitset<32> f, std::bitset<32> g);

std::bitset<32> merge(std::bitset<8>(x1), std::bitset<8>(x2), std::bitset<8>(x3), std::bitset<8>(x4));
std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2, std::bitset<32> x3, std::bitset<32> x4);
std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2);
std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2, std::bitset<32> x3, std::bitset<32> x4, std::bitset<32> x5);



#endif
