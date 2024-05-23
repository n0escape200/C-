#include "Motocicleta.h"


Motocicleta::Motocicleta() :Vehicul(), tipMotor("undefined"), corp("undefined") {};
Motocicleta::Motocicleta(Vehicul vehicul, string tipMotor, string corp) :Vehicul(vehicul), tipMotor(tipMotor), corp(corp) {};
Motocicleta::Motocicleta(const Motocicleta& other) :Vehicul(other), tipMotor(other.tipMotor), corp(other.corp) {}


Motocicleta& Motocicleta::operator=(const Motocicleta& other)
{
	if (this != &other) {
		Vehicul::operator=(other);
		tipMotor = other.tipMotor;
		corp = other.corp;
	}
	return *this;
}

bool Motocicleta::operator==(const Motocicleta& other) {

	if (!Vehicul::operator==(other) || tipMotor != other.tipMotor || corp != other.corp) {
		return false;	
	}
	return true;
}

istream& operator>>(istream& in, Motocicleta& veh)
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
    cout << "Tip motor: ";
    in >> veh.tipMotor;
    cout << "Corp: ";
    in >> veh.corp;
    return in;
}

ostream& operator<<(ostream& out, const Motocicleta& veh)
{
    out << "\nBrand: " << veh.Brand << "\nModel: " << veh.Model << "\nAn : " << veh.An
        << "\nKM: " << veh.KM << "\nPret: " << veh.Pret << "\nCapacitate Cilindrica: " << veh.CapacitateCilindrica
        << "\nCombustibil: " << veh.Combustibil << "\nTip motor: " << veh.tipMotor << "\nCorp:" << veh.corp;
    return out;
}
