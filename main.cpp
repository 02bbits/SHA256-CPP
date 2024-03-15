#include <iostream>
#include <string>
#include "SHA256.cpp"
#include <bitset>

using namespace std;


int main() {
    string str = "hello, world!";
    cout << stringToBinary(str) << endl;
    cout << pad(stringToBinary(str));
}
