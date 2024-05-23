#pragma once
#include "Vehicul.h"
class Camion :
    public Vehicul
{
    int greutateMaxima;
    int lungimePlatforma;
public:
    Camion();
    Camion(Vehicul vehicul, int greutateMaxima, int lungimePlatforma);
    Camion(const Camion& other);

    int GetGretutate() { return greutateMaxima; }
    int GetLungime() { return lungimePlatforma; }

    void SetGreutate(int greutate) { greutateMaxima = greutate; }
    void SetLungimePlatforma(int lungime) { lungimePlatforma = lungime; }
    

    Camion& operator=(const Camion& other);
    bool operator==(const Camion& other);

    friend istream& operator>>(istream& in, Camion& veh);
    friend ostream& operator<<(ostream& out, const Camion& veh);
};

