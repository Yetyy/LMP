#include "My_list.h"
#include <functional>


DLIST::DLIST(std::ifstream& file)
{
	TInfo elem;
	file >> elem;
	first_node(elem);
	ptrNODE place;
	while (!file.eof())
	{
		TInfo elem; file >> elem;
		/*place = find_place(begin, elem);
		if (place)
			add_before(place, elem);
		else*/
		add_after(end, elem);
	}
	file.close();

	end->next = begin;
	begin->prev = end;
}

void DLIST::first_node(const TInfo elem)
{
	begin = new NODE(elem);
	end = begin;
}

bool DLIST::empty()
{
	return begin == nullptr;
}

ptrNODE DLIST::find_place(ptrNODE begin, const TInfo elem)
{
	ptrNODE p = begin;
	while (p && p->info < elem)
		p = p->next;
	return p;
}

void DLIST::add_after(ptrNODE ptr, const TInfo elem)
{
	ptrNODE p = new NODE(elem, ptr->next, ptr);
	if (ptr == end)
		end = p;
	else
		ptr->next->prev = p;
	ptr->next = p;
}

void DLIST::add_before(ptrNODE ptr, const TInfo elem)
{
	ptrNODE p = new NODE(elem, ptr->next, ptr);
	if (ptr == end)
		end = p;
	else
		ptr->next->prev = p;
	ptr->next = p;
}



std::string DLIST::to_string() const
{
	std::string result;
	ptrNODE ptr = begin;
	while (ptr)
	{
		result += std::to_string(ptr->info) + ' ';
		ptr = ptr->next;
	}
	result += '\n';
	return result;
}

void DLIST::print() const
{
	ptrNODE p = begin, start = p;
	//p = p->next;
	while (p->next != start)
	{
		std::cout << p->info << ' ';
		p = p->next;
	}
	std::cout << p->info << ' ';
	std::cout << '\n';
}

//template<typename T>
//ptrNODE<T>& DLIST<T>::del_before(ptrNODE<T>& ptr)
//{
//	ptrNODE<T> tmp = ptr->prev;
//	ptr->prev = tmp->prev;
//	if (!tmp->prev)
//		begin = ptr;
//	else
//		tmp->prev->next = ptr;
//
//	static ptrNODE<T> a;
//	a = tmp->next;
//
//	delete tmp;
//	size--;
//	return a;
//}
//

ptrNODE& DLIST::Delete(ptrNODE& ptr)
{
	ptrNODE p = ptr;
	if (ptr == begin)
	{
		begin = p->next;
		ptr = begin;
		if (p->next)
			p->next->prev = nullptr;
	}
	else
		if (ptr == end)
		{
			end = p->prev;
			ptr = end;
			if (p->prev)
				p->prev->next = nullptr;
		}
		else
		{
			ptr = ptr->next;
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}
	static ptrNODE a;
	a = p->next;

	delete p;
	size--;
	return a;
}