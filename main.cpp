#include <iostream>
#include <set>

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::multiset<std::string> ms;
    std::set<std::string> ss;

    ms.insert("abc");
    ms.insert("def");
    ms.insert("abc");
    ms.insert("cat");

    ss.insert("abc");
    ss.insert("def");
    ss.insert("cat");
    ss.insert("abc");

    std :: cout<< "*Multiset*\n";
    for (const auto& elem: ms) {
        std::cout << elem << "\n";
    }
    std::cout << std::endl;


    std :: cout<< "*Set*\n";
    for (const auto& elem: ss) {
        std::cout << elem << "\n";
    }
    std::cout << std::endl;

    return 0;
}
