#include <iostream>
#include <string>
#include "SHA256.cpp"
#include <bitset>
#include <vector>

using namespace std;
void transform(std::vector<std::bitset<32>> &chunk) {
    for (int k = 16; k < 64; k++) {
        std::bitset<32> w = add(chunk[k - 16], sig0(chunk[k - 15]), chunk[k - 7], sig1(chunk[k - 2]));
        chunk.push_back(w);
    }
}



int main() {
    string str = "hello world";
    std::vector<std::bitset<8>> messageBlocks = pad(stringToBinary(str));
    std::vector<std::bitset<8>> bigEndian = getBigEndian(str.size() * 8);
    messageBlocks.insert(messageBlocks.end(), bigEndian.begin(), bigEndian.end());
    std::vector<std::bitset<32>> entries = getEntrys(messageBlocks);
    std::vector<std::vector<std::bitset<32>>> chunks = splitChunks(entries);

    transform(chunks[0]);

}
