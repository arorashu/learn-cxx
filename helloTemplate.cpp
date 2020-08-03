//
// Created by shubham on 7/16/20.
//
#include<iostream>
#include<set>

using namespace std;

template<bool multiSet = false> class IBLT {
public:
    void add(int num)
    {
        multiSet ? addf1(num) : addf2(num);
    }
    void remove(int num)
    {
        multiSet ? removef1(num) : removef2(num);
    }
    void addf1(int num) { 
        cout<<"f1 insert multi called\n";
        numVals.insert(num); 
    }
    void addf2(int num) { 
        cout<<"f2 insert called\n";
        numVals.insert(num+5);
    }
    void removef1(int num)  { numVals.erase(num); }
    void removef2(int num)  { numVals.erase(num+5); }
public:
    set<int> numVals;
};

int main()
{
    IBLT<false> obj1;
    obj1.add(2);
    obj1.add(4);
    obj1.add(6);
    obj1.add(16);
    obj1.remove(6);

    // IBLT<true> obj2;
    // obj2.add(2);
    // obj2.add(4);
    // obj2.add(6);
    // obj2.add(16);
    // obj2.remove(6);


    cout << "obj1 set:\n";
    set<int>::iterator it;
    for(it = obj1.numVals.begin(); it != obj1.numVals.end() ; it++) {
        cout << *it << endl;
    }

    // cout << "obj2 set:\n";
   //  for(it = obj2.numVals.begin(); it != obj2.numVals.end() ; it++) {
    //     cout << *it << endl;
    // }
}
