#pragma once
#include <iostream>
#include <fstream>
#include <string>

using TInfo = int;
struct NODE
{
	TInfo info;
	NODE* next, * prev;
	NODE(TInfo info, NODE* next = nullptr, NODE* prev = nullptr) :info(info), next(next), prev(prev) {}
	~NODE()
	{
		next = nullptr;
		prev = nullptr;
	}
};

using ptrNODE = NODE*;


struct DLIST
{
private:
	ptrNODE begin, end;
public:
	size_t size;
	DLIST() { begin = nullptr; end = nullptr; }
	DLIST(std::ifstream& file);
	void first_node(const TInfo);
	bool empty();
	ptrNODE find_place(ptrNODE begin, const TInfo);
	void add_after(ptrNODE ptr, const TInfo);
	void add_before(ptrNODE ptr, const TInfo);
	//~DLIST();
	ptrNODE& Delete(ptrNODE& ptr);
	//ptrNODE<T>& del_before(ptrNODE<T>& ptr);
	//ptrNODE<T>& del_after(ptrNODE<T>& ptr);
	ptrNODE get_begin() const
	{
		return begin;
	}
	ptrNODE get_end() const
	{
		return end;
	}
	//friend std::ostream& operator <<(std::ostream& stream, const T list);
	std::string to_string() const;
	void print() const;
};