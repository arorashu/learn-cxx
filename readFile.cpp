//
// Created by shubham on 6/23/20.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    cout << "Hello, World!" << std::endl;

    ifstream clientFile("client0.txt");
//    stringstream buffer;
    string temp;
//    buffer << clientFile.rdbuf();

    vector<string> elements;
    stringstream splitStream;
    while (getline(clientFile, temp, '\n')) {
        elements.push_back(temp);
    }


    cout << "Client File: \n";
//    for(const auto &it: elements) {
//        cout<< it <<", ";
//    }
    cout<< elements[0];
    cout<<endl << "File size: " << elements.size();

    ofstream outFile("outFile.txt");
    for(const auto &it: elements) {
        outFile << it;
        outFile << endl;
    }



    return 0;
}

