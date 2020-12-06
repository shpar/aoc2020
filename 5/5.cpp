#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

auto loadData() -> std::vector<std::string> {
    std::vector<std::string> res;
    std::ifstream stream("data.txt");
    std::string line;
    while (std::getline(stream, line)) {
        res.push_back(line);
    }
    return res;
}

auto getPosition(const std::string& s, std::pair<int, int> limits, std::pair<char, char> code)
{
    int left = limits.first;
    int right = limits.second;
    for (const auto c : s) {
        int reduce = (right - left) / 2 + (right - left) % 2;
        if (c == code.first) 
        {
            right -= reduce;
        }
        else if (c == code.second) 
        {
            left += reduce;
        }
    }
    return left;
}


auto getRow(const std::string& s) -> int {
    return getPosition(s, {0, 127}, {'F', 'B'});
}

auto getColumn(const std::string& s) -> int {
    return getPosition(s, {0, 7}, {'L', 'R'});
}

auto getId(int row, int column) -> int {
    return row * 8 + column;
}

auto getHighestSeatId(const std::vector<std::string>& v) {
    int highestId = 0;
    for (const auto& pass : v)
    {
        highestId = std::max(getId(getRow(pass), getColumn(pass)), highestId);
    }
    return highestId;
}

auto findMissingSeat(const std::vector<std::string>& v) -> int {
    std::vector<std::pair<int, int>> seats;
    std::vector<int> ids;
    for (const auto& pass : v)
    {
       const auto row = getRow(pass);
       const auto column = getColumn(pass);
       seats.push_back(std::make_pair(row, column));
       ids.push_back(getId(row, column));
    }
    std::vector<std::pair<int, int>> missing;
    for (int row = 0; row < 128; ++row)
    {
        for (int column = 0; column < 8; ++column)
        {
            if (std::find_if(seats.begin(), seats.end(), [row, column] (const auto& pair) {
                    return pair.first == row && pair.second == column;
                }) == seats.end())
                missing.push_back(std::make_pair(row, column));
        }
    }
    for (const auto& missingSeat : missing) {
        const auto seatId = getId(missingSeat.first, missingSeat.second);
        if (std::find(ids.begin(), ids.end(), seatId - 1) != ids.end() 
            && std::find(ids.begin(), ids.end(), seatId + 1) != ids.end())
            return seatId;
    }
    return 0;
}

auto main() -> int {
    const auto data = loadData();
    std::cout << "highest id: " << getHighestSeatId(data) << std::endl;
    std::cout << "missing id: " << findMissingSeat(data) << std::endl;
    return 0;
}
