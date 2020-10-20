//
// Created by shubham on 10/20/20.
//

#include <iostream>
#include <exception>
#include <sstream>

using namespace std;

class myVector {
private:
    int *arr;
    int size;
    int top;

public:
    myVector(): size(10), top(0) {
        arr = new int[size];
    }

    /**
     *
     * @param sz capacity to reserve for array
     */
    myVector(int sz): size(sz), top(0) {
        arr = new int[size];
    }

    ~myVector() {
        delete arr;
    }

    /**
     *
     * @return new size of array
     */
    int push_back(int val) {
        if(top+1==size) {
            size *= 2;
            int *b = new int[size];
            for (int i = 0; i < top; ++i) {
                b[i] = arr[i];
            }
            delete arr;
            arr = b;
        }
        arr[top] = val;
        top++;
        return top;
    }


    /**
     *
     * @return new size of array
     */
    int pop_back() {
        if (top-1 < size/4) {
            size = (size/2 > 10) ? (size/2) : 10;
            int *b = new int[size];
            for (int i = 0; i < top; ++i) {
                b[i] = arr[i];
            }
            delete arr;
            arr = b;
        }
        top--;
        return top;
    }

    int getSize() const {
        return top;
    }

    int getCapacity() const {
        return size;
    }

    int operator[] (int index) const{
        if (index >= top || index < 0) {
            stringstream err;
            err << "Index: " << index << "is not accesible for myVector of size: " << top << endl;
            throw runtime_error(err.str());
        }
        return arr[index];
    }

};

ostream& operator<<(ostream &os, const myVector& mv) {
    for (int i=0; i<mv.getSize(); i++) {
        os << mv[i] << ' ';
    }
    os << endl;
}


int main() {
    myVector arr;
    arr.push_back(20);
    arr.push_back(15);
    arr.push_back(30);
    arr.pop_back();
    arr.push_back(199);
    cout << "arr size: " << arr.getSize() << ", arr capacity: " << arr.getCapacity() << endl;
    cout << arr << endl;

    for (int i = 0; i < 100; ++i) {
        arr.push_back(i);
    }
    cout << "arr size: " << arr.getSize() << ", arr capacity: " << arr.getCapacity() << endl;
    cout << arr << endl;

    for (int i = 0; i < 80; ++i) {
        arr.pop_back();
    }
    cout << "arr size: " << arr.getSize() << ", arr capacity: " << arr.getCapacity() << endl;
    cout << arr << endl;

}