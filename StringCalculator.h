#ifndef STRINGCALCULATOR_HPP
#define STRINGCALCULATOR_HPP

#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string &numbers);

private:
    std::vector<int> split(const std::string &input, const std::string &delimiter);
    int parseNumber(const std::string &numStr);
    void checkForNegatives(const std::vector<int> &numbers);
    int sumNumbers(const std::vector<int> &numbers);
};

#endif // STRINGCALCULATOR_HPP

