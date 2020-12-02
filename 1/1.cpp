#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

auto loadNumbers() -> std::vector<int>  {
    std::vector<int> numbers;
    std::ifstream stream("data.txt");
    int i;
    while (stream >> i) {
        numbers.push_back(i);
    }
    return numbers;
}

auto numbersAddingUpToTwo(const std::vector<int>& numbers, int targetSum) -> std::vector<int> {
    for (const auto number : numbers) {
        const auto target = targetSum - number;
        if (std::binary_search(numbers.cbegin(), numbers.cend(), target)) {
            return {number, target};
        }
    }
    return {};
}

auto numbersAddingUpToThree(const std::vector<int>& numbers, int targetSum) -> std::vector<int> {
    for (const auto number : numbers) {
        const auto target = targetSum - number;
        auto result = numbersAddingUpToTwo(numbers, target);
        if (!result.empty()) {
            result.push_back(number);
            return result;
        }
    }
    return {};
}

auto main() -> int {
    const auto targetSum = 2020;
    auto numbers = loadNumbers();
    std::sort(numbers.begin(), numbers.end());
    const auto twoNumbers = numbersAddingUpToTwo(numbers, targetSum);
    const auto threeNumbers = numbersAddingUpToThree(numbers, targetSum);
    std::cout << "first result: " <<  std::accumulate(twoNumbers.begin(), twoNumbers.end(), 1, std::multiplies<int>()) << std::endl;
    std::cout << "second result: " <<  std::accumulate(threeNumbers.begin(), threeNumbers.end(), 1, std::multiplies<int>()) << std::endl;
    return 0;
}
