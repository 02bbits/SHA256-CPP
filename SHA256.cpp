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

std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2, std::bitset<32> x3, std::bitset<32> x4, std::bitset<32> x5) {
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

    while (x5!= 0) {
    carry = x1 & x5;
    x1 = x1 ^ x5;
    x5  = (carry << 1);
    }
    return x1;
}

std::bitset<32> add(std::bitset<32> x1, std::bitset<32> x2) {
    std::bitset<32> carry;
    
    while (x2 != 0) {
        carry = x1 & x2;
        x1 = x1 ^ x2;
        x2  = (carry << 1);
    }
    return x1;
}

std::vector<std::bitset<32>> getEntrys(std::vector<std::bitset<8>> messageBlocks) {
    std::vector<std::bitset<32>> entries;

    for (int i = 0; i < messageBlocks.size(); i += 4) {
        entries.push_back(merge(messageBlocks[i], messageBlocks[i + 1], messageBlocks[i + 2], messageBlocks[i + 3]));
    }

    return entries;
}   

std::vector<std::bitset<8>> getBigEndian(const short ogMessageLength) {
    std::bitset<64> length = ogMessageLength;
    std::vector<std::bitset<8>> bigEndian;

    for (int i = 56; i >= 0; i -= 8) {
        std::bitset<8> byte((length >> i).to_ulong());
        bigEndian.push_back(byte);
    }

    return bigEndian;
}

std::vector<std::vector<std::bitset<32>>> splitChunks(std::vector<std::bitset<32>> messageBlock) {
    std::vector<std::vector<std::bitset<32>>> messageChunks;

    for (size_t i = 0; i < messageBlock.size(); i += 16) {
        std::vector<std::bitset<32>> chunk(messageBlock.begin() + i, messageBlock.begin() + i + 16);
        messageChunks.push_back(chunk);
    }

    return messageChunks;
}