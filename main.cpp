#include <iostream>
#include <string>
#include "SHA256.cpp"
#include <bitset>
#include <vector>

using namespace std;

std::bitset<8> rotr(char x, int n) {
	return (std::bitset<8>(x) >> n) | (std::bitset<8>(x) << (8 - n));
}

std::bitset<8> sig0(char x) {
	return rotr(x, 7) ^ rotr(x, 18) ^ (std::bitset<8>(x) >> 3);
}

std::bitset<8> sig1(char x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (std::bitset<8>(x) >> 10);
}

int main() {
    string str = "hello";
    vector<bitset<8>> vec = stringToBinary(str);
    vec = pad(vec);

    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
    }
}
