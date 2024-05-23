#pragma once
#include "Vehicul.h"
class Motocicleta :
    public Vehicul
{
    string tipMotor;
    string corp;

public:
    Motocicleta();
    Motocicleta(Vehicul vehicul, string tipMotor, string corp);
    Motocicleta(const Motocicleta& other);

    string GetTipMotor() { return tipMotor; }
    string GetCorp() { return corp; }

    void SetTipMotor(string motor) { tipMotor = motor; }
    void SetCorp(string _corp) { corp = _corp; }

    Motocicleta& operator=(const Motocicleta& other);
    bool operator==(const Motocicleta& other);

    friend istream& operator>>(istream& in, Motocicleta& veh);
    friend ostream& operator<<(ostream& out, const Motocicleta& veh);
};

