#include "StringCalculator.hpp"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

// Add method implementation
int StringCalculator::add(const std::string &numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string delimiter = ",";
    std::string numString = numbers;

    // Check for custom delimiter
    if (numbers.rfind("//", 0) == 0) {
        size_t delimiter_end = numbers.find("\n");
        delimiter = numbers.substr(2, delimiter_end - 2);
        numString = numbers.substr(delimiter_end + 1);
    }

    // Replace newline with the delimiter
    std::replace(numString.begin(), numString.end(), '\n', delimiter[0]);

    // Split the string by the delimiter
    std::vector<int> nums = split(numString, delimiter);

    // Check for negative numbers
    checkForNegatives(nums);

    // Return the sum of the numbers
    return sumNumbers(nums);
}

// Helper function to split the string into numbers based on delimiter
std::vector<int> StringCalculator::split(const std::string &input, const std::string &delimiter) {
    std::vector<int> numbers;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != std::string::npos) {
        numbers.push_back(parseNumber(input.substr(start, end - start)));
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }

    // Add the last number
    numbers.push_back(parseNumber(input.substr(start)));
    return numbers;
}

// Helper function to parse a string to a number
int StringCalculator::parseNumber(const std::string &numStr) {
    int num = std::stoi(numStr);
    return (num > 1000) ? 0 : num;  // Ignore numbers greater than 1000
}

// Build the exception message for negative numbers
std::string buildNegativeExceptionMessage(const std::vector<int>& negatives) {
    std::stringstream ss;
    ss << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        if (i != 0) ss << ", ";
        ss << negatives[i];
    }
    return ss.str();
}

// Check for negative numbers and throw an exception if any are found
void StringCalculator::checkForNegatives(const std::vector<int> &numbers) {
    std::vector<int> negatives;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(negatives), [](int n) { return n < 0; });

    if (!negatives.empty()) {
        throw std::runtime_error(buildNegativeExceptionMessage(negatives));
    }
}

// Sum the list of numbers
int StringCalculator::sumNumbers(const std::vector<int> &numbers) {
    return std::accumulate(numbers.begin(), numbers.end(), 0);
}

// Main function to test the StringCalculator
int main() {
    StringCalculator calculator;

    // Test cases
    std::cout << "Sum of \"1,2\": " << calculator.add("1,2") << std::endl;
    std::cout << "Sum of \"1\n2,3\": " << calculator.add("1\n2,3") << std::endl;
    std::cout << "Sum of \"//;\n1;2\": " << calculator.add("//;\n1;2") << std::endl;

    try {
        // Test for negative numbers
        calculator.add("1,-2");
    } catch (const std::runtime_error &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}

