#pragma once
#include "Vehicul.h"
class Masina :
    public Vehicul
{
    string sasiu;
    string transmisie;
    int nrUsi;

public:
    Masina();
    Masina(Vehicul vehicul, string sasiu, string transmise, int nrUsi);
    Masina(const Masina& other);

    string GetSasiu() { return sasiu; }
    string GetTransmisie() { return transmisie; }
    int GetNrUsi() { return nrUsi; }

    void SetSasiu(string _sasiu) { sasiu = _sasiu; }
    void SetTransmisie(string _transmisie) { transmisie = _transmisie; }
    void SetNrUsi(int _nrUsi) { nrUsi = _nrUsi; }

    Masina& operator=(const Masina& other);
    bool operator==(const Masina& other);

    friend istream& operator>>(istream& in, Masina& veh);

    friend ostream& operator<<(ostream& out, const Masina& veh);

};

