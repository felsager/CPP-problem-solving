#include <iostream>
#include <string>
#include <map>
#include <typeinfo>
#include <vector>
#include <math.h>

using namespace std;

int a_to_i(string s) {
    bool in_signs = false;
    bool in_numbers = false;
    bool negate = false;
    int result = 0;
    for (char c : s) {
        if (c >= '0' && c <= '9') {
            if (result > (INT_MAX - (c - '0')) / 10) 
                return (negate ? INT_MIN : INT_MAX);
            result = 10*result + (c - '0');
            in_numbers = true;
        }
        else if (in_numbers) 
            break;
        else if (in_signs)
            return 0;
        else if (c == ' ' ) 
            continue;
        else if (c == '+' || c == '-') {
            in_signs = true;
            negate = (c == '-');
        }
        else
            break;
    }
    result = (negate) ? -result : result;
    return result;
}


int main() {
    string s = "69 420 abc clear 69";
    int result = a_to_i(s);
    cout << result;

}