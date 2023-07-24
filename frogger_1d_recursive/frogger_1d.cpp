#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

pair<string, int> frog_hop(vector<int>& board, int idx, int n, int m, int h) {
    int move = board[idx];
    if (move == m) 
        return make_pair("magic", h);
    else if (move == 0)
        return make_pair("cycle", h);
    board[idx] = 0;
    idx += move;
    h += 1;
    if (idx < 0) 
        return make_pair("left", h);
    else if (idx > n - 1)
        return make_pair("right", h);
    return frog_hop(board, idx, n, m, h);
}

int main() {
    int n;
    int s;
    int m;
    int h = 0;
    cin >> n >> s >> m;
    s -= 1;
    vector<int> board(n); 
    string input_line;
    getline(cin >> ws, input_line);
    stringstream ss(input_line);
    for (int i = 0; ss >> board[i]; i++);
    pair<string, int> result{frog_hop(board, s, n, m, h)};
    cout << result.first << endl << result.second;
}