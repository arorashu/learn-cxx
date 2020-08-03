#include <iostream>
#include <set>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    multiset<string> ms1, ms2;

    ms1.insert("a");
    ms1.insert("b");
    ms1.insert("c");
    ms1.insert("d");
    ms1.insert("e");
    ms1.insert("x");
    ms1.insert("y");

    ms2.insert("a");
    ms2.insert("b");
    ms2.insert("c");
    ms2.insert("e");
    ms2.insert("d");
    ms2.insert("x");
    ms2.insert("y");


    cout<< "Compare ms1 & ms2\n";
    if (ms1 == ms2) {
        cout << "multisets are equal\n";
    } else {
        cout << "multisets are not equal\n";
    }

    return 0;
}
