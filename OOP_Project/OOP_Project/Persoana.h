#pragma once
#include <iostream>
#include <string>
using namespace std;

class Persoana
{
protected:
	string Nume;
	string Prenume;
	string Username;
	string Parola;

public:

	Persoana(string _Nume, string _Prenume, string _Username, string _Parola);

	Persoana(const Persoana& other) :Nume(other.Nume), Prenume(other.Prenume), Username(other.Username), Parola(other.Parola) {}

	Persoana();

	//Setters
	void SetNume(string _Nume) { Nume = _Nume; }

	void SetPrenume(string _Prenume) { Prenume = _Prenume; }

	void SetUsername(string _Username) { Username = _Username; }

	void SetParola(string _Parola) { Parola = _Parola; }

	//Getters

	const string GetNume() { return Nume; }

	const string GetPrenume() { return Prenume; }

	const string GetUsername() { return Username; }

	const string GetParola() { return Parola; }

	Persoana& operator=(const Persoana& other);
	bool operator==(const Persoana& other);
	bool operator!=(const Persoana& other);

	friend ostream& operator<<(ostream& out, const Persoana& pers);
	friend istream& operator>>(istream& in, Persoana& pers);


};
