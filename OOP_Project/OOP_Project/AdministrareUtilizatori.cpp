#include "AdministrareUtilizatori.h"
#include "Server.h"
Server server;


AdministrareUtilizatori::AdministrareUtilizatori() {}

//
//vector<string> AdministrareUtilizatori::Split(string line)
//{
//	string buffer = "";
//	vector<string> list;
//	if (line.length() > 0) {
//		for (int i = 0; i < line.length(); i++)
//		{
//			if (line[i] == '_') {
//				list.push_back(buffer);
//				buffer = "";
//			}
//			else {
//				buffer += line[i];
//			}
//		}
//	}
//	return list;
//}

void AdministrareUtilizatori::Register(Administrator admin)
{
	server.con->setSchema("users");
	server.pstmt = server.con->prepareStatement("INSERT INTO users.admins (FirstName, LastName, Username, Password, Code) VALUES(?,?,?,?,?);");
	server.pstmt->setString(1, admin.GetNume());
	server.pstmt->setString(2, admin.GetPrenume());
	server.pstmt->setString(3, admin.GetUsername());
	server.pstmt->setString(4, admin.GetParola());
	server.pstmt->setInt(5, admin.GetCod());
	server.pstmt->execute();
	cout << "Admin inregistrat\n";
}

void AdministrareUtilizatori::Register(Client client)
{
	server.con->setSchema("users");
	server.pstmt = server.con->prepareStatement("INSERT INTO users.customers (FirstName, LastName, Username, Password, Buget) VALUES(?,?,?,?,?);");
	server.pstmt->setString(1, client.GetNume());
	server.pstmt->setString(2, client.GetPrenume());
	server.pstmt->setString(3, client.GetUsername());
	server.pstmt->setString(4, client.GetParola());
	server.pstmt->setInt(5, client.GetBuget());
	server.pstmt->execute();
	cout << "Client inregistrat\n";
}

Administrator AdministrareUtilizatori::Login(string username, string password, int cod)
{
	try {
		server.con->setSchema("users");
		server.pstmt = server.con->prepareStatement("SELECT * FROM users.admins WHERE username = ? AND password = ? AND code = ?");
		server.pstmt->setString(1, username);
		server.pstmt->setString(2, password);
		server.pstmt->setInt(3, cod);

		Administrator admin;

		auto result = server.pstmt->executeQuery();
		if (result->next()) {
			admin = Administrator(
				result->getString("FirstName"),
				result->getString("LastName"),
				result->getString("Username"),
				result->getString("Password"),
				result->getInt("Code")
			);
			cout << "Admin gasit\n";
			return admin;
		}
		else {
			cout << "Admin nu exista\n";
		}
	}
	catch (const std::exception& e) {
		cout << "Error: " << e.what() << endl;
	}
	return Administrator();
}

Client AdministrareUtilizatori::Login(string username, string password)
{
	
	try
	{
		server.con->setSchema("users");
		server.pstmt = server.con->prepareStatement("SELECT * FROM users.customers WHERE username = ? AND password = ?");
		server.pstmt->setString(1, username);
		server.pstmt->setString(2, password);
		Client client;
		auto result = server.pstmt->executeQuery();
		if (result->next()) {
			cout << "Client gasit\n";
			client.SetNume(result->getString("FirstName"));
			client.SetPrenume(result->getString("LastName"));
			client.SetUsername(result->getString("Username"));
			client.SetParola(result->getString("Password"));
			client.SetBuget(result->getInt("Buget"));
			return client;
		}
		else {
			cout << "Clientul nu exista\n";
		}
	}
	catch (const std::exception& e)
	{
		cout << "Error: " << e.what() << endl;
	}
	return Client();
}


