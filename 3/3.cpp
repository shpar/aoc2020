#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using Map = std::vector<std::vector<bool>>;

auto loadData() -> Map  {
    Map entries;
    std::ifstream stream("data.txt");
    std::string line;
    int numLine = 0;
    while (std::getline(stream, line)) {
       int numChar = 0;
       std::vector<bool> mapLine;
       for (const char c : line) {
           if (c == '#')
               mapLine.push_back(true);
           else if (c == '.')
               mapLine.push_back(false);
           ++numChar;
       }
       entries.push_back(mapLine);
       mapLine.clear();
       ++numLine;
    }
    return entries;
}

auto countTreesOnWay(const Map& entries, int charInc, int lineInc) -> int 
{
    int maxChars = entries[0].size();
    int res = 0;
    int lineNum = 0;
    int charNum = 0;
    while (lineNum < entries.size())
    {
       if (entries[lineNum][charNum % maxChars]) 
          ++res;
       charNum += charInc;
       lineNum += lineInc;
    }
    return res;
}

auto countAllSlopesMultiplied(const Map& entries) -> long long
{
    std::vector<long long> results;
    results.push_back(countTreesOnWay(entries, 1, 1));
    results.push_back(countTreesOnWay(entries, 3, 1));
    results.push_back(countTreesOnWay(entries, 5, 1));
    results.push_back(countTreesOnWay(entries, 7, 1));
    results.push_back(countTreesOnWay(entries, 1, 2));
    return std::accumulate(results.begin(), results.end(), 1LL, std::multiplies<long long>());
}
auto main() -> int {
    const auto entries = loadData();
    std::cout << "trees on first slope: " << countTreesOnWay(entries, 3, 1) << std::endl;
    std::cout << "all slopes multiplied: " << countAllSlopesMultiplied(entries) << std::endl;
    return 0;
}
