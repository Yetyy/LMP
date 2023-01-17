#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using TInfo = char;
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

void task1_formula_1(Tree root)
{
	if (root->right && root->left)
	{
		task1_formula_1(root->right);
		task1_formula_1(root->left);
		if (root->info == '+' || root->info == '-')
			if (root->left->info == '*' && root->right->info == '*')
			{
				if (check(root->left->left, root->right->left))
				{
					std::swap(root->right->right, root->right->left);
					std::swap(root->left->right, root->left->left);
				}
				else if (check(root->left->left, root->right->right))
				{
					std::swap(root->left->right, root->left->left);
				}
				else if (check(root->left->right, root->right->left))
				{
					std::swap(root->right->right, root->right->left);
				}
				if (check(root->right->right, root->left->right))
				{
					std::swap(root->left->info, root->info);
					Clear(root->left->right);
					root->left->right = root->right->left;
					Tree ptr = root->right->right;
					root->right->left = nullptr;
					root->right->right = nullptr;
					Clear(root->right);
					root->right = ptr;
				}
			}
	}
}

void task2_formula_1(Tree root)
{
	Tree src = root;
	stack st;
	stack oper;

	while (src)
	{
		if (src->left)
		{
			if (src->right)
				st.push(src->right);
			if (src->info == '+' || src->info == '-')
				oper.push(src);
			src = src->left;
		}
		else if (src->right)
		{
			if (src->info == '+' || src->info == '-')
				oper.push(src);
			src = src->right;
		}
		else if (st.empty())
			src = nullptr;
		else
			src = st.pop();
	}
	while (!oper.empty())
	{
		src = oper.Top();
		if (src->left->info == '*' && src->right->info == '*')
		{
			if (check(root->left->left, root->right->left))
			{
				std::swap(root->right->right, root->right->left);
				std::swap(root->left->right, root->left->left);
			}
			else if (check(root->left->left, root->right->right))
			{
				std::swap(root->left->right, root->left->left);
			}
			else if (check(root->left->right, root->right->left))
			{
				std::swap(root->right->right, root->right->left);
			}
			if (check(root->right->right, root->left->right))
			{
				std::swap(root->left->info, root->info);
				Clear(root->left->right);
				root->left->right = root->right->left;
				Tree ptr = root->right->right;
				root->right->left = nullptr;
				root->right->right = nullptr;
				Clear(root->right);
				root->right = ptr;
			}
		}
		oper.pop();
	}
}
bool search(const Tree& root, const Tree& elem)
{
	Tree src = root;
	stack s;
	s.push(root);
	bool res = false;
	int count = 1;
	while (!s.empty() && !res)
	{
		int countNext = 0;
		for (int i = 1; i <= count; i++)
		{
			Tree t = s.pop();
			if (elem->info == t->info && t != elem)res = true;
			if (t->left)
			{
				s.push(t->left);
				++countNext;
			}

			if (t->right)
			{
				s.push(t->right);
				++countNext;
			}
			count = countNext;
		}
	}
	return res;
}

bool search_r(const Tree root, const Tree elem)
{
	bool res = false;
	if (root->info == elem->info && root != elem)
		res = true;
	else
	{
		if (root->right)
			res = search_r(root->right, elem);
		if (root->left)
			res = search_r(root->left, elem);
		return res;
	}

}
bool task1_balance_1(Tree root, Tree croot)
{
	bool res = false;
	if (!res && root->right && !search_r(croot, root->right))
	{
		res = task1_balance_1(root->right, croot);
	}
	else if (root->right)res = true;

	if (!res && root->left && !search_r(croot, root->left))
	{
		res = task1_balance_1(root->left, croot);
	}
	else if (root->left)res = true;
	return res;
}
bool task2_balance_1(Tree root)
{
	Tree src = root;
	stack s;
	s.push(root);
	bool res = false;
	int count = 1;
	while (!s.empty() && !res)
	{
		int countNext = 0;
		for (int i = 1; i <= count; i++)
		{
			Tree t = s.pop();
			if (search(root, t))res = true;
			if (t->left)
			{
				s.push(t->left);
				++countNext;
			}

			if (t->right)
			{
				s.push(t->right);
				++countNext;
			}
			count = countNext;
		}
	}
	return res;
}
void task1_balance_2(Tree root, Tree& max_leaf, Tree& min_leaf, Tree& prev_max, Tree& prev_min)
{
	if (root->right || root->left)
	{
		if (root->right)
		{
			task1_balance_2(root->right, max_leaf, min_leaf, prev_max, prev_min);
			if (root->right == max_leaf)
			{
				prev_max = root;
			}
			else if (root->right == min_leaf)
			{
				prev_min = root;
			}
		}
		if (root->left)
		{
			task1_balance_2(root->left, max_leaf, min_leaf, prev_max, prev_min);
			if (root->left == max_leaf)
			{
				prev_max = root;
			}
			else if (root->left == min_leaf)
			{
				prev_min = root;
			}
		}
	}
	else
	{
		if (!max_leaf || max_leaf->info < root->info)
		{
			max_leaf = root;
		}
		if (!min_leaf || min_leaf->info > root->info)
		{
			min_leaf = root;
		}
	}
}

void task2_balance_2(Tree root, Tree& max_leaf, Tree& min_leaf, Tree& prev_max, Tree& prev_min)
{
	stack bypass;

	bypass.push(root);
	Tree prev = NULL;
	while (!bypass.empty())
	{
		Tree current = bypass.Top(); 
		if (prev == NULL || prev->left == current || prev->right == current)
		{
			if (current->left)
			{
				bypass.push(current->left);
			}
			else if (current->right)
			{
				bypass.push(current->right);
			}
			else
			{
				bypass.pop();
				if (!max_leaf || max_leaf->info < current->info)
				{
					max_leaf = current;
				}
				if (!min_leaf || min_leaf->info > current->info)
				{
					min_leaf = current;
				}
			}
		}
		else if (current->left == prev)
		{
			if (current->right)
			{
				bypass.push(current->right);
			}
			else
			{
				bypass.pop();
				if (current->left == max_leaf)
				{
					prev_max = current;
				}
				else if (current->left == min_leaf)
				{
					prev_min = current;
				}
			}
		}
		else if (current->right == prev)
		{
			bypass.pop();
			if (current->right == max_leaf)
			{
				prev_max = current;
			}
			else if (current->right == min_leaf)
			{
				prev_min = current;
			}
		}
		prev = current;
	}
}



TInfo task1_search_1(Tree t)
{
	TInfo result = 0;
	if (t)
	{
		if (t->left)
			result = task1_search_1(t->left);
		else if (t->right)
			result = task1_search_1(t->right);
		else
			result = t->info;
	}

	return result;
}

TInfo task2_search_1(Tree root)
{
	std::queue<Tree> q;
	q.push(root);
	int count = 1;
	TInfo result = 0;
	bool flag = false;
	while (!q.empty() && !flag)
	{
		int countNext = 0;
		for (int i = 1; i <= count; i++)
		{
			Tree t = q.front();
			q.pop();
			if (t->left)
			{
				q.push(t->left);
				++countNext;
			}
			else if (t->right)
			{
				q.push(t->right);
				++countNext;
			}
			else if (i == 1) // first in queue - left elem
			{
				flag = true;
				result = t->info;
			}

			/*	if (t->right && !flag)
				{
					q.push(t->right);
					++countNext;
				}*/
		}
		count = countNext;
	}
	return result;
}
void main()
{
	std::ifstream file("form.txt");
	Tree root;
	root = Build_Formula(file);
	tree_formula(root);

	std::cout << '\n';
	Print(root);
	std::cout << '\n';
	//task2(root);
	tree_formula(root);
	std::cout << '\n';
	Print(root);
	Clear(root);
	std::cin.get();
}