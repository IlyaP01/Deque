#include "Deque/deque.hpp"
#include <iostream>

int main() {
	// some tests

	using namespace std;
	deque<string> a;
	deque<string> b = move(a);
	deque<string> c = b;
	b = c;
	deque<string> d;

	d.push_back("1");
	d.push_back("2");
	d.push_back("3");
	d.push_back("4");
	d.push_back("5");
	d.push_front("0");
	d.push_front("-1");

	cout << d;

	cout << endl;
	for (auto& str : d) {
		cout << str << " ";
	}
	cout << endl;
	deque<string>::iterator it = d.begin();
	cout << *it++;
	cout << *it;
	++it;
	cout << *it--;
	cout << *it;
	--it;
	cout << *it;

	cout << endl;
	auto it2 = d.end();

	cout << (it < it2);
	cout << (it <= it2);
	cout << (it > it2);
	cout << (it >= it2);
	cout << (it == it2);
	cout << (it == it);

	cout << it->at(0);

	cout << endl;

	b = std::move(d);
	cout << b[0];
	b[0] = "ab";
	cout << endl;
	std::cout << b[0] << b[1] << b[2] << b[3] << b[4] << b[5] << b[6];
	cout << endl;
	b.at(2);
	try {
		b.at(5);
	}
	catch (std::out_of_range e){
		std::cout << e.what();
	}

	b = std::move(b);
	std::cout << b.back();

	string str = "rgssgvxcds";
	b.push_back(str);
	cout << str << endl;
	b.push_back(std::move(str));
	cout << str << endl; // empty string, so move push works right
	std::cout << b.back();

	cout << endl;
	b.emplace_front("first");
	b.emplace_front("first");
	b.emplace_front("first");
	b.emplace_front("first");
	b.emplace_front("first");
	b.emplace_front("first");
	b.emplace_front("first");
	b.emplace_front("first");
	b.emplace_front("first");
	cout << b;

	auto cit = --b.cend();
	cout << *cit;

	b.clear();
	b.push_front("ss");
	cout << b.front();

	deque<string> g;
	cout << endl;
	g.push_back("aaa");
	g.push_back("bbb");
	g.pop_back();
	cout << g << endl;
	g.pop_back();
	cout << g << endl;
	g.push_back("aaa");
	g.push_back("bbb");
	g.push_back("ccc");
	g.push_back("ddd");
	g.push_back("eee");
	g.pop_front();
	g.pop_front();
	g.pop_front();
	g.pop_front();
	cout << g << endl;
	g.pop_back();
	cout << g << endl;


	cout << endl << endl;

	deque<string> r(5, "test");
	cout << r;
	cout << endl << r.size() << endl;

	auto itb = r.begin();
	auto ite = r.end();
	cout << ite - itb << *(ite - 4);

	return 0;
}