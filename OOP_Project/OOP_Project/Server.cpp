#include "Server.h"


Server::Server()
{
	const string server = "tcp://127.0.0.1:3306";
	const string username = "root";
	const string password = "Canalulu1!";
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}

void Server::AddVehicle(Masina masina)
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("INSERT INTO vehicles.car (Brand, Model, An, KM, Pret, CapacitateCilindrica, Combustibil,OwnerId, Sasiu, Transmisie, NrUsi) VALUES(?,?,?,?,?,?,?,?,?,?,?);");
		pstmt->setString(1, masina.Getbrand());
		pstmt->setString(2, masina.GetModel());
		pstmt->setInt(3, masina.GetAn());
		pstmt->setDouble(4, masina.GetKM());
		pstmt->setDouble(5, masina.GetPret());
		pstmt->setDouble(6, masina.GetCapacitateCilindrica());
		pstmt->setString(7, masina.GetCombustibil());
		pstmt->setInt(8, masina.GetOwnerId());
		pstmt->setString(9, masina.GetSasiu());
		pstmt->setString(10, masina.GetTransmisie());
		pstmt->setInt(11, masina.GetNrUsi());
		pstmt->execute();
		
	}
	catch (const std::exception& e)
	{
		cout << e.what() <<"\n";
	}
}

void Server::AddVehicle(Camion camion)
{
	con->setSchema("vehicles");
	pstmt = con->prepareStatement("INSERT INTO vehicles.truck (Brand, Model, An, KM, Pret, CapacitateCilindrica, Combustibil,OwnerId, GreutateMaxima, LungimePlatforma) VALUES(?,?,?,?,?,?,?,?,?,?);");
	pstmt->setString(1, camion.Getbrand());
	pstmt->setString(2, camion.GetModel());
	pstmt->setInt(3, camion.GetAn());
	pstmt->setDouble(4, camion.GetKM());
	pstmt->setDouble(5, camion.GetPret());
	pstmt->setDouble(6, camion.GetCapacitateCilindrica());
	pstmt->setString(7, camion.GetCombustibil());
	pstmt->setInt(8, camion.GetOwnerId());
	pstmt->setInt(9, camion.GetGretutate());
	pstmt->setInt(10, camion.GetLungime());
	pstmt->execute();
	
}

void Server::AddVehicle(Motocicleta motocicleta)
{
	con->setSchema("vehicles");
	pstmt = con->prepareStatement("INSERT INTO vehicles.motorcycle (Brand, Model, An, KM, Pret, CapacitateCilindrica, Combustibil,OwnerId, TipMotor, Corp) VALUES(?,?,?,?,?,?,?,?,?,?);");
	pstmt->setString(1, motocicleta.Getbrand());
	pstmt->setString(2, motocicleta.GetModel());
	pstmt->setInt(3, motocicleta.GetAn());
	pstmt->setDouble(4, motocicleta.GetKM());
	pstmt->setDouble(5, motocicleta.GetPret());
	pstmt->setDouble(6, motocicleta.GetCapacitateCilindrica());
	pstmt->setString(7, motocicleta.GetCombustibil());
	pstmt->setInt(8, motocicleta.GetOwnerId());
	pstmt->setString(9, motocicleta.GetTipMotor());
	pstmt->setString(10, motocicleta.GetCorp());
	pstmt->execute();
	
}

int Server::GetCustomerId(string username, string password)
{
	try
	{
		con->setSchema("users");
		pstmt = con->prepareStatement("SELECT ID FROM users.customers WHERE username = ? AND password = ?");
		pstmt->setString(1, username);
		pstmt->setString(2, password);

		auto result = pstmt->executeQuery();
		if (result->next()) {
			return result->getInt("ID");
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	return -1;
}

int Server::GetAdminId(string username, string password)
{
	try
	{
		con->setSchema("users");
		pstmt = con->prepareStatement("SELECT ID FROM users.admins WHERE username = ? AND password = ?");
		pstmt->setString(1, username);
		pstmt->setString(2, password);

		auto result = pstmt->executeQuery();
		if (result->next()) {
			return result->getInt("ID");
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
	return -1;
}



void Server::ShowOwnedVehicles(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.car WHERE OwnerId = ?");
		pstmt->setInt(1, id);
		
		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Masini----------\n";
			while (data) {
				int vehId = result->getInt("VehicleID");
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				string sasiu = result->getString("Sasiu");
				string transmisie = result->getString("Transmisie");
				int usi = result->getInt("NrUsi");
				cout << "\nMasina ID:" << vehId << "\n";
				cout << Masina(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), sasiu, transmisie, usi) << "\n\n";
				data = result->next();
			}
			cout << "--------------------------\n";
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}

	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.truck WHERE OwnerId = ?");
		pstmt->setInt(1, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Camioane----------\n";
			while (data) {
				int vehId = result->getInt("VehicleID");
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				int greutate = result->getInt("GreutateMaxima");
				int lungime = result->getInt("LungimePlatforma");
				cout << "\nCamion ID:" << vehId << "\n";
				cout << Camion(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), greutate, lungime) << "\n\n";
				data = result->next();
			}
			cout << "----------------------------\n";
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}

	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.motorcycle WHERE OwnerId = ?");
		pstmt->setInt(1, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Motociclete----------\n";
			while (data) {
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				string motor = result->getString("TipMotor");
				string corp = result->getString("Corp");
				cout << Motocicleta(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), motor, corp) << "\n";
				data = result->next();
			}
			cout << "-------------------------------\n";
		}
		
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Server::ShowVehicleTypeCar(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.car WHERE OwnerId = ?");
		pstmt->setInt(1, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Masini----------\n";
			while (data) {
				int vehId = result->getInt("VehicleID");
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				string sasiu = result->getString("Sasiu");
				string transmisie = result->getString("Transmisie");
				int usi = result->getInt("NrUsi");
				cout << "\nMasina ID:" << vehId << "\n";
				cout << Masina(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), sasiu, transmisie, usi) << "\n\n";
				data = result->next();
			}
			cout << "--------------------------\n";
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

void Server::ShowVehicleTypeTruck(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.truck WHERE OwnerId = ?");
		pstmt->setInt(1, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Camioane----------\n";
			while (data) {
				int vehId = result->getInt("VehicleID");
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				int greutate = result->getInt("GreutateMaxima");
				int lungime = result->getInt("LungimePlatforma");
				cout << "\nCamion ID:" << vehId << "\n";
				cout << Camion(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), greutate, lungime) << "\n\n";
				data = result->next();
			}
			cout << "----------------------------\n";
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Server::ShowVehicleTypeMotorcycle(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.motorcycle WHERE OwnerId = ?");
		pstmt->setInt(1, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Motociclete----------\n";
			while (data) {
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				string motor = result->getString("TipMotor");
				string corp = result->getString("Corp");
				cout << Motocicleta(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), motor, corp) << "\n";
				data = result->next();
			}
			cout << "-------------------------------\n";
		}

	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Server::ShowAllVehicles()
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.car");
		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Masini----------\n";
			while (data) {
				int vehId = result->getInt("VehicleID");
				int id = result->getInt("OwnerId");
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				string sasiu = result->getString("Sasiu");
				string transmisie = result->getString("Transmisie");
				int usi = result->getInt("NrUsi");
				cout << "\Masina ID:" << vehId << "\n";
				cout << Masina(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), sasiu, transmisie, usi) << "\n\n";
				data = result->next();
			}
			cout << "----------------------------\n";
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}

	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.motorcycle");
		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Motociclete----------\n";
			while (data) {
				int vehId = result->getInt("VehicleID");
				int id = result->getInt("OwnerId");
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				string motor = result->getString("TipMotor");
				string corp = result->getString("Corp");
				cout << "\Motocicleta ID:" << vehId << "\n";
				cout << Motocicleta(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), motor, corp) << "\n\n";
				data = result->next();
			}
			cout << "-------------------------------\n";
		}

	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}

	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.truck");
		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			cout << "----------Camioane----------\n";
			while (data) {
				int vehId = result->getInt("VehicleID");
				int id = result->getInt("OwnerId");
				string brand = result->getString("Brand");
				string model = result->getString("Model");
				int an = result->getInt("An");
				int km = result->getInt("KM");
				int pret = result->getInt("Pret");
				int capCil = result->getInt("CapacitateCilindrica");
				string combustibil = result->getString("Combustibil");
				int greutate = result->getInt("GreutateMaxima");
				int lungime = result->getInt("LungimePlatforma");
				cout << "\nCamion ID:" << vehId << "\n";
				cout << Camion(Vehicul(brand, model, an, km, pret, capCil, combustibil, id), greutate, lungime) << "\n\n";
				data = result->next();
			}
			cout << "----------------------------\n";
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


void Server::UpdateCarById(int i, Masina masina)
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("UPDATE vehicles.car SET Brand = ?, Model = ?, An = ?, KM = ?, Pret = ?, CapacitateCilindrica = ?, Combustibil = ?, Sasiu = ?, Transmisie = ?, NrUsi = ? WHERE VehicleID = ?");
		pstmt->setString(1, masina.Getbrand());
		pstmt->setString(2, masina.GetModel());
		pstmt->setInt(3, masina.GetAn());
		pstmt->setInt(4, masina.GetKM());
		pstmt->setInt(5, masina.GetPret());
		pstmt->setInt(6, masina.GetCapacitateCilindrica());
		pstmt->setString(7, masina.GetCombustibil());
		pstmt->setString(8, masina.GetSasiu());
		pstmt->setString(9, masina.GetTransmisie());
		pstmt->setInt(10, masina.GetNrUsi());
		pstmt->setInt(11, i);

		auto result = pstmt->executeUpdate();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Server::UpdateTruckById(int i, Camion camion)
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("UPDATE vehicles.truck SET Brand = ?, Model = ?, An = ?, KM = ?, Pret = ?, CapacitateCilindrica = ?, Combustibil = ?, GreutateMaxima = ?, LungimePlatforma = ? WHERE VehicleID = ?");
		pstmt->setString(1, camion.Getbrand());
		pstmt->setString(2, camion.GetModel());
		pstmt->setInt(3, camion.GetAn());
		pstmt->setInt(4, camion.GetKM());
		pstmt->setInt(5, camion.GetPret());
		pstmt->setInt(6, camion.GetCapacitateCilindrica());
		pstmt->setString(7, camion.GetCombustibil());
		pstmt->setInt(8, camion.GetGretutate());
		pstmt->setInt(9, camion.GetLungime());
		pstmt->setInt(10, i);

		auto result = pstmt->executeUpdate();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Server::UpdateMotorcycleById(int i, Motocicleta motocicleta)
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("UPDATE vehicles.truck SET Brand = ?, Model = ?, An = ?, KM = ?, Pret = ?, CapacitateCilindrica = ?, Combustibil = ?, TipMotor = ?, Corp = ? WHERE VehicleID = ?");
		pstmt->setString(1, motocicleta.Getbrand());
		pstmt->setString(2, motocicleta.GetModel());
		pstmt->setInt(3, motocicleta.GetAn());
		pstmt->setInt(4, motocicleta.GetKM());
		pstmt->setInt(5, motocicleta.GetPret());
		pstmt->setInt(6, motocicleta.GetCapacitateCilindrica());
		pstmt->setString(7, motocicleta.GetCombustibil());
		pstmt->setString(8, motocicleta.GetTipMotor());
		pstmt->setString(9, motocicleta.GetCorp());
		pstmt->setInt(10, i);

		auto result = pstmt->executeUpdate();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}



void Server::DeleteCarById(int i)
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("DELETE FROM vehicles.car WHERE VehicleId = ?");
		pstmt->setInt(1, i);
		pstmt->execute();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Server::DeleteTruckById(int i)
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("DELETE FROM vehicles.truck WHERE VehicleId = ?");
		pstmt->setInt(1, i);
		pstmt->execute();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Server::DeleteMotorcycleById(int i)
{
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("DELETE FROM vehicles.motorcycle WHERE VehicleId = ?");
		pstmt->setInt(1, i);
		pstmt->execute();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

