#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Administrator.h"
#include "Client.h"
using namespace std;

class AdministrareUtilizatori
{
public:
	AdministrareUtilizatori();
	
	void Register(Administrator admin);
	void Register(Client client);

	Administrator Login(string username, string password, int cod);
	Client Login(string username, string password);
};

