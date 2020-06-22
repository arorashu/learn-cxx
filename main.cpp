#include <iostream>
#include <set>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::multiset<std::string> ms;

    ms.insert("abc");
    ms.insert("def");
    ms.insert("abc");

    for (auto elem: ms) {
        std::cout << elem << "\n";
    }
    std::cout << std::endl;

    return 0;
}
