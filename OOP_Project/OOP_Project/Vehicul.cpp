#include "Vehicul.h"


Vehicul& Vehicul::operator=(const Vehicul& other)
{
    if (this != &other)
    {
        Brand = other.Brand;
        Model = other.Model;
        An = other.An;
        KM = other.KM;
        Pret = other.Pret;
        CapacitateCilindrica = other.CapacitateCilindrica;
        Combustibil = other.Combustibil;
        Ownerid = other.Ownerid;
    }
    return *this;
}

bool Vehicul::operator==(const Vehicul& other)
{
    if (Brand != other.Brand || Model != other.Model || An != other.An || KM != other.KM || Pret != other.Pret
        || CapacitateCilindrica != other.CapacitateCilindrica || Combustibil != other.Combustibil || Ownerid != other.Ownerid) {
        return false;
    }
    return true;
}

istream& operator>>(istream& in, Vehicul& veh)
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
    return in;
}

ostream& operator<<(ostream& out, const Vehicul& veh)
{
    out << "Brand: " << veh.Brand << ", Model: " << veh.Model << ", An: " << veh.An
        << ", KM: " << veh.KM << ", Pret: " << veh.Pret << ", Capacitate Cilindrica: " << veh.CapacitateCilindrica
        << ", Combustibil: " << veh.Combustibil << ", Owner: "<<veh.Ownerid;
    return out;
}
