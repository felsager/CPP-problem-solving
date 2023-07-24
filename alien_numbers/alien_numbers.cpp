#include <iostream>
#include <string>
#include <map>

using namespace std;

int source_to_decimal(string& alien_number, string& source_language) {
    int result = 0;
    int N_base = source_language.size();
    int N_an = alien_number.size();
    for (int i = 0; i < N_an; i++) {
        result = N_base*result + source_language.find(alien_number[i]);
    }
    return result;
}

string decimal_to_target(int decimal, string& target_language) {
    string translation;
    int remainder;
    int N_base = target_language.size();
    while (decimal != 0) {
        remainder = decimal % N_base;
        decimal /= N_base;
        translation.insert(0, 1, target_language[remainder]);
    }
    return translation;
}

int main() {
    int N;
    cin >> N;
    string alien_number, source_language, target_language;
    for (int i=1; i<=N; i++) {
        cin >> alien_number >> source_language >> target_language;
        int decimal_repr = source_to_decimal(alien_number, source_language);
        string translation = decimal_to_target(decimal_repr, target_language);
        cout << "Case #" << i << ": " << translation << endl;
    }
}