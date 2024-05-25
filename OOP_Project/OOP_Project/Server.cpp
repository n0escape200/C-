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

/// <summary>
/// Functie pentru adaugarea unui vehicul de tip 'Masinia' in baza de date
/// </summary>
/// <param name="masina"></param>
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


/// <summary>
/// Functie pentru adaugarea unui vehicul de tip 'Camion' in baza de date
/// </summary>
/// <param name="camion"></param>
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


/// <summary>
/// Functie pentru adaugarea unui vehicul de tip 'Motocicleta' in baza de date
/// </summary>
/// <param name="motocicleta"></param>
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


/// <summary>
/// Functie care cauta un id in tabela 'Customers' in functie de 'username' si 'parola'
/// </summary>
/// <param name="username"></param>
/// <param name="password"></param>
/// <returns></returns>
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


/// <summary>
/// Functie care cauta un id in tabela 'Admins' in functie de 'username' si 'parola'
/// </summary>
/// <param name="username"></param>
/// <param name="password"></param>
/// <returns></returns>
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele detinute de 'client'
/// </summary>
/// <param name="client"></param>
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele de tip 'Masina', detinute de 'client'
/// </summary>
/// <param name="client"></param>
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele de tip 'Camion', detinute de 'client'
/// </summary>
/// <param name="client"></param>
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele de tip 'Motocicleta', detinute de 'client'
/// </summary>
/// <param name="client"></param>
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele care NU sunt detinute de 'client'
/// </summary>
/// <param name="client"></param>
void Server::ShowAllVehicles(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.car WHERE OwnerId != ?");
		pstmt->setInt(1,id);
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
		pstmt = con->prepareStatement("SELECT * FROM vehicles.motorcycle WHERE OwnerId != ?");
		pstmt->setInt(1, id);
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
		pstmt = con->prepareStatement("SELECT * FROM vehicles.truck WHERE OwnerId != ?");
		pstmt->setInt(1, id);
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele de tip 'Masina', care NU sunt detinute de 'client'
/// </summary>
/// <param name="client"></param>
void Server::ShowAllCars(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.car WHERE OwnerId != ?");
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele de tip 'Camion', care NU sunt detinute de 'client'
/// </summary>
/// <param name="client"></param>
void Server::ShowAllTrucks(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.truck WHERE OwnerId != ?");
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


/// <summary>
/// Functie care cauta si afiseaza pe ecran toate vehiculele de tip 'Motocicleta', care NU sunt detinute de 'client'
/// </summary>
/// <param name="client"></param>
void Server::ShowAllMotorcycles(Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.motorcycle WHERE OwnerId != ?");
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


/// <summary>
/// Functie care cauta si schimba un vehicul de tip 'Masina', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul este detinuta de catre 'client'
/// </summary>
/// <param name="client"></param>
void Server::UpdateCarById(int i, Masina masina, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("UPDATE vehicles.car SET Brand = ?, Model = ?, An = ?, KM = ?, Pret = ?, CapacitateCilindrica = ?, Combustibil = ?, Sasiu = ?, Transmisie = ?, NrUsi = ? WHERE VehicleID = ? AND OwnerId = ?");
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
		pstmt->setInt(12, id);

		auto result = pstmt->executeUpdate();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


/// <summary>
/// Functie care cauta si schimba un vehicul de tip 'Camion', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul este detinuta de catre 'client'
/// </summary>
/// <param name="client"></param>
void Server::UpdateTruckById(int i, Camion camion, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("UPDATE vehicles.truck SET Brand = ?, Model = ?, An = ?, KM = ?, Pret = ?, CapacitateCilindrica = ?, Combustibil = ?, GreutateMaxima = ?, LungimePlatforma = ? WHERE VehicleID = ? AND OwnerId = ?");
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
		pstmt->setInt(11, id);

		auto result = pstmt->executeUpdate();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


/// <summary>
/// Functie care cauta si schimba un vehicul de tip 'Motocicleta', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul este detinuta de catre 'client'
/// </summary>
/// <param name="client"></param>
void Server::UpdateMotorcycleById(int i, Motocicleta motocicleta, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("UPDATE vehicles.truck SET Brand = ?, Model = ?, An = ?, KM = ?, Pret = ?, CapacitateCilindrica = ?, Combustibil = ?, TipMotor = ?, Corp = ? WHERE VehicleID = ? AND OwnerId = ?");
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
		pstmt->setInt(11, id);

		auto result = pstmt->executeUpdate();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


/// <summary>
/// Functie care cauta si sterge un vehicul de tip 'Masina', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul este detinuta de catre 'client'
/// </summary>
/// <param name="client"></param>
void Server::DeleteCarById(int i, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("DELETE FROM vehicles.car WHERE VehicleId = ? AND OwnerId = ? ");
		pstmt->setInt(1, i);
		pstmt->setInt(2, id);
		pstmt->execute();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


/// <summary>
/// Functie care cauta si sterge un vehicul de tip 'Camion', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul este detinuta de catre 'client'
/// </summary>
/// <param name="client"></param>
void Server::DeleteTruckById(int i, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("DELETE FROM vehicles.truck WHERE VehicleId = ? AND OwnerId = ?");
		pstmt->setInt(1, i);
		pstmt->setInt(2, id);
		pstmt->execute();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


/// <summary>
/// Functie care cauta si sterge un vehicul de tip 'Motocicleta', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul este detinuta de catre 'client'
/// </summary>
/// <param name="client"></param>
void Server::DeleteMotorcycleById(int i, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());
	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("DELETE FROM vehicles.motorcycle WHERE VehicleId = ? AND OwnerId = ?");
		pstmt->setInt(1, i);
		pstmt->setInt(2, id);
		pstmt->execute();
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


/// <summary>
/// Functie care cauta si cumpara un vehicul de tip 'Masina', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul NU este detinuta de catre 'client'.
/// Functia returneaza un buget modificat al obiectului 'client', daca vehiculul poate fi achizitionat. In caz contrat va returna bugetul actual fara modificari.
/// </summary>
/// <param name="client"></param>
int Server::PurchaseCarById(int i, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());

	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.car WHERE VehicleID = ? AND OwnerId != ?");
		pstmt->setInt(1, i);
		pstmt->setInt(2, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			int vehPrice = result->getInt("Pret");

			if (vehPrice > client.GetBuget()) {
				cout << "Fonduri insuficiente\n";
			}
			else {
				pstmt = con->prepareStatement("UPDATE vehicles.car SET OwnerId = ? WHERE VehicleID = ?");
				pstmt->setInt(1, id);
				pstmt->setInt(2, i);
				pstmt->execute();

				con->setSchema("users");
				int updatedBuget = client.GetBuget() - vehPrice;

				pstmt = con->prepareStatement("UPDATE users.customers SET Buget = ? WHERE ID = ?");
				pstmt->setInt(1, updatedBuget);
				pstmt->setInt(2, id);
				pstmt->execute();
				cout << "Masina cumparata\n";
				return updatedBuget;
			}
		}
		else {
			cout << "Entry error\n";
		}
		return client.GetBuget();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}


/// <summary>
/// Functie care cauta si cumpara un vehicul de tip 'Camion', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul NU este detinuta de catre 'client'.
/// Functia returneaza un buget modificat al obiectului 'client', daca vehiculul poate fi achizitionat. In caz contrat va returna bugetul actual fara modificari.
/// </summary>
/// <param name="client"></param>
int Server::PurchaseTruckById(int i, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());

	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.truck WHERE VehicleID = ? AND OwnerId != ?");
		pstmt->setInt(1, i);
		pstmt->setInt(2, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			int vehPrice = result->getInt("Pret");

			if (vehPrice > client.GetBuget()) {
				cout << "Fonduri insuficiente";
			}
			else {
				pstmt = con->prepareStatement("UPDATE vehicles.truck SET OwnerId = ? WHERE VehicleID = ?");
				pstmt->setInt(1, id);
				pstmt->setInt(2, i);
				pstmt->execute();

				con->setSchema("users");
				int updatedBuget = client.GetBuget() - vehPrice;
				pstmt = con->prepareStatement("UPDATE users.customers SET Buget = ? WHERE ID = ?");
				pstmt->setInt(1, updatedBuget);
				pstmt->setInt(2, id);
				pstmt->execute();
				cout << "Camion cumparat";
				return updatedBuget;
			}
		}
		else {
			cout << "Entry error\n";
		}
		return client.GetBuget();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}


/// <summary>
/// Functie care cauta si cumpara un vehicul de tip 'Motocicleta', dupa un id 'i'.
/// Totodata, se verifica daca vehiculul NU este detinuta de catre 'client'.
/// Functia returneaza un buget modificat al obiectului 'client', daca vehiculul poate fi achizitionat. In caz contrat va returna bugetul actual fara modificari.
/// </summary>
/// <param name="client"></param>
int Server::PurchaseMotorcycleById(int i, Client client)
{
	int id = GetCustomerId(client.GetUsername(), client.GetParola());

	try
	{
		con->setSchema("vehicles");
		pstmt = con->prepareStatement("SELECT * FROM vehicles.motorcycle WHERE VehicleID = ? AND OwnerId != ?");
		pstmt->setInt(1, i);
		pstmt->setInt(2, id);

		auto result = pstmt->executeQuery();
		auto data = result->next();
		if (data) {
			int vehPrice = result->getInt("Pret");

			if (vehPrice > client.GetBuget()) {
				cout << "Fonduri insuficiente";
			}
			else {
				pstmt = con->prepareStatement("UPDATE vehicles.motorcycle SET OwnerId = ? WHERE VehicleID = ?");
				pstmt->setInt(1, id);
				pstmt->setInt(2, i);
				pstmt->execute();

				con->setSchema("users");
				int updatedBuget = client.GetBuget() - vehPrice;
				pstmt = con->prepareStatement("UPDATE users.customers SET Buget = ? WHERE ID = ?");
				pstmt->setInt(1, updatedBuget);
				pstmt->setInt(2, id);
				pstmt->execute();
				cout << "Motocicleta cumparata";
				return updatedBuget;
			}
		}
		else {
			cout << "Entry error\n";
		}
		return client.GetBuget();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}
