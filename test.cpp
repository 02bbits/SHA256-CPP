#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
    int b = 5;
    std::vector<int> list = {};
    list.push_back(b);
    for (int i : list) {
        cout << (std::bitset<8>(i) & std::bitset<8>(5))<< endl;
    }
}