#pragma once
#include <vector>
#include "Server.h"
#include "Vehicul.h"

using namespace std;
class Repository
{
private:
	vector<Vehicul> data;
	Server server;


public:
	Repository() {};

	void AddToDB();
	void AddToDBByIndex(int index);

	void operator+(const Vehicul& veh);
	void operator-(const Vehicul& veh);

	friend ostream& operator<<(ostream& out, const Repository& repo);
};

