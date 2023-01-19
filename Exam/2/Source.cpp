
#include <iostream>
#include <fstream>
#include "My_List.h"
/*
удалить центральный элемент если список содержит нечетное кол-во элементов
*/
bool task_1(DLIST& list)
{
	bool result = false;
	ptrNODE p = list.get_begin(), q = list.get_end();
	while (p != q && p->next != q)
	{
		p = p->next;
		q = q->prev;
	}

	if (p == q)
	{
		result = true;
		list.del_after(p->prev);
	}
	return result;
}

/*
если список содержит четное кол-во элементов то вставить в центр сумму всех чисел
*/
bool task_2(DLIST& list)
{
	bool result = false;
	ptrNODE p = list.get_begin(), q = list.get_end();
	int sum = p->info + q->info;
	while (p != q && p->next != q)
	{
		p = p->next;
		q = q->prev;
		sum += p->info + q->info;
	}

	if (p->next == q)
	{
		result = true;
		list.add_after(p, sum);
	}
	return result;
}
bool task_3(DLIST& list,ptrNODE& p, ptrNODE& prelast, ptrNODE& last)
{
	if (p->next)
	{
		if (std::abs(p->info % 2) == 0)
		{
			prelast = last;
			last = p->next->prev;
		}
		task_3(list,p->next, prelast, last);
	}
	list.Delete(prelast);
}
int main()
{
	std::ifstream file("input.txt");
	DLIST list(file);
	list.print();
	task_1(list);
	list.print();
}