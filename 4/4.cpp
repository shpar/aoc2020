#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <sstream>
#include <unordered_map>
#include <vector>

auto validId(const std::string_view s) -> bool {
    return s == "byr" || s == "iyr" || s == "eyr" || s == "hgt" || s == "hcl" || s == "ecl" || s == "pid" || s == "cid";
}

auto validByr(const std::string& entry) -> bool {
    return (entry.size() == 4 && std::stoi(entry) >= 1920 && std::stoi(entry) <= 2002);
}

auto validIyr(const std::string& entry) -> bool {
    return (entry.size() == 4 && std::stoi(entry) >= 2010 && std::stoi(entry) <= 2020);
}

auto validEyr(const std::string& entry) -> bool {
    return (entry.size() == 4 && std::stoi(entry) >= 2020 && std::stoi(entry) <= 2030);
}

auto validPid(const std::string& entry) -> bool {
    return (entry.size() == 9 && std::all_of(entry.begin(), entry.end(), ::isdigit));
}

auto validEcl(const std::string& entry) -> bool {
    return (entry == "amb" || entry == "blu" || entry == "brn" || entry == "gry" || entry == "grn" || entry == "hzl" || entry == "oth");
}

auto validHcl(const std::string& entry) -> bool {
    if (entry.size() != 7 || entry[0] != '#')
        return false;
    const auto hcl = entry.substr(1);
    const auto left = 'a';
    const auto right = 'f';
    for (const char c : hcl) {
        if (!::isdigit(c) && (std::strcmp(&c, &left) <= 0 || std::strcmp(&c, &right) >= 0))
            return false;
    }
    return true;
}

auto validHgt(const std::string& entry) -> bool {
    if (entry.find("cm") != std::string::npos && entry.size() == 5)
    {
       const auto digit = entry.substr(0, 3); 
       return std::all_of(digit.begin(), digit.end(), ::isdigit) && (std::stoi(digit) >= 150 || std::stoi(digit) <= 193);
    }
    else if (entry.find("in") != std::string::npos && entry.size() == 4) {
       const auto digit = entry.substr(0, 2);
       return std::all_of(digit.begin(), digit.end(), ::isdigit) && (std::stoi(digit) >= 59 || std::stoi(digit) <= 76);
    }
    return false;
}

auto validIdAndEntry(const std::string_view id, const std::string& entry) -> bool {
    return (id == "byr" && validByr(entry)) ||
           (id == "iyr" && validIyr(entry)) ||
           (id == "eyr" && validEyr(entry)) ||
           (id == "hgt" && validHgt(entry)) ||
           (id == "hcl" && validHcl(entry)) ||
           (id == "ecl" && validEcl(entry)) ||
           (id == "pid" && validPid(entry)) ||
           id == "cid";
}
auto loadAndValidateStream(bool strictValidation) -> int {
    int res = 0;
    std::ifstream stream("data.txt");
    std::string line;
    int entries = 0;
    bool hasCid = false;
    while (std::getline(stream, line)) {
       if (line.empty())
       {
           if (entries == 8 || (entries == 7 && !hasCid))
           {
               ++res;
           }
           entries = 0;
           hasCid = false;
       }
       std::string entry;
       std::istringstream lineStream(line);
       std::string code;
       while(getline(lineStream, code, ':'))
       {
           lineStream >> entry;
           if (code.size() == 4)
               code = code.substr(1);
           auto entryValid = strictValidation ? validIdAndEntry(code, entry) : validId(code);
           if (code == "cid")
               hasCid = true;
           if (entryValid)
               ++entries;
       }
    }
    return res;
}

auto main() -> int {
    const auto looseValidationCount = loadAndValidateStream(false);
    const auto strictValidationCount = loadAndValidateStream(true);
    std::cout << "loose validation: " << looseValidationCount << std::endl;
    std::cout << "strict validation: " << strictValidationCount << std::endl;
    return 0;
}
