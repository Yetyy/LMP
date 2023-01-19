#include "My_List.h"
#include <functional>

void task_1(LIST& list, std::function<bool(ptrNODE&)> lambda)
{
	ptrNODE prelast = nullptr;
	ptrNODE last = nullptr;
	ptrNODE ptr = list.get_head();
	while (ptr->next)
	{
		if (lambda(ptr->next))

		{
			prelast = last;
			last = ptr;
		}
		ptr = ptr->next;
	}
	if (prelast)
	{
		while (prelast->next != last)
			list.del_after(prelast);
		list.del_after(prelast);
		list.del_after(prelast); 
	}
}
void task_2(LIST& list)
{
	ptrNODE ptr = list.get_head();
	ptrNODE p_elem=nullptr;
	while (ptr->next)
	{
		if (std::abs(ptr->next->info) % 3 == 0) p_elem = ptr;
		ptr = ptr->next;
	}
	if (p_elem)
	{
		ptrNODE end=list.get_tail();
		ptrNODE tmp = p_elem->next;
		end->next = p_elem->next;
		p_elem->next = p_elem->next->next;
		list.set_tail(p_elem);
		tmp->next = nullptr;
	}
 }
void main()
{


	LIST list;
	std::ifstream file("input.txt");
	if (file)
	{
		list.create_by_queue(file);
		file.close();
		list.print();
		std::cout << "\n";
		auto lamda = [](ptrNODE& ptr) {return ptr->info % 10 == 7; };
		task_2(list);
		list.print();
	}


	std::cin.ignore();
	std::cin.get();
}