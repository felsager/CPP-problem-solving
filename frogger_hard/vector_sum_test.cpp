#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<short> v_1(10);
    vector<short> v_2(10);
    fill(v_1.begin(), v_1.end(), 1);
    fill(v_2.begin(), v_2.end(), 10);
    transform(v_1.begin(), v_1.end(), v_2.begin(), v_1.begin(), plus<int>());
    transform(v_1.begin(), v_1.end(), v_2.begin(), v_1.begin(), plus<int>());
    transform(v_1.begin(), v_1.end(), v_2.begin(), v_1.begin(), plus<int>());
    for (int i : v_1) {
        cout << i << endl;
    }

}
