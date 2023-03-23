#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <functional>

void findUniqueWords(const std::string& filename, std::function<bool(const std::string&)> checkProperty) {
    std::ifstream file(filename);
    std::string line;
    std::set<std::string> uniqueWords;
    std::set<std::string> notuniqueWords;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            if (checkProperty(word))
            {
                if (uniqueWords.find(word) != uniqueWords.end() || notuniqueWords.find(word) != notuniqueWords.end())
                {
                    notuniqueWords.insert(word);
                    uniqueWords.erase(word);
                }
                else
                    uniqueWords.insert(word);
            }
        }
    }
    for (const auto& word : uniqueWords) {
        std::cout << word << std::endl;
    }
}


int main() {
    std::string filename = "test.txt";
    std::string input;
    std::cin >> input;
    findUniqueWords(filename, [input](const std::string& word) { return word.find(input) == 0; });
}