#pragma once
#include "Persoana.h"
class Administrator:public Persoana
{
private:
	int Cod;
public:
	Administrator();
	Administrator(const string& _Nume, const string& _Prenume, const string& _Username, const string& _Parola, int _Cod);
	Administrator(const Administrator& other);

	int GetCod() { return Cod; }
	void SetCod(int _cod) { Cod = _cod; }

	Administrator& operator= (const Administrator& admin);
	bool operator==(const Administrator& other);
	bool operator!=(const Administrator& other);

	friend istream& operator>>(istream& is, Administrator& admin);
	friend ostream& operator<<(ostream& os, Administrator& admin);

};

