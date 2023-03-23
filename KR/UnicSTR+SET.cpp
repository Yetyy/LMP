#include<iostream>
#include<string>
#include <fstream>
#include<set>
#include<sstream>
using namespace std;

void task(fstream& file)
{
	set<string> S;
	stringstream sstr;
	string str;
	string comstring = "";
	string str1;
	while (getline(file, str))
	{
		comstring += " " + str;
		sstr << str;
		while (sstr >> str1)
			S.insert(str1);

		//S.clear();
		sstr.str("");
		sstr.clear();
	}
	for (auto x : S)
	{
		if (comstring.find(x, comstring.find(x) + 1) == -1)
			cout << x << " ";

	}
	cout << "\n";
}

void main()
{
	fstream file("test.txt");
	task(file);
}