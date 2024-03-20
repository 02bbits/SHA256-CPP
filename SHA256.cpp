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

std::vector<std::bitset<32>> getEntries(std::vector<std::bitset<8>> messageBlocks) {
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

void schedule(std::vector<std::bitset<32>> &chunk) {
    for (int k = 16; k < 64; k++) {
        std::bitset<32> w = add(chunk[k - 16], sig0(chunk[k - 15]), chunk[k - 7], sig1(chunk[k - 2]));
        chunk.push_back(w);
    }
}

std::bitset<32> majority(std::bitset<32> a, std::bitset<32> b, std::bitset<32> c) {
	return (a & (b | c)) | (b & c);
}

std::bitset<32> choose(std::bitset<32> e, std::bitset<32> f, std::bitset<32> g) {
	return (e & f) ^ (~e & g);
}

std::vector<std::bitset<32>> digest(std::vector<std::vector<std::bitset<32>>> chunks) {
    const std::bitset<32> k[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    std::vector<std::bitset<32>> hashValues = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
    };

    for (std::vector<std::bitset<32>> chunk : chunks) { // chunk hasnt scheduled
        std::bitset<32> workVariables[] = {
            hashValues[0],
            hashValues[1],
            hashValues[2],
            hashValues[3],
            hashValues[4],
            hashValues[5],
            hashValues[6],
            hashValues[7]
        };

        for (int i = 0; i < 64; i++) {
            std::bitset<32> sig1 = rotr(workVariables[4], 6) ^ rotr(workVariables[4], 11) ^ rotr(workVariables[4], 25);
            std::bitset<32> sig0 = rotr(workVariables[0], 2) ^ rotr(workVariables[0], 13) ^ rotr(workVariables[0], 22);

            std::bitset<32> temp1 = add(workVariables[7], sig1, choose(workVariables[4], workVariables[5], workVariables[6]), chunk[i], k[i]);
            std::bitset<32> temp2 = add(sig0, majority(workVariables[0], workVariables[1], workVariables[2]));

            workVariables[7] = workVariables[6];
            workVariables[6] = workVariables[5];
            workVariables[5] = workVariables[4];
            workVariables[4] = add(workVariables[3], temp1);
            workVariables[3] = workVariables[2];
            workVariables[2] = workVariables[1];
            workVariables[1] = workVariables[0];
            workVariables[0] = add(temp1, temp2);
        }

        hashValues[0] = add(workVariables[0], hashValues[0]);
        hashValues[1] = add(workVariables[1], hashValues[1]);
        hashValues[2] = add(workVariables[2], hashValues[2]);
        hashValues[3] = add(workVariables[3], hashValues[3]);
        hashValues[4] = add(workVariables[4], hashValues[4]);
        hashValues[5] = add(workVariables[5], hashValues[5]);
        hashValues[6] = add(workVariables[6], hashValues[6]);
        hashValues[7] = add(workVariables[7], hashValues[7]);
    }

    return hashValues;
}