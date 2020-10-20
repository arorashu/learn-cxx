// test out serialization and deserialization using C++ streams (probably)
//
// # Mind dump
// 1. encode base64 encoded data?
// 2. text encoding vs binary encoding?
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Contact {
public:
    string name;
    long phone;
    vector<unsigned char> key;

    // serialize in textual format using stringStream
    // cannot actually deserialize this
    string serializeText() {
        stringstream out;
        out << name
            << phone;
        for (const auto &x: key) out << x;
        return out.str();
    }

    void deserialize(string ser) {

    }

    // serialize in textual format using string
    string serializeText2() {
        string out;
        out += name
               + to_string(phone);
        for (const auto &x: key) out += x;
        return out;
    }

    // serialize in textual format using string
    vector<pair<int, string>> serializeText3() {
        vector<pair<int, string>> out;
        out.push_back(make_pair(name.size()*sizeof(name), name));
        out.push_back(make_pair(sizeof(phone), to_string(phone)));
        size_t keySize = key.size();
        out.push_back(make_pair(sizeof(keySize), to_string(keySize)));
        for (const auto &x: key) {
            // string(1,x) : fill constructor
            //    Fills the string with n consecutive copies of character c.
            // http://www.cplusplus.com/reference/string/string/string/
            out.push_back( make_pair(sizeof(x), string(1, x)) );
        }
        return out;
    }

    // serialize in textual format using vector of string
    vector<string> serializeText4() {
        vector<string> out;
        out.push_back(name);
        out.push_back(to_string(phone));
        size_t keySize = key.size();
        out.push_back(to_string(keySize));
        for (const auto &x: key) {
            // string(1,x) : fill constructor
            //    Fills the string with n consecutive copies of character c.
            // http://www.cplusplus.com/reference/string/string/string/
            out.push_back( string(1, x));
        }
        return out;
    }

    /**
     *
     * @param buf - the buffer from which to read data
     * @param numBytes - the total size of data in bytes
     */
    void deserialize3(void *buf, size_t numBytes) {

        pair<int, string>* inp = static_cast< pair<int, string>* >(buf);

        size_t bufferPtrSize = sizeof(int) + sizeof(string);

        vector<pair<int, string>> in(inp, inp +(numBytes / bufferPtrSize) );


        if(in.size() < 3) cout << "ERROR: cannot deserialize\n";

        this->name = in.at(0).second;
        this->phone = stol(in.at(1).second);
        size_t keySize = stol(in.at(2).second);
        cout << "no of keys: " << keySize << endl;
        cout << "got metadata\n";
        for (int i=3; i<3+keySize; i++) {
            this->key.push_back( static_cast<unsigned char>(in.at(i).second[0]) );
        }
    }

    /**
     *
     * @param buf - the buffer from which to read data
     * @param numBytes - the total size of data in bytes
     */
    void deserialize4(void *buf, size_t numBytes) {

        string* inp = static_cast<string*>(buf);

        size_t bufferPtrSize = sizeof(string);

        vector<string> in(inp, inp +(numBytes / bufferPtrSize) );

        if(in.size() < 3) cout << "ERROR: cannot deserialize\n";

        this->name = in.at(0);
        this->phone = stol(in.at(1));
        size_t keySize = stol(in.at(2));
        cout << "no of keys: " << keySize << endl;
        cout << "got metadata\n";
        for (int i=3; i<3+keySize; i++) {
            this->key.push_back( static_cast<unsigned char>(in.at(i)[0]) );
        }
    }


    friend ostream &operator<<(ostream &out, const Contact &self) {
        out << "{ Name: " << self.name
            << ", phone: " << self.phone
            << ", key: ";
        for (const auto &x: self.key) out << x;
        out << " }\n";

        return out;
    }

    bool operator==(const Contact &other) {
        if (other.name == name && other.phone == this->phone && isKeyEqual(other.key)) {
            return true;
        }
        return false;
    }

    bool isKeyEqual (const vector<unsigned char>& otherKey) {
        if (otherKey.size() != key.size()) {
            return false;
        }
        for (int i=0; i<key.size(); i++) {
            if(otherKey[i] != key[i]) {
                return false;
            }
        }
        return true;
    }

};

/**
 * works for int, long,
 * any type for which sizeof() reports the actual size occupied in memory
 * and, bitshift >> is defined
 * @tparam T
 * @param obj
 * @return
 */
template<typename T>
vector< unsigned char> toBytes(T obj) {
    // put obj from left to right
    size_t objSize = sizeof(obj);
    vector<unsigned char> res(objSize);
    for (size_t i=0; i<objSize; i++ ) {
        res[objSize-1-i] = (obj >> (i*8));
    }
    return res;
}

template<typename T>
T fromBytes(vector<unsigned char> rep) {
    // put obj from left to right
    T res = 0;
    for (size_t i=0; i<rep.size(); i++ ) {
        res = (res<<8) | rep[i];
    }
    return res;
}



int main() {
    cout << "serialize\n";

//    Contact c;
//    c.name = "Ram";
//    c.phone = 9899045620;
//    c.key = {'k', 'i', 'c', 'k', 'a', 's', 's'};
//
//    int originalSize = sizeof(c.name) + sizeof(c.phone) + sizeof(unsigned char)*c.key.size();
//    cout << "original sizes: "
//    << "name: " << sizeof(c.name) << endl
//    << "phone: " << sizeof(c.phone) << endl
//    << "key: " << sizeof(unsigned char)*c.key.size() << endl
//    << "total: " << originalSize << " bytes\n"
//    ;
//
//    cout << "original : ";
//    cout << c;
//
//    // 3rd way
//    vector<pair<int, string>> msg3 = c.serializeText3();
//    long tSize = 0;
//    for (const auto &val: msg3) {
//        tSize += sizeof(val.first) + sizeof(val.second);
//    }
//    cout << "msg3 size: " << tSize << " bytes\n";
//
//    Contact d;
//    void * buf = static_cast<void*>(msg3.data());
//    d.deserialize3(buf, tSize);
//    cout << "deserialized: " << d << endl;
//
//    // 4th way
//    vector<string> msg4 = c.serializeText4();
//    long tSize4 = 0;
//    for (const auto &val: msg4) {
//        tSize4 += sizeof(val);
//    }
//    cout << "msg4 size: " << tSize4 << " bytes\n";
//
//    Contact c4;
//    void * buf4 = static_cast<void*>(msg4.data());
//    c4.deserialize4(buf4, tSize);
//    cout << "deserialized4: " << c4 << endl;
//
//    if (c==d && c==c4) {
//        cout << "All versions are equal to original\n";
//    } else {
//        cout << "All versions are not equal !!!\n";
//    }

    unsigned long a = 9875876;
    unsigned long b = 1023;
    cout << "sizes, a: " << sizeof(a) << ", b: " << sizeof(b) << endl;
    cout << "char size: " << sizeof(char) << endl;

    vector<unsigned char> carr = toBytes(a);
    cout << endl;
    cout << "original: " << a << endl;
    unsigned long x = fromBytes<unsigned long>(carr);
    cout << "fromBytes, x = " << x << endl;
}
