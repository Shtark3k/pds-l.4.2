#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

/**
 * @brief Function to print a combination (vector of integers).
 * @param combination The vector to print.
 */
void print_combination(const std::vector<int>& combination) {
    for (size_t i = 0; i < combination.size(); ++i) {
        std::cout << combination[i];
    }
    std::cout << std::endl;
}

/**
 * @brief Calculates the number of combinations C(n, r) = n! / (r! * (n-r)!).
 * @param n Total number of items.
 * @param r Number of items to choose.
 * @return The number of combinations.
 */
long long combinations(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r;

    long long res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

// Function to generate the next lexicographical combination based on the algorithm steps 4.1-4.2
bool next_combination(std::vector<int>& combination, int n, int r) {
    // 4.1) Find the rightmost element a_i such that a_i != n - r + i
    int i = r - 1;
    while (i >= 0 && combination[i] == n - r + i + 1) {
        i--;
    }

    // If i < 0, all combinations have been generated (current is the last one)
    if (i < 0) {
        return false;
    }

    // 4.2) For the found element, perform the assignment a_i := a_i + 1
    combination[i]++;

    // 4.3) (Implicitly from the algorithm's spirit, but required for correctness)
    // Set all elements to the right of a_i to the smallest possible increasing values.
    // The next element a_{i+1} must be a_i + 1, a_{i+2} must be a_i + 2, and so on.
    for (int j = i + 1; j < r; ++j) {
        combination[j] = combination[j - 1] + 1;
    }

    return true;
}

int main() {
    // 1) Start

    int n, r;

    // 2) Input the natural number n and non-negative integer r (r <= n)
    std::cout << "Enter the total number of elements (n): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: n must be a positive integer." << std::endl;
        return 1;
    }

    std::cout << "Enter the size of the combination (r): ";
    if (!(std::cin >> r) || r < 0 || r > n) {
        std::cerr << "Error: r must be a non-negative integer and r <= n." << std::endl;
        return 1;
    }

    // --- Pre-computation and Initialization ---
    long long total_combinations = combinations(n, r);
    std::cout << "\n--- Generating C(" << n << ", " << r << ") = "
        << total_combinations << " Combinations ---\n" << std::endl;

    // Initial combination (1, 2, ..., r)
    std::vector<int> current_combination(r);
    // std::iota fills the combination vector with 1, 2, ..., r
    std::iota(current_combination.begin(), current_combination.end(), 1);

    // 3) Output the lexicographically smallest combination 123...r
    std::cout << "1. Initial Combination (Smallest):" << std::endl;
    print_combination(current_combination);

    long long count = 1;

    // 4) Loop from k = 2 to C(n, r): apply the algorithm for the next combination
    // The loop continues as long as 'next_combination' returns true
    while (next_combination(current_combination, n, r)) {
        count++;
        // 4.3) Output the obtained combination to the screen
        print_combination(current_combination);
    }

    // 5) End: Summary
    std::cout << "\n--------------------------------------------------" << std::endl;
    std::cout << "Finished. Generated " << count << " combinations." << std::endl;

    return 0;
}