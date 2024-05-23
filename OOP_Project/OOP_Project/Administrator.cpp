#include "Administrator.h"


Administrator::Administrator() :Persoana(), Cod(0000) {}

Administrator::Administrator(const string& _Nume, const string& _Prenume, const string& _Username, const string& _Parola, int _Cod):Persoana(_Nume,_Prenume,_Username,_Parola),Cod(_Cod){}

Administrator::Administrator(const Administrator& other) :Persoana(other.Nume, other.Prenume, other.Username, other.Parola), Cod(other.Cod) {}


Administrator& Administrator::operator=(const Administrator& admin)
{
	if (this != &admin) {
		Persoana::operator=(admin);
		this->Cod = admin.Cod;
	}
	return *this;
}

bool Administrator::operator==(const Administrator& other)
{
	if (Persoana::operator!=(other) || Cod != other.Cod) {
		return false;
	}
	return true;
}

bool Administrator::operator!=(const Administrator& other)
{
	if (Persoana::operator!=(other) || Cod != other.Cod) {
		return true;
	}
	return false;
}

istream& operator>>(istream& in, Administrator& admin)
{
	cout << "Introduceti numele: ";
	in >> admin.Nume;
	cout << "Introduceti prenumele: ";
	in >> admin.Prenume;
	cout << "Introduceti username-ul: ";
	in >> admin.Username;
	cout << "Introduceti parola: ";
	in >> admin.Parola;
	cout << "Codul administratorului: ";
	in >> admin.Cod;
	return in;
}

ostream& operator<<(ostream& out, Administrator& admin)
{
	out << "Nume: " << admin.Nume << ", Prenume: " << admin.Prenume << ", Username: " << admin.Username;
	return out;
}
