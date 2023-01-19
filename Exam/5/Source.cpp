#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

struct NODE
{
    NODE* ptrs[26];
    bool eow = false;
    NODE()
    {
        for (int i = 0; i < 26; ++i)
            ptrs[i] = nullptr;
    }
};

using TrieTree = NODE*;

void init(TrieTree& root)
{
    root = nullptr;
}

bool empty(TrieTree root)
{
    return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
    if (!t)
    {
        t = new NODE;
    }
    if ((word.length()) - 1 < i)
        t->eow = true;
    else
        add(t->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptr_empty(TrieTree t)
{
    bool res = true;
    size_t i = 0;
    while (i < 26 && res)
        if (!t->ptrs[i])
            ++i;
        else
            res = false;
    return res;
}

void del(TrieTree& t, const std::string word, size_t i)
{
    if (t)
        if (i <= word.length() - 1)
            del(t->ptrs[word[i] - 'a'], word, i + 1);
        else
        {
            t->eow = false;
            if (all_ptr_empty(t))
            {
                delete t;
                t = nullptr;
            }
        }
}

TrieTree& find_root(TrieTree& t, const std::string word, size_t i)
{
    if (t)
    {
        if (i <= word.length() - 1)
            find_root(t->ptrs[word[i] - 'a'], word, i + 1);
        else return t;
    }
}

void print(TrieTree t, std::string word)
{
    if (t->eow)
    {
        std::cout << word << '\n';
    }
    for (size_t i = 0; i < 26; ++i)
    {
        if (t->ptrs[i])
        {
            print(t->ptrs[i], word + char(i + 'a'));
        }
    }
}

void print_2(TrieTree t, std::string word, int& count)
{
    if (t->eow)
    {
        count++;
        std::cout << word << '\n';
    }
    for (size_t i = 0; i < 26; ++i)
    {
        if (t->ptrs[i])
        {
            print_2(t->ptrs[i], word + char(i + 'a'), count);
        }
    }
}

bool task_1(TrieTree& t, const std::string word, size_t i)
{
    bool result = false;
    TrieTree root = nullptr;
    if (t)
    {
        if (i < word.length())
            task_1(t->ptrs[word[i] - 'a'], word, i + 1);
        else root = t;
    }
    int count = 0;
    if (root)
    {
        print_2(root, word, count);
        std::cout << count << '\n';
        result = true;
    }
    return result;
}

void clear(TrieTree& t)
{
    for (size_t i = 0; i < 26; ++i)
        if (t->ptrs[i])
            clear(t->ptrs[i]);
    delete t;
    t = nullptr;
}

bool include(std::string word, std::string set)
{
    bool* flags = new bool[set.length()]{ 0 };

    int pos = 0;
    for (size_t i = 0; i < word.length(); i++)
    {
        pos = set.find(word[i]);
        if (pos != -1)
            flags[pos] = true;
    }

    bool res = true;
    size_t i = 0;
    while (i < set.length() && res)
    {
        if (!flags[i])
            res = false;
        i++;
    }

    return res;
}

TrieTree copy(TrieTree root) {
    if (!root) return nullptr;
    TrieTree new_root = new NODE;

    new_root->eow = root->eow;
    for (int i = 0; i < 26; ++i) {
        new_root->ptrs[i] = copy(root->ptrs[i]);
        
    }
    if (root->eow)
    {
        TrieTree add_root = new NODE;
        new_root->ptrs[0] = add_root;
        new_root->ptrs[0]->eow = true;
        new_root->eow = false;
    };
    return new_root;
}
TrieTree copy_2(TrieTree root) {
    if (!root) return nullptr;
    TrieTree new_root = new NODE;


    for (int i = 0; i < 26; ++i) {
        if(root->ptrs[i])
        if (root->ptrs[i]->eow) 
            new_root->eow=true;
        else
            new_root->ptrs[i] = copy_2(root->ptrs[i]);

    }
    if (root->eow)
    {
        TrieTree add_root = new NODE;
        new_root->ptrs[0] = add_root;
        new_root->ptrs[0]->eow = true;
        new_root->eow = false;
    };
    return new_root;
}
void task_1(TrieTree& tree)
{
	for (int i = 0; i < 26; i++)
	{

		if (tree->ptrs[i])
		{
            task_1(tree->ptrs[i]);
		}
	}
	if (tree->eow)
	{
		if (!tree->ptrs[0])
		{
			TrieTree t = new NODE;
			tree->ptrs[0] = t;
		}
		tree->ptrs[0]->eow = true;
		tree->eow = false;
	}
}
int count_words(TrieTree& t, std::string key, size_t ind)
{
    int result = 0;
    if (t->eow && ind >= key.length())
    {
        ++result;
    }

    for (size_t i = 0; i < 26; i++)
    {
        if (t->ptrs[i])
        {
            if (ind < key.length() && key[ind] == 'a' + i)
            {
                result += count_words(t->ptrs[i], key, ind + 1);
            }
            else if (ind >= key.length())
            {
                result += count_words(t->ptrs[i], key, ind);

            }
        }
    }

    return result;
}
int main()
{

	std::ifstream file("D.txt");
	TrieTree root;
	init(root);
	std::string word;
	while (std::getline(file, word))
	{
		if (word.length())
			add(root, word, 0);
	}
	file.close();
	print(root, "");

    TrieTree c_root= copy_2(root);

	
	print(c_root, "");
	clear(root);

}