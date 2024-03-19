#include <iostream>
#include <string>
#include "SHA256.cpp"
#include <bitset>
#include <vector>

using namespace std;

int main() {
    string str = "hello world";
    std::vector<std::bitset<8>> messageBlocks = pad(stringToBinary(str));
    std::vector<std::bitset<8>> bigEndian = getBigEndian(str.size() * 8);
    messageBlocks.insert(messageBlocks.end(), bigEndian.begin(), bigEndian.end());
    std::vector<std::bitset<32>> entries = getEntrys(messageBlocks);
    std::vector<std::vector<std::bitset<32>>> messageChunks = splitChunks(entries);

    for (vector<bitset<32>> i : messageChunks) {
        for (bitset<32> j : i) {
            cout << j << " ";
        }
    }

}
