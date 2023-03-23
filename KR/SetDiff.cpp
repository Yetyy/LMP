//(set)find words that are repeated and do not have repeated letters
#include <iostream>
#include <fstream>
#include <functional>

auto check = [](std::string word)
{
    std::set<char> s;
    int i=0;
    while (i < word.size() && s.find(word[i]) == s.end())
    {
        s.insert(word[i]);
        i++;
    }
    return i == word.size();
};

void print(std::set<std::string>);
std::set<std::string> Task(std::string, std::function<bool(std::string)>);

int main()
{
    std::string file_name("test.txt");
    std::set<std::string> S = Task(file_name, check);
    print(S);
    return 0;
}

std::set<std::string> Task(std::string file_name, std::function<bool(std::string)> comp)
{
    std::ifstream file(file_name);
    std::set<std::string> tmp;
    std::set<std::string> result;
    std::string word;
    while (file >> word)
    {
        if (comp(word))
            if (tmp.find(word) != tmp.end())
                result.insert(word);
            else
                tmp.insert(word);
    }
    file.close();
    return result;
}

void print(std::set<std::string> S)
{
    for (auto i : S)
        std::cout << i << ' ';
}