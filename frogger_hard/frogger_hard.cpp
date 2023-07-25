#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_set>
#include <algorithm>
#include <immintrin.h>

#include <cstdint>
#include <cstdlib>
#include <ctime>

#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("avx")

constexpr const int N_BITSET = 4e5;
constexpr const int N_MAX = 2e5;
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

void updatePreWinsWithVisitedTiles(int pre_wins[], const int visited_tiles[], int num_full_blocks) {
    // The unroll factor should be a multiple of 4 for better vectorization
    int j = 0;

    // Process full blocks of 4 elements each
    for (; j < num_full_blocks; j += unroll_factor) {
        // Load 4 elements of visited_tiles into SIMD registers
        __m128i visited_vec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&visited_tiles[j*unroll_factor]));

        // Load 4 elements of pre_wins into SIMD registers
        __m128i pre_wins_vec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&pre_wins[j*unroll_factor]));

        // Perform the addition between visited_vec and pre_wins_vec
        pre_wins_vec = _mm_add_epi32(pre_wins_vec, visited_vec);

        // Store the result back to pre_wins array
        _mm_storeu_si128(reinterpret_cast<__m128i*>(&pre_wins[j*unroll_factor]), pre_wins_vec);
    }

    // Process the remaining elements (less than 4) if any
    for (; j < N_MAX; j++) {
        pre_wins[j] += visited_tiles[j];
    }
}

int winning_instances(int board[], const int n) {
    int no_wins = 0; // number of winning instances
    int num_full_blocks = n / unroll_factor;
    int board_val;
    bool cycle;
    bool outside;
    unordered_set<int> magic_numbers(board, board + N_MAX); // unique magic numbers
    int pre_wins[N_MAX]; // tiles where the no. wins from that tile is noted
    int visited_tiles[N_MAX]; 
    CustomBitset used_magic_numbers;
    int idxs[N_MAX]; // keeps track of the next move
    for (int i = 0; i < n; i++) {
        idxs[i] = board[i] + i;
        pre_wins[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        used_magic_numbers.reset();
        cycle = false;
        outside = false;
        int idx = i;  
        for (int i = 0; i < n; i++) {
            visited_tiles[i] = 0;
        }
        while (!cycle && !outside) {
            board_val = board[idx];
            visited_tiles[idx] = 1;
            if (pre_wins[idx] != 0) {
                break;
            }
            else if (!used_magic_numbers.test(board_val + n)) {
                auto magic_num_it = magic_numbers.find(board_val);
                if (magic_num_it != magic_numbers.end()) {
                    updatePreWinsWithVisitedTiles(pre_wins, visited_tiles, num_full_blocks);
                    used_magic_numbers.set(board_val + n);
                }
            }
            idx = idxs[idx];
            if (idx < 0 || idx >= n) {
                outside = true;
            }
            else if (visited_tiles[idx] == 1) {
                cycle = true;
                updatePreWinsWithVisitedTiles(pre_wins, visited_tiles, num_full_blocks);
            }
        };
    } 
    for (int i = 0; i < n; i++) {
        no_wins += pre_wins[i];
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
        //cout << val << " ";
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