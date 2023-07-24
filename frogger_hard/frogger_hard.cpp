#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <algorithm>
#include <execution>

#include <cstdint>
#include <cstdlib>
#include <ctime>

#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
//#pragma GCC optimize ("unroll-loops")

constexpr const int N_BITSET = 4e5;
constexpr const int N_MAX = 4e5;
constexpr int unroll_factor = 4;

using namespace std;

class CustomBitset {
public:
    static const int BITS_PER_BLOCK = 64;
    static const int BLOCK_COUNT = (N_BITSET + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;

    CustomBitset() {
        reset();
    }

    void reset() {
        fill(blocks, blocks + BLOCK_COUNT, 0);
    }

    void set(int pos) {
        blocks[pos / BITS_PER_BLOCK] |= (uint64_t(1) << (pos % BITS_PER_BLOCK));
    }

    bool test(int pos) const {
        return (blocks[pos / BITS_PER_BLOCK] & (uint64_t(1) << (pos % BITS_PER_BLOCK))) != 0;
    }

private:
    uint64_t blocks[BLOCK_COUNT];
};

int winning_instances(int board[], const int n) {
    int no_wins = 0; // number of winning instances
    int num_full_blocks = n - (n % 4);
    int board_val;
    bool cycle;
    bool outside;
    unordered_set<int> magic_numbers(board, board + N_MAX); // unique magic numbers
    short pre_wins[N_MAX]; // tiles where the no. wins from that tile is noted
    CustomBitset visited_tiles; 
    CustomBitset used_magic_numbers;
    int idxs[N_MAX]; // keeps track of the next move
    for (int i = 0; i < n; i++) {
        idxs[i] = board[i] + i;
        pre_wins[i] = 0;
    }
    //fill(pre_wins.begin(), pre_wins.end(), 0);
    //copy(board.begin(), board.end(), inserter(magic_numbers, magic_numbers.end()));
    for (int i = 0; i < n; i++) {
        visited_tiles.reset();
        used_magic_numbers.reset();
        cycle = false;
        outside = false;
        int idx = i;
        while (!cycle && !outside) {
            if (pre_wins[idx] != 0) {
                no_wins += pre_wins[idx];
                break;
            }
            visited_tiles.set(idx);
            board_val = board[idx];
            idx = idxs[idx];
            auto magic_num_it = magic_numbers.find(board_val);
            if (magic_num_it != magic_numbers.end() && !used_magic_numbers.test(board_val + n)) {
                no_wins += 1;
                used_magic_numbers.set(board_val + n);

                for (int j = 0; j < num_full_blocks; j += unroll_factor) {
                    pre_wins[j] += visited_tiles.test(j);
                    pre_wins[j + 1] += visited_tiles.test(j + 1);
                    pre_wins[j + 2] += visited_tiles.test(j + 2);
                    pre_wins[j + 3] += visited_tiles.test(j + 3);
                }

                for (int j = num_full_blocks; j < n; j++) {
                    pre_wins[j] += visited_tiles.test(j);
                }
            }
            if (idx < 0 || idx >= n) {
                outside = true;
            }
            else if (visited_tiles.test(idx)) {
                cycle = true;
                for (int j = 0; j < num_full_blocks; j += unroll_factor) {
                    pre_wins[j] += visited_tiles.test(j);
                    pre_wins[j + 1] += visited_tiles.test(j + 1);
                    pre_wins[j + 2] += visited_tiles.test(j + 2);
                    pre_wins[j + 3] += visited_tiles.test(j + 3);
                }
                
                for (int j = num_full_blocks; j < n; j++) {
                    pre_wins[j] += visited_tiles.test(j);
                }           
            }
        };
    } 
    return no_wins;
}

int main() {
    /*int n;
    cin >> n;

    vector<int> board(n); 
    string input_line;
    getline(cin >> ws, input_line);
    stringstream ss(input_line);
    for (int i = 0; ss >> board[i]; i++);*/
    
    // Set a seed for the random number generator
    srand(static_cast<unsigned>(time(0)));

    int n; // Size of the board
    cout << "Enter the size of the board (n): ";
    cin >> n;

    //vector<int> board(n);
    int board[N_MAX];
    // Generate a random board with values between 0 and n-1
    for (int i = 0; i < n; i++) {
        int val;
        do {
            val = rand() % (2 * n) - n;
        } while (val == 0);
        board[i] = val;
    }

    // Call the winning_instances function and measure the time taken
    clock_t startTime = clock();
    int no_wins = winning_instances(board, n);
    clock_t endTime = clock();

    // Print the number of winning instances and the time taken
    cout << "Number of winning instances: " << no_wins << endl;
    double timeTaken = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "Time taken: " << timeTaken << " seconds" << endl;
    /*
    int no_wins;
    no_wins = winning_instances(board, n);
    cout << no_wins;*/
    return 0;
}