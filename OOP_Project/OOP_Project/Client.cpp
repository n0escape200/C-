#include "Client.h"

Client::Client(const string& _Nume, const string& _Prenume, const string& _Username, const string& _Parola, int _Buget)
    : Persoana(_Nume, _Prenume,_Username, _Parola), Buget(_Buget) {}

Client::Client(const Client& other)
    : Persoana(other.Nume,other.Prenume, other.Username, other.Parola), Buget(other.Buget) {}

Client::Client():Persoana(),Buget(0)
{
}


Client& Client::operator=(const Client& other)
{
    if (this != &other)
    {
        Persoana::operator=(other);
        Buget = other.Buget;
        VehiculeAchizitionate = other.VehiculeAchizitionate;
        VehiculeDeVanzare = other.VehiculeDeVanzare;
    }
    return *this;
}

bool Client::operator==(const Client& other)
{
    if (!Persoana::operator==(other) || Buget != other.Buget) {
        return false;
    }
    return true;
}

bool Client::operator!=(const Client& other)
{
    if (!Persoana::operator==(other) || Buget != other.Buget) {
        return true;
    }
    return false;
}

istream& operator>>(istream& in, Client& client)
{
    cout << "Nume: ";
    in >> client.Nume;
    cout << "Prenume: ";
    in >> client.Prenume;
    cout << "Username: ";
    in >> client.Username;
    cout << "Parola: ";
    in >> client.Parola;
    cout << "Buget: ";
    in >> client.Buget;
    return in;
}

ostream& operator<<(ostream& out, const Client& client)
{
    out << "Nume: " << client.Nume << ", Prenume: " << client.Prenume << ", Username: " << client.Username << ", Buget: " << client.Buget;
    return out;
}
