#include <iostream>

using namespace std;

int dangling_if(bool a, bool b) {
    if (a)
        if (b)
            return 1;
    else
        return 2;
    return 0;
} 

int main() {
    cout << "(0, 0): " << dangling_if(0, 0) << endl;
    cout << "(0, 1): " << dangling_if(0, 1) << endl;
    cout << "(1, 0): " << dangling_if(1, 0) << endl;
    cout << "(1, 1): " << dangling_if(1, 1) << endl;
}