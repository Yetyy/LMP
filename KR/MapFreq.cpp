#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <functional>

int main()
{
    std::ifstream file("test.txt");
    std::string line;
    std::string sub = "as";
    std::map<std::string, int> freq;
    auto check = [](std::string word, std::string sub) {
        return word.find(sub) != std::string::npos;
    };
    while (std::getline(file, line))
    {
        std::stringstream sstream(line);
        std::string word;
        while (sstream >> word)
        {
            freq[word]++;
        }
    }
    for (auto i : freq)
    {
        if (check(i.first, sub))
            std::cout << i.first << ' ';
    }
    return 0;
}