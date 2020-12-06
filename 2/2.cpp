#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

struct PasswordEntry
{
    int min;
    int max;
    char rule;
    std::unordered_map<char, int> occurences;
    std::string pass;
};

auto loadPasswordEntries() -> std::vector<PasswordEntry>  {
    std::vector<PasswordEntry> entries;
    std::ifstream stream("data.txt");
    std::string line;
    while (std::getline(stream, line)) {
       auto entry = PasswordEntry{};
       auto& occ = entry.occurences;
       char ignore;
       std::string delimiter;
       std::string pass;
       std::istringstream lineStream(line);
       lineStream >> entry.min;
       getline(lineStream, delimiter, '-'); 
       lineStream >> entry.max;
       lineStream >> entry.rule;
       lineStream >> ignore;
       getline(lineStream, pass, '\n'); 
       entry.pass = pass.substr(1);
       
       std::cout << entry.pass << std::endl;
       for (const char c : entry.pass) {
           std::cout << "curr " << c << std::endl;
           if (occ.find(c) == occ.end())
           {
               std::cout << "emplaced" << std::endl;
               occ.emplace(c, 1);
           }
           else
           {
               auto i = occ[c];
               std::cout << i << "num occ" << std::endl;
               occ[c] = i + 1;
           }
       }
       std::cout << entry.min << std::endl;
       std::cout << entry.max << std::endl;
       std::cout << entry.rule << std::endl;
       std::cout << occ[entry.rule] << std::endl;
       entries.emplace_back(entry);
    }
    return entries;
}

auto countValidEntries(const std::vector<PasswordEntry>& entries) -> int {
    int res;
    std::cout << "nm entries: " << entries.size() << std::endl;
    for (const auto& entry : entries) {
        auto& occ = entry.occurences;
        if (occ.find(entry.rule) != occ.end() && occ.at(entry.rule) >= entry.min && occ.at(entry.rule) <= entry.max)
        {
            ++res;
        }
    }
    return res;
}

auto countValidEntriesTwo(const std::vector<PasswordEntry>& entries) -> int {
    int res;
    std::cout << "nm entries: " << entries.size() << std::endl;
    for (const auto& entry : entries) {
        if ((entry.pass[entry.min-1] == entry.rule && entry.pass[entry.max-1] != entry.rule) ||
            (entry.pass[entry.min-1] != entry.rule && entry.pass[entry.max-1] == entry.rule))
        {
            ++res;
        }
    }
    return res;
}
auto main() -> int {
    const auto entries = loadPasswordEntries();
    std::cout << countValidEntries(entries) << std::endl;
    std::cout << countValidEntriesTwo(entries) << std::endl;
    return 0;
}
