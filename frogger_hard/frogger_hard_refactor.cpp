#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <immintrin.h>

// compiler flags
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("avx")

constexpr const int N_MAX = 2e5;
constexpr int unroll_factor = 4;

using namespace std;

class CustomBitset {
public:
    static const int N_BITSET = 4e5;
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

void updatePreWins(int pre_wins[], const int visited_tiles[], int num_full_blocks) {
    int j = 0;
    for (; j < num_full_blocks; j += unroll_factor) {
        __m128i visited_vec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&visited_tiles[j*unroll_factor]));
        __m128i pre_wins_vec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&pre_wins[j*unroll_factor]));
        pre_wins_vec = _mm_add_epi32(pre_wins_vec, visited_vec);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(&pre_wins[j*unroll_factor]), pre_wins_vec);
    }
    for (; j < N_MAX; j++) {
        pre_wins[j] += visited_tiles[j];
    }
}

int winning_instances(int board[], const int n) {
    int idx;
    int pre_idx;
    int board_val;
    CustomBitset magic_numbers;
    int pre_wins[N_MAX]; // tiles where the no. wins from that tile is noted
    int visited_tiles[N_MAX];
    int idxs[N_MAX];
    int num_full_blocks = n / unroll_factor;
    for (int i = 0; i < n; i++) {
        idxs[i] = board[i] + i;
        pre_wins[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        idx = i;
        if (pre_wins[idx] != 0) {
            continue;
        }
        magic_numbers.reset();
        fill(visited_tiles, visited_tiles + n, 0);
        for (int j = 0; j < n; j++) {
            visited_tiles[idx] = 1;
            board_val = board[idx];
            cout << "test = " << !magic_numbers.test(board_val + n) << "\n\n";
            if (!magic_numbers.test(board_val + n)) {
                magic_numbers.set(board_val + n);
                updatePreWins(pre_wins, visited_tiles, num_full_blocks);
            }
            pre_idx = idx;
            idx = idxs[idx];
            if (visited_tiles[idx]) {
                pre_wins[pre_idx] += 1;
                break;
            }
            else if (idx < 0 || idx >= n) {
                break;
            }
        }
    }
    int no_wins = accumulate(pre_wins, pre_wins + n, 0);
    return no_wins;
}

int main() {
    int board[N_MAX];
    /*int n;
    cin >> n;
    string input_line;
    getline(cin >> ws, input_line);
    stringstream ss(input_line);
    for (int i = 0; ss >> board[i]; i++);*/
    
    // Set a seed for the random number generator
    srand(static_cast<unsigned>(time(0)));

    int n; // Size of the board
    cout << "Enter the size of the board (n): ";
    cin >> n;

    
    // Generate a random board with values between 0 and n-1
    for (int i = 0; i < n; i++) {
        int val;
        do {
            val = rand() % (2 * n) - n;
        } while (val == 0);
        board[i] = val;
        cout << val << " ";
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