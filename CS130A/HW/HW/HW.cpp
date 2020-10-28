#include<vector>
using namespace std;
class Originator//The originator class creates a memo that records its internal state at the current time
{
private:
	int m;
public:
	Originator() : m(100) {}
	Memento Save()
	{
		Memento memento(m);
		return memento;
	}
	void Load(Memento memento)
	{
		m = memento.m;
	}
};

class Memento//This Memento class stores the internal state of the originator object
{
public:
	int m;
public:
	Memento(int v1) :
		m(v1) {}
	Memento& operator=(const Memento& memento)
	{
		m = memento.m;
		return *this;
	}
};

class Caretake//Responsible for keeping memos; However, the contents of the memo cannot be manipulated or reviewed.
{
public:
	Caretake() {}
	void Save(Memento menento) { mMemento.push_back(menento); }
	Memento Load(int state) { return mMemento[state]; }
private:
	vector<Memento> mMemento;
};