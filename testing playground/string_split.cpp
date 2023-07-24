#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(void) {
    string s = "420 069";
    istringstream iss(s);
    for (int number; iss >> number; ) {
        cout << number << endl;
    }
}