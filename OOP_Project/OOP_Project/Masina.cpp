#include "Masina.h"


Masina::Masina() :Vehicul(),sasiu("undefined"),transmisie("undefined"),nrUsi(-1) {};

Masina::Masina(Vehicul vehicul, string sasiu, string transmise, int nrUsi)
	:Vehicul(vehicul), sasiu(sasiu), transmisie(transmisie), nrUsi(nrUsi) {}

Masina::Masina(const Masina& other)
	:Vehicul(other), sasiu(other.sasiu), transmisie(other.transmisie), nrUsi(other.nrUsi) {}


Masina& Masina::operator=(const Masina& other)
{
	if (this != &other) {
		Vehicul::operator=(other);
		sasiu = other.sasiu;
		transmisie = other.transmisie;
		nrUsi = other.nrUsi;
	}
	return *this;
}

bool Masina::operator==(const Masina& other)
{
    if (!Vehicul::operator==(other) || sasiu != other.sasiu || transmisie != other.transmisie || nrUsi != other.nrUsi) {
        return false;
    }
    return true;
}

istream& operator>>(istream& in, Masina& veh)
{
    cout << "Brand: ";
    in >> veh.Brand;
    cout << "Model: ";
    in >> veh.Model;
    cout << "An: ";
    in >> veh.An;
    cout << "KM: ";
    in >> veh.KM;
    cout << "Pret: ";
    in >> veh.Pret;
    cout << "Capacitate Cilindrica: ";
    in >> veh.CapacitateCilindrica;
    cout << "Combustibil: ";
    in >> veh.Combustibil;
    cout << "Sasiu: ";
    in >> veh.sasiu;
    cout << "Transmisie: ";
    in >> veh.transmisie;
    cout << "Numar usi: ";
    in >> veh.nrUsi;
    return in;
}

ostream& operator<<(ostream& out, const Masina& veh)
{
    out << "Brand: " << veh.Brand << "\nModel: " << veh.Model << "\nAn: " << veh.An
        << "\nKM: " << veh.KM << "\nPret: " << veh.Pret << "\nCapacitate Cilindrica: " << veh.CapacitateCilindrica
        << "\nCombustibil: " << veh.Combustibil << "\nSasiu: " << veh.sasiu << "\nTransmisie:" << veh.transmisie 
        << "\nNumar usi: " << veh.nrUsi;
    return out;
}
