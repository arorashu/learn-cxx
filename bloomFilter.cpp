//
// Created by shubham on 6/26/20.
//
#include <iostream>
#include <vector>
#include "fnv.h"

using namespace std;

/**
 * Basic bloom filter that supports creation from a vector
 * and checks if an element exists
 *
 * Questions?
 * 1. How many hash functions? --- k
 * 2. How to choose size of store? --- m
 * What we know in input list size --- n
 *
 */
class BloomFilter {
private:
    vector<bool> store;

public:

    BloomFilter() = default;

    bool create(vector<int> inputList) {
//        store.resize(inputList.size()*2);
        store.assign(inputList.size() * 10, false);
        for (const auto &it: inputList) {
            uint32_t valHash = FNV::fnv1a((uint32_t) it);
            std::size_t pos = valHash % store.size();
            cout << "it: " << it << ", hash: " << valHash << ", pos: " << pos << endl;
            store[pos] = true;
        }
        cout << "Store size: " << store.size() << endl;
        return true;
    }

    bool exists(int input) {
        uint32_t valHash = FNV::fnv1a((uint32_t) input);
        std::size_t pos = valHash % store.size();
        cout << "input: " << input << ", hash: " << valHash << ", pos: " << pos << endl;
        return store[pos] == true;
    }

    size_t getsize() {
        return sizeof(BloomFilter) + (sizeof(bool ) * store.size());
    }

};

int main() {

    vector<int> list{1, 2, 3, 4, 5};
    cout << "Input list: ";
    for (const auto &it: list) {
        cout << it << " ";
    }
    cout << endl;
    BloomFilter f;
    f.create(list);
    cout << endl << "Does 6 exist: ? " << f.exists(6) << endl;


    cout << "Bloom Filter\n";
    cout << "bf size: " << f.getsize() << endl << "list size: " << sizeof(std::vector<int>) + (sizeof(int) * list.size())
         << endl << "bf class size: " << sizeof(BloomFilter) << endl;

    return 0;
}