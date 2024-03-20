#include <iostream>
#include <string>
#include "SHA256.cpp"
#include <bitset>
#include <vector>

using namespace std;

int main() {
    string str;
    cout << "Enter a string: ";
    cin >> str;

    // Get size of string for getting big endian
    short strSize = str.size() * 8; 

    // Finish getting (512 * n) bits message block
    vector<bitset<8>> paddedMessage = pad(stringToBinary(str));
    vector<bitset<8>> bigEndian = getBigEndian(strSize);

    for (bitset<8> i : bigEndian) {
        paddedMessage.push_back(i); 
    }

    // Split message block into chunks and create a 64 bits entries of 32 bits
    std::vector<std::bitset<32>> entries = getEntries(paddedMessage);

    std::vector<vector<std::bitset<32>>> chunks = splitChunks(entries);

    for (int i = 0; i < chunks.size(); i++) {
        schedule(chunks[i]);
    }

    // Loop through each chunk and getting the final hash values
    std::vector<std::bitset<32>> hashValues = digest(chunks);

    cout << "Here is your hashed string: ";
    for (bitset<32> i : hashValues) {
        cout << hex << i.to_ulong();
    }
}
