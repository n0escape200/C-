#include <iostream>
#include "Persoana.h"
#include "Client.h"
#include "Administrator.h"
#include "AdministrareUtilizatori.h"
#include "Masina.h"
#include "Camion.h"
#include "Motocicleta.h"
#include "Server.h"

using namespace std;

AdministrareUtilizatori administrare;

void LoginMenu() {
	cout << "1)Login\n";
	cout << "2)Register admin\n";
	cout << "3)Register client\n";
}

void CustomernMenu() {
	cout << "\n------------MENU------------\n";
	cout << "1)Add a vehicle\n";
	cout << "2)Show owned listings\n";
	cout << "3)Show all listings\n";
	cout << "4)Update a vehicle\n";
	cout << "5)Delete a vehicle\n";
}

int main() {
	int op = 0;
	int auth = 0;

	Administrator admin;
	Client client;
	Server server;
	int clientId;

	do
	{
		LoginMenu();
		cout << ">>>"; cin >> op;
		switch (op) {
		case 1: {
			try
			{
				string username, parola;
				int cod;
				cout << "Username:"; cin >> username;
				cout << "Parola:"; cin >> parola;
				cout << "Cod (optional):"; cin >> cod;
				if (cin.fail()) {
					throw std::invalid_argument("Invalid input for Cod. Please enter a valid number.");
				}

				if (cod == NULL) {
					client = administrare.Login(username, parola);
					if (client != Client()) {
						auth = 1;
						clientId = server.GetCustomerId(username, parola);
					}
				}
				else {
					admin = administrare.Login(username, parola, cod);
					if (admin != Administrator()) {
						auth = 2;
					}
				}
			}
			catch (const std::exception& error)
			{
				cout << error.what() << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
			break;
		case 2: {
			try
			{
				Administrator admin;
				cin >> admin;
				administrare.Register(admin);
			}
			catch (const std::exception& error)
			{
				cout << error.what() << endl;
			}
		}
			break;
		case 3: {
			try
			{
				Client client;
				cin >> client;
				administrare.Register(client);
			}
			catch (const std::exception& error)
			{
				cout << error.what() << endl;
			}
		}
			  break;
		default:
			break;
		}

		cout << "Press enter...\n";
		cin.get();
		cin.get();
		system("CLS");
	} while (auth == 0);

	if (auth == 1) {
		op = 0;
		
		do
		{
			cout << "ID:" << server.GetCustomerId(client.GetUsername(),client.GetParola()) << "\nNume:" << client.GetNume() << "\nPrenume:" << client.GetPrenume() << "\nBuget:" << client.GetBuget() << "\n";
			CustomernMenu();
			cout << ">>";
			cin >> op;
			switch (op)
			{
			case 1: {
				int veh;
				cout << "1)Masina\n2)Camion\n3)Motocicleta\n";
				cin >> veh;
				switch (veh)
				{
				case 1: {
					Masina masina;
					cin >> masina;
					masina.SetOwnerId(clientId);
					server.AddVehicle(masina);
				}
					  break;
				case 2: {
					Camion camion;
					cin >> camion;
					camion.SetOwnerId(clientId);
					server.AddVehicle(camion);
				}
					  break;
				case 3: {
					Motocicleta motocicleta;
					cin >> motocicleta;
					motocicleta.SetOwnerId(clientId);
					server.AddVehicle(motocicleta);
				}
					  break;
				default:
					break;
				}
				cout << "Press enter...\n";
				cin.get();
				cin.get();
				system("CLS");
			}
				  break;
			case 2: {
				server.ShowOwnedVehicles(client);
				cout << "Press enter...\n";
				cin.get();
				cin.get();
				system("CLS");
			}
				  break;
			case 3: {
				server.ShowAllVehicles();
				cout << "Press enter...\n";
				cin.get();
				cin.get();
				system("CLS");
			}
				  break;
			case 4: {
				int i;
				cout << "1)Masina\n2)Camion\n3)Motocicleta\n";
				cout << "Type:";
				cin >> i;
				switch (i)
				{
				case 1: {
					server.ShowVehicleTypeCar(client);
					int j;
					cout << "Id-ul masinii care va fi schimbata:";
					cin >> j;
					Masina masina;
					cin >> masina;
					server.UpdateCarById(j, masina);
				}
					  break;
				case 2: {
					server.ShowVehicleTypeTruck(client);
					int j;
					cout << "Id-ul camionului care va fi schimbat:";
					cin >> j;
					Camion camion;
					cin >> camion;
					server.UpdateTruckById(j, camion);
				}
					  break;
				case 3: {
					server.ShowVehicleTypeMotorcycle(client);
					int j;
					cout << "Id-ul motocicletei care va fi schimbata:";
					cin >> j;
					Motocicleta motocicleta;
					cin >> motocicleta;
					server.UpdateMotorcycleById(j, motocicleta);
				}
					  break;
				default:
					break;
				}
				cout << "Press enter...\n";
				cin.get();
				cin.get();
				system("CLS");
			}
				  break;
			case 5: {
				int i;
				cout << "1)Masina\n2)Camion\n3)Motocicleta\n";
				cout << "Type:";
				cin >> i;
				switch (i){
				case 1: {
					server.ShowVehicleTypeCar(client);
					int j;
					cout << "Id-ul masinii care va fi sterse:";
					cin >> j;
					server.DeleteCarById(j);
				}
					  break;
				case 2: {
					server.ShowVehicleTypeTruck(client);
					int j;
					cout << "Id-ul camionului care va fi sters:";
					cin >> j;
					server.DeleteTruckById(j);
				}
					  break;
				case 3: {
					server.ShowVehicleTypeMotorcycle(client);
					int j;
					cout << "Id-ul motocicletei care va fi stearsa:";
					cin >> j;
					server.DeleteMotorcycleById(j);
				}
					  break;
				default:
					break;
				}
				cout << "Press enter...\n";
				cin.get();
				cin.get();
				system("CLS");
			}
				  break;
			default:
				cout << "\n!!!UNKNOWN!!!\n";
				cin.get();
				cin.get();
				system("CLS");
				break;
			}
		} while (op != 0);
	}
	if (auth == 2) {

		do
		{

		} while (true);

		cout << "Press enter...\n";
		char c;
		cin.get();
		cin.get(c);
		system("CLS");
	}
	return 0;
}