#include "Camion.h"

Camion::Camion() :Vehicul(), greutateMaxima(0), lungimePlatforma(0) {};

Camion::Camion(Vehicul vehicul, int greutateMaxima, int lungimePlatforma)
	:Vehicul(vehicul),greutateMaxima(greutateMaxima),lungimePlatforma(lungimePlatforma)  {};

Camion::Camion(const Camion& other):Vehicul(other),greutateMaxima(other.greutateMaxima), lungimePlatforma(other.lungimePlatforma){}

Camion& Camion::operator=(const Camion& other)
{
	if (this != &other) {
		Vehicul::operator=(other);
		greutateMaxima = other.greutateMaxima;
		lungimePlatforma = other.lungimePlatforma;
	}
	return *this;
}

bool Camion::operator==(const Camion& other)
{
    if (!Vehicul::operator==(other) || greutateMaxima != other.greutateMaxima || lungimePlatforma != other.lungimePlatforma) {
        return false;
    }
    return true;
}

istream& operator>>(istream& in, Camion& veh)
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
    cout << "Greutate maxima:";
    in >> veh.greutateMaxima;
    cout << "Lungime platforma:";
    in >> veh.lungimePlatforma;
    return in;
}

ostream& operator<<(ostream& out,const Camion& veh)
{
    out << "\nBrand: " << veh.Brand << "\nModel: " << veh.Model << "\nAn: " << veh.An
        << "\nKM: " << veh.KM << "\nPret: " << veh.Pret << "\nCapacitate Cilindrica: " << veh.CapacitateCilindrica
        << "\nCombustibil: " << veh.Combustibil
        << "\nGreutate maxima: " << veh.greutateMaxima << "\nLungime platforma" << veh.lungimePlatforma;
    return out;
}


