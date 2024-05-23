#include "Repository.h"

void Repository::AddToDB()
{
    for (int i = 0; i < data.size(); i++) {
        if (Masina* masina = dynamic_cast<Masina*>(&data[i])) {
            server.AddVehicle(*masina);
        }
        else if (Motocicleta* motor = dynamic_cast<Motocicleta*>(&data[i])) {
            server.AddVehicle(*motor);
        }
        else if (Camion* camion = dynamic_cast<Camion*>(&data[i])) {
            server.AddVehicle(*camion);
        }
    }
}

void Repository::AddToDBByIndex(int i)
{
    if (Masina* masina = dynamic_cast<Masina*>(&data[i])) {
        server.AddVehicle(*masina);
    }
    else if (Motocicleta* motor = dynamic_cast<Motocicleta*>(&data[i])) {
        server.AddVehicle(*motor);
    }
    else if (Camion* camion = dynamic_cast<Camion*>(&data[i])) {
        server.AddVehicle(*camion);
    }
}

void Repository::operator+(const Vehicul& veh)
{
	data.push_back(veh);
}

void Repository::operator-(const Vehicul& veh)
{
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (*it == veh) {
            data.erase(it);
            break;
        }
    }
}

ostream& operator<<(ostream& out, const Repository& repo)
{
    int index = 0;
    for (auto it = repo.data.begin(); it != repo.data.end(); ++it) {
        cout << "============================\n";
        cout << index++; out << *it;
        cout << "============================\n";
    }
    return out;
}
