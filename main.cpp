#include <iostream>
#include <string>
#include "SHA256.cpp"
#include <bitset>
#include <vector>

using namespace std;

std::bitset<32> rotr(std::bitset<32> (x), int n) {
	return (x >> n) | (x << (32 - n));
}

std::bitset<32> sig0(std::bitset<32> (x)) {
	return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

std::bitset<32> sig1(std::bitset<32> (x)) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

std::bitset<32> merge(std::bitset<8>(x1), std::bitset<8>(x2), std::bitset<8>(x3), std::bitset<8>(x4)) {
    std::bitset<32> mergedBitset;
    mergedBitset |= (x1.to_ulong() << 24);
    mergedBitset |= (x2.to_ulong() << 16);
    mergedBitset |= (x3.to_ulong() << 8);
    mergedBitset |= x4.to_ulong();
    return mergedBitset;
}

std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2, std::bitset<32> x3, std::bitset<32> x4) {
    std::bitset<32> carry;
    while (x2 != 0) {
        carry = x1 & x2;
        x1 = x1 ^ x2;
        x2  = (carry << 1);
    }
    while (x3!= 0) {
        carry = x1 & x3;
        x1 = x1 ^ x3;
        x3  = (carry << 1);
    }
    while (x4!= 0) {
        carry = x1 & x4;
        x1 = x1 ^ x4;
        x4  = (carry << 1);
    }
    return x1;
}

std::vector<std::bitset<8>> getBigEndian(const short ogMessageLength) {
    std::bitset<64> length = ogMessageLength;
    std::vector<std::bitset<8>> bigEndian;
    bigEndian.push_back(bitset<8>((length >> 56).to_ulong()));
    bigEndian.push_back(bitset<8>((length >> 48).to_ulong()));
    bigEndian.push_back(bitset<8>((length >> 40).to_ulong()));
    bigEndian.push_back(bitset<8>((length >> 32).to_ulong()));
    bigEndian.push_back(bitset<8>((length >> 24).to_ulong()));
    bigEndian.push_back(bitset<8>((length >> 16).to_ulong()));
    bigEndian.push_back(bitset<8>((length >> 8).to_ulong()));
    bigEndian.push_back(bitset<8>((length).to_ulong()));

    return bigEndian;
}
int main() {
    string str = "hello me!";
    vector<bitset<8>> v = stringToBinary(str);

    std::vector<std::bitset<8>> bigEndian = getBigEndian(v.size() * 8);

    for (int i = 0; i < bigEndian.size(); i++) {
        cout << bigEndian[i] << endl;
    }

}
