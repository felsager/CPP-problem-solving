#include <iostream>
#include <sstream> // Required for stringstream

int main() {

    int N;
    std::cin >> N;
    std::cout << "N = " << N;

    std::string inputLine;
    std::getline(std::cin >> std::ws, inputLine); // Read the entire line

    // Create a stringstream from the input line
    std::stringstream ss(inputLine);

    int num;
    while (ss >> num) {
        // Here, 'num' will hold the individual integers
        // You can process or store them as required

        // For example, you can print them out
        std::cout << num << std::endl;
    }

    std::cout << std::endl; // Add a newline after printing the integers
    return 0;
}