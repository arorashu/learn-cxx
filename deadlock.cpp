/*
    program to simulate a deadlock
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <wait.h>

using namespace std;

const string filename = "ma-file";


// read to file
void f1() {
    FILE* fr = fopen(filename.c_str(), "r");
    fclose(fr);
    string command = "chmod -w " + filename;
    system(command.c_str());
    cout << "f1 file open for read\n";
    sleep(3);
    command = "chmod +w " + filename;
    system(command.c_str());
    cout << "f1 says now you may write\n";
}



// write to file
void f2() {
    sleep(1);
    //fstream fo(filename);
    FILE* fo = fopen(filename.c_str(), "w");
    while(!fo) {
        fo = fopen(filename.c_str(), "w");
        cout << "f2 waiting to get fp\n";
    }
    cout << "f2 file open for write\n";
    fclose(fo);
}


int main() {

    cout << getpid() << " master\n";
    
    int pid = fork();
    if(pid==0) { //
        f1();

    } else { // parent
        int chld_state;
        f2();
        waitpid(pid, &chld_state, 0);
    }

    
    
    cout << getpid() << " deadlock\n";
}
