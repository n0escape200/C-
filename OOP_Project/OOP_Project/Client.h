#pragma once
#include "Persoana.h"
#include "Vehicul.h"
#include <vector>
using namespace std;

class Client : public Persoana
{
private:
    int Buget;
public:
    //Constructori
    Client(const string& _Nume, const string& _Prenume, const string& _Username, const string& _Parola, int _Buget);
    Client(const Client& other);
    Client();

    int GetBuget() { return Buget; }
    void SetBuget(int buget) { Buget = buget; }

    //Supradefinirea operatorilor
    Client& operator=(const Client& other);
    bool operator==(const Client& other);
    bool operator!=(const Client& other);

    friend istream& operator>>(istream& in, Client& client);
    friend ostream& operator<<(ostream& out, const Client& client);
};
