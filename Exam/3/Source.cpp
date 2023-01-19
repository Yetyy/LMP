#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using TInfo = int;
struct NODE
{
	TInfo info;
	NODE* left, * right;
	int count = 1;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) : info(info), left(left), right(right) {}
	~NODE()
	{
		left = nullptr;
		right = nullptr;
	}
};

using Tree = NODE*;

void Clear(Tree& t)
{
	if (t)
	{
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = nullptr;
	}
}

void Print(Tree t, int level = 0)
{
	if (t)
	{
		Print(t->right, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << ' ';
		std::cout << t->info << '\n';
		Print(t->left, level + 1);
	}
}


using TElem = Tree;

void add(Tree& t, TInfo elem)
{
	if (!t)
		t = new NODE(elem);
	else
		if (elem < t->info)
			add(t->left, elem);
		else
			if (elem > t->info)
				add(t->right, elem);
			else
				t->count++;
}
Tree search(const Tree& root, TInfo elem)
{
	Tree t = root, ptr = nullptr;
	while (t && !ptr)
	{
		if (elem < t->info)
			t = t->left;
		else
			if (elem > t->info)
				t = t->right;
			else
				ptr = t;
	}
	return ptr;
}
Tree Build_Search(std::string file_name)
{
	std::ifstream file(file_name);
	Tree root = nullptr;
	int elem;
	while (file >> elem)
		add(root, elem);
	file.close();
	return root;
}
Tree Build_Balans(std::ifstream& file, int count)
{
	Tree result = nullptr;
	if (count)
	{
		int count_left = count / 2;
		int count_right = count - count_left - 1;
		int x;
		file >> x;
		result = new NODE(x);
		result->left = Build_Balans(file, count_left);
		result->right = Build_Balans(file, count_right);
	}
	return result;
}
Tree Build_Formula(std::ifstream& file)
{
	char c = file.get();
	Tree root = new NODE(' ');
	if (c >= '0' && c <= '9')
		root->info = c;
	else
	{
		root->left = Build_Formula(file);
		root->info = file.get();
		root->right = Build_Formula(file);
		c = file.get();
	}
	return root;
}

void tree_formula(Tree root)
{
	if (root)
	{
		if (!(root->info >= '0' && root->info <= '9'))
			std::cout << '(';
		tree_formula(root->left);
		std::cout << root->info;
		tree_formula(root->right);
		if (!(root->info >= '0' && root->info <= '9'))
			std::cout << ')';
	}
}

using SInfo = Tree;

class stack
{
private:
	SInfo* elements;
	int size;
	int top;
public:
	stack();
	~stack();
	bool empty();
	bool full();
	void resize(int n_size);
	int get_alloc_size();
	void push(SInfo elem);
	SInfo pop();
	SInfo Top();
	void View();
};

stack::stack()
{
	size = 1;
	elements = new SInfo[size];
	top = -1;
}

stack::~stack()
{
	delete[] elements;
}

bool stack::empty()
{
	return top == -1;
}

bool stack::full()
{
	return top == size - 1;
}

void stack::resize(int n_size)
{
	if (n_size > size)
	{
		SInfo* temp = new SInfo[n_size];
		for (int i = 0; i <= top; i++)
			temp[i] = elements[i];
		size = n_size;
		delete[] elements;
		elements = temp;
	}
}

int stack::get_alloc_size()
{
	return size;
}

void stack::push(SInfo elem)
{
	if (size == top + 1)
		resize(2 * size);
	elements[++top] = elem;
}

SInfo stack::pop()
{
	SInfo elem = elements[top--];
	return elem;
}

SInfo stack::Top()
{
	return elements[top];
}

void stack::View()
{
	for (int i = top; i >= 0; i--)
		std::cout << elements[i] << ' ';
	std::cout << std::endl;
}


bool check(Tree r1, Tree r2)
{
	if (r1->right && r1->left && r2->right && r2->left)
	{
		return (r1->info == r2->info) && check(r1->right, r2->right) && check(r1->left, r2->left);
	}
	else
	{
		if (r1->info == r2->info)
		{
			if ((!r1->right && !r2->right))
				if ((!r1->left && !r2->left) || (r1->left && r2->left && ((r1->left->info) == (r2->left->info))))
					return true;
		}
		else if ((!r1->left && !r2->left))
			if (r1->right && r2->right && ((r1->right->info) == (r2->right->info)))
				return true;
		return false;
	}
}


void task_1(Tree& t, int h, int count = 0)
{

	if (count > h)
		Clear(t);
	if (t)
	{
		task_1(t->left, h, count + 1);
		task_1(t->right, h, count + 1);
	}
}
void task_2(Tree& t)
{
	
	
		if (std::abs(t->info%2) == 1)
		{
			if(t->left)
			Clear(t->left);
			if (t->right)
			Clear(t->right);
		}
		else
		{
			if (t->left)
				task_2(t->left);
			if (t->right)
				task_2(t->left);
		}
	
}
void main()
{
	std::ifstream file("numbers.txt");

	Tree root = Build_Balans(file, 7);
	Print(root, 0);

	task_2(root);
	std::cout << "----------------------\n";
	Print(root, 0);

	Clear(root);
	std::cin.get();
}