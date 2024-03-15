#include <iostream>
#include <string>
#include "SHA256.cpp"
#include <bitset>

using namespace std;

string pad(string message, int n = 1) {
    int end = message.length() < 448 ? 448 : 512;

    if (n == 1) {
        message += "1";
    }

    for (int start = message.length(); start < end; start++) {
        message += "0";
    }

    if (message.length() > 448) {
        message += pad(message.substr(end), n + 1);
    }
    
    return message;
}

int main() {
    string str = "ddddddddddddddddddddddddddddddddddddddddddddddddddddddd";
    cout << pad(stringToBinary(str));
}
