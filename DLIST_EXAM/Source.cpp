#include <iostream>
#include "My_list.h"
#include <iostream>
#include <fstream>
//DLIST циклический
using std::cin;
using std::cout;
//соседи равны
void task_1(DLIST& list)
{
    int counter = 0;
    ptrNODE p = list.get_begin();
    ptrNODE start = p;
    p = p->next;
    int test = p->info;
    test = p->next->info;
    while (p != start)
    {
        if (p->prev->info == p->next->info)
        {
            counter++;
        }
        p = p->next;
    }
    if (p->prev->info == p->next->info) counter++;
    cout << counter;
}

void task_2(DLIST& list, TInfo e)
{

    /*auto switch_pointers = [](ptrNODE p, ptrNODE q)
    {
        ptrNODE tmp = p->next;
        p->next = q->next;
        p->next->prev = p;
        p->prev->next = q;
    };*/
    ptrNODE first = 0, last = 0, p = list.get_begin();

    while (!first)
    {
        if (p->info == e)
            first = p;
        else
            p = p->next;
    }

    p = list.get_end();

    while (!last)
    {
        if (p->info == e)
            last = p;
        else
            p = p->prev;
    }

    if (first && last && first != last)
    {
        ptrNODE end = list.get_end();
        p = list.get_begin();
        while (p != first)
        {
            cout << p->info << ' ';
            p = p->next;
        }
        p = last;
        while (p != first)
        {
            cout << p->info << ' ';
            p = p->prev;
        }
        p = last;
        while (p != end->next)
        {
            cout << p->info << ' ';
            p = p->next;
        }
    }
}

void task_3(DLIST& list)
{
    ptrNODE p = list.get_begin();
    ptrNODE start = p;
    p = p->next;
    while (p != start)
    {
        if (p->prev->info == p->next->info)
        {
            p = list.Delete(p);
        }
        else
        {
            p = p->next;
        }
        //cout << p->info << ' ';
    }
}
void task_4(DLIST& list)
{
    ptrNODE p = list.get_end();
    ptrNODE start = list.get_begin();

    
    while (p != start)
    {
        list.add_after(list.get_end(), p->info);
        p = p->prev;
    }
    list.add_after(list.get_end(), p->info);
}
void task_5(DLIST& list,int k)
{
    ptrNODE p = list.get_begin();
    int i = 0;
    while (p)
    {
        ++i;
        if (i == k)
        {
            std::cout << p->info << " ";
                p = list.Delete(p);
            i = 0;
        }
        else
        p = p->next;
    }
 
}
void task_6(DLIST& list, int k)
{
    ptrNODE p = list.get_begin();
    ptrNODE start = list.get_begin();
    int i = 1;
    bool flag = false;
    p = p->next;
    while (p != start && !flag)
    {
        ++i;
        if (p->info % 2 == 1)
        {
            flag = true;
            ptrNODE tmp = p->next->prev;
            p->prev->next = p->next;    
            p->next->prev = p->prev;
            if (i != k)
                if (i < k)
                    for (i; i < k; ++i) { p = p->next; }
                else for(i; i > k; --i) { p = p->prev; }
   
            p->prev->next = tmp;
            tmp->prev = p->prev;
            tmp->next = p;
            p->prev = tmp;
            break;
        }
        p = p->next;
    }
}
int main()
{
    std::ifstream file("data.txt");
    if (file)
    {
        DLIST list(file);
        list.print();
        //cout << list.to_string();
        //task_1(list);
        //task_2(list, 3);
        //task_3(list);
        //task_4(list);
        //task_5(list, 2);
        task_6(list, 2);
        std::cout << '\n';
        list.print();
        //cout << list.size;
    }
}