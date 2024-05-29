#include "Persoana.h"

Persoana::Persoana(string _Nume, string _Prenume, string _Username, string _Parola):
	Nume(_Nume), Prenume(_Prenume), Username(_Username), Parola(_Parola) {}

Persoana::Persoana()
	: Nume("undefined"), Prenume("undefined"), Username("undefined"), Parola("parola") {}


ostream& operator<<(ostream& out, const Persoana& pers)
{
	out << "Nume: " << pers.Nume << ", Prenume: " << pers.Prenume << ", Username: " << pers.Username;
	return out;
}

istream& operator>>(istream& in, Persoana& pers)
{
	cout << "Introduceti numele: ";
	in >> pers.Nume;
	cout << "Introduceti prenumele: ";
	in >> pers.Prenume;
	cout << "Introduceti username-ul: ";
	in >> pers.Username;
	cout << "Introduceti parola: ";
	in >> pers.Parola;
	return in;
}

Persoana& Persoana::operator=(const Persoana& other)
{
	if (this != &other)
	{
		Nume = other.Nume;
		Prenume = other.Prenume;
		Username = other.Username;
		Parola = other.Parola;
	}
	return *this;
}

bool Persoana::operator==(const Persoana& other)
{
	if (Nume != other.Nume || Prenume != other.Prenume || Username != other.Username || Parola != other.Parola) {
		return false;
	}
	return  true;
}

bool Persoana::operator!=(const Persoana& other)
{
	if (Nume != other.Nume || Prenume != other.Prenume || Username != other.Username || Parola != other.Parola) {
		return true;
	}
	return false;
}
