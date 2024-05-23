#pragma once
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Masina.h"
#include "Camion.h"
#include "Motocicleta.h"
#include "Administrator.h"
#include "Client.h"
using namespace std;

class Server
{
public:
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;

	Server();

	void AddVehicle(Masina masina);
	void AddVehicle(Camion camion);
	void AddVehicle(Motocicleta motocicleta);

	int GetCustomerId(string username, string password);
	int GetAdminId(string username, string password);

	void ShowOwnedVehicles(Client client);
	void ShowVehicleTypeCar(Client client);
	void ShowVehicleTypeTruck(Client client);
	void ShowVehicleTypeMotorcycle(Client client);
	void ShowAllVehicles();

	void UpdateCarById(int i, Masina masina);
	void UpdateTruckById(int i, Camion camion);
	void UpdateMotorcycleById(int i, Motocicleta motocicleta);

	void DeleteCarById(int i);
	void DeleteTruckById(int i);
	void DeleteMotorcycleById(int i);
};

