#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <algorithm>
#include <array>

#include <cstdint>
#include <cstdlib>
#include <ctime>

#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

constexpr const int MAX_N_BIT = 4e5;
constexpr const int MAX_N = 4e5;

using namespace std;

class CustomBitset {
public:
    static const int BITS_PER_BLOCK = 64; // or use std::bitset::bits_per_block if available
    static const int BLOCK_COUNT = (MAX_N_BIT + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK;

    CustomBitset() {
        reset();
    }

    void reset() {
        std::fill(blocks, blocks + BLOCK_COUNT, 0);
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

int winning_instances(const array<int, MAX_N> board, const int n) {
    int no_wins = 0; // number of winning instances
    int board_val;
    bool cycle;
    bool outside;
    array<int, MAX_N> idxs; // keeps track of the next move
    for (int i = 0; i < n; i++) {
        idxs[i] = board[i] + i;
    }
    unordered_set<int> magic_numbers; // unique magic numbers
    array<int, MAX_N> pre_wins; // tiles where the no. wins from that tile is noted
    CustomBitset visited_tiles; 
    CustomBitset used_magic_numbers;
    fill(pre_wins.begin(), pre_wins.end(), 0);
    copy(board.begin(), board.end(), inserter(magic_numbers, magic_numbers.end()));
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
                for (int j = 0; j < n; j++) {
                    pre_wins[j] += visited_tiles.test(j);
                }
            }
            if (idx < 0 || idx >= n) {
                outside = true;
            }
            else if (visited_tiles.test(idx)) {
                cycle = true;
                for (int j = 0; j < n; j++) {
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
    std::srand(static_cast<unsigned>(std::time(0)));

    int n; // Size of the board
    std::cout << "Enter the size of the board (n): ";
    std::cin >> n;

    array<int, MAX_N> board;

    // Generate a random board with values between 0 and n-1
    for (int i = 0; i < n; i++) {
        int val;
        do {
            val = std::rand() % (2 * n) - n;
        } while (val == 0);
        board[i] = val;
    }

    // Call the winning_instances function and measure the time taken
    clock_t startTime = clock();
    int no_wins = winning_instances(board, n);
    clock_t endTime = clock();

    // Print the number of winning instances and the time taken
    std::cout << "Number of winning instances: " << no_wins << std::endl;
    double timeTaken = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << timeTaken << " seconds" << std::endl;
    /*
    int no_wins;
    no_wins = winning_instances(board, n);
    cout << no_wins;*/
    return 0;
}