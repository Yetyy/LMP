#include "My_List.h"
/*
file.clear();
file.seekg(0);
*/

using std::cin;
using std::cout;

void main()
{
	LIST list;
	LIST list2;
	std::ifstream file("data.txt");
	if (file)
	{
		list.create_by_queue(file);
		list.print();
		cout << '\n';
		file.close();
	}
	std::cin.get();
}

//recursion 

int sum(const ptrNODE head)
{
	int result = 0;
	if (head)
		result = head->info + sum(head->next);
	return result;
}

int count(const ptrNODE head)
{
	int result = 0;
	if (head)
	{
		result = ((head->info % 2 != 0) ? 1 : 0) + count(head->next);
	}
	return result;
}
//copy list
void copy_list(LIST& kuda, ptrNODE otkuda)
{
	if (otkuda)
	{
		kuda.add_to_tail(otkuda->info);
		copy_list(kuda, otkuda->next);
	}
	kuda.get_tail()->next = nullptr;
}
//double even elem
void doublee(LIST& list, ptrNODE elem)
{
	if (elem && elem->info % 2 == 0)
	{
		list.add_after(elem, elem->info);
		doublee(list, elem->next->next);
	}
	else if (elem)
	{
		doublee(list, elem->next);
	}
}

//find elem
//last even
ptrNODE before_last_even(LIST& list)
{
	ptrNODE result = nullptr;
	ptrNODE p = list.get_head()->next;
	while (p->next)
	{
		if (p->next->info % 2 == 0)
		{
			result = p;

		}
		p = p->next;
	}
	return result;
}
//min
ptrNODE before_min_elem(LIST& list)
{
	ptrNODE p = list.get_head()->next;
	int min = p->info;
	ptrNODE min_pos = nullptr;
	while (p->next)
	{
		if (p->next->info < min)
		{
			min = p->next->info;
			min_pos = p;
		}
		p = p->next;
	}
	return min_pos;
}
//max 
ptrNODE before_max_elem(LIST& list)
{
	ptrNODE p = list.get_head();
	int max = p->next->info;
	ptrNODE result = p->next;
	while (p->next)
	{
		if (p->next->info > max)
		{
			max = p->next->info;
			result = p;
		}
		p = p->next;
	}
	return result;
}



bool is_two_number(int x)
{
	return (x / 10 > 9 ? 1 : 0);
}
//before last XX-number enter XX^2
bool task_5(LIST& list)
{
	bool result = false;
	ptrNODE p = list.get_head();
	ptrNODE last_two = nullptr;

	while (p->next)
	{
		if (is_two_number(p->next->info))
		{
			last_two = p;
			result = true;
		}
		p = p->next;
	}
	if(last_two)
	list.add_after(last_two, last_two->next->info * last_two->next->info);

	return result;
}

//delete first and last elem even 7
ptrNODE find_elem(LIST& list, bool is_first)
{
	auto is_even = [](int elem) {return elem != 0 && elem % 7 == 0; };
	ptrNODE result = nullptr, p = list.get_head();

	if (is_first)
	{
		while (p->next && !result)
		{
			if (is_even(p->next->info))
			{
				result = p;
			}
			else
			{
				p = p->next;

			}
		}
	}
	else
	{
		while (p->next)
		{
			if (is_even(p->next->info))
			{
				result = p;
			}
			p = p->next;
		}
	}
	return result;
}

bool task_6(LIST& list)
{
	bool result = false;
	ptrNODE first = find_elem(list, true), last = find_elem(list, false);
	if (first && last && first != last)
	{
		list.del_after(first);
		list.del_after(last);
		result = true;
	}
	else if (first && last)
	{
		list.del_after(first);
		result = true;
	}

	return result;
}

//delete elem after last even
bool task_2(LIST& list, int count)
{
	bool result = true;
	ptrNODE p = before_last_even(list);
	for (size_t i = 0; i < count; i++)
	{
		if (p)
			list.del_after(p);
		else
			result = false;

		p = before_last_even(list);
	}
	return result;
}


//find max elem and move it at head
bool task_7(LIST& list)
{
	auto switch_pointers = [](ptrNODE q, ptrNODE p)
	{
		ptrNODE tmp = p->next;
		p->next = tmp->next;
		tmp->next = q->next;
		q->next = tmp;
	};

	bool flag = true;
	ptrNODE elem = before_max_elem(list);
	if (elem)
		switch_pointers(list.get_head(), elem);
	else
		flag = false;

	return flag;
}

//move min elem at the head
bool task_3(LIST& list)
{
	auto switch_pointers =
		[](ptrNODE q, ptrNODE p)
	{
		ptrNODE tmp = p->next;
		p->next = tmp->next;
		tmp->next = q->next;
		q->next = tmp;
	};
	bool result = true;
	ptrNODE p = before_min_elem(list);
	if (p)
	{
		if (p->next == list.get_tail())
		{
			p->next = list.get_head();
			list.set_tail(p);
		}
		else
		{
			switch_pointers(list.get_head(), p);

		}
	}
	else
		result = false;
	return result;
}