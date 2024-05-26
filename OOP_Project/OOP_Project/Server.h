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
	void ShowAllVehicles(Client client);
	void ShowAllCars(Client client);
	void ShowAllTrucks(Client client);
	void ShowAllMotorcycles(Client client);

	void UpdateCarById(int i, Masina masina, Client client);
	void UpdateTruckById(int i, Camion camion, Client client);
	void UpdateMotorcycleById(int i, Motocicleta motocicleta, Client client);

	void DeleteCarById(int i, Client client);
	void DeleteTruckById(int i, Client client);
	void DeleteMotorcycleById(int i, Client client);

	int PurchaseCarById(int i, Client client);
	int PurchaseTruckById(int i, Client client);
	int PurchaseMotorcycleById(int i, Client client);

	void ShowAllClients();
	int GetInfoAboutUserByName(string fname, string lname);

	int GetCustomerByName(string fname, string lname);

	void DeleteCarByCustomerId(int idCar, int idCustomer);
	void DeleteTruckByCustomerId(int idCar, int idCustomer);
	void DeleteMotorcycleByCustomerId(int idCar, int idCustomer);
	void DeleteCustomerById(int id);
};

