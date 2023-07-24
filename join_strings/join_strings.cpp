#include <iostream>
#include <sstream>  
#include <string>
#include <vector>
#include <utility>

using namespace std;

void printRecursively(vector<vector<int>> &v, vector<string> &s, int idx) {
    cout << s[idx];
    for(int i : v[idx]) {
        printRecursively(v, s, i);
    }
}

int main() {
    int N;
    cin >> N;
    vector<string> strings(N);
    for (int n = 0; n < N; n++) {
        cin >> strings[n];
    }

    int idx_1 = 0, idx_2 = 0;
    vector<vector<int>> permutations;
    permutations.assign(N, vector<int>());
    for (int n = 0; n < N - 1; n++) {
        cin >> idx_1 >> idx_2;
        idx_1--; 
        idx_2--;
        permutations[idx_1].push_back(idx_2);
    }
    permutations[0].insert(permutations[0].begin(), idx_1);
    for (vector<int>& v : permutations) {
        for (int idx : v) {
            cout << strings[idx];
        }
    }
    cout << endl;
    //printRecursively(permutations, strings, idx_1);
    cout << endl;
}