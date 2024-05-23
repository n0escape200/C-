#pragma once
#include <iostream>
#include <string>
using namespace std;

class Vehicul
{
protected:
    string Brand;
    string Model;
    int An;
    float KM;
    float Pret;
    float CapacitateCilindrica;
    string Combustibil;
    int Ownerid;

public:
    virtual ~Vehicul() {}
    Vehicul(const string& _Brand, const string& _Model, int _An, float _KM, float _Pret, float _CapacitateCilindrica, const string& _Combustibil,int _ownerId)
        : Brand(_Brand), Model(_Model), An(_An), KM(_KM), Pret(_Pret), CapacitateCilindrica(_CapacitateCilindrica), Combustibil(_Combustibil), Ownerid(_ownerId){}

    Vehicul()
        :Brand("undefined"),Model("undefined"), An(0), KM(0.0), Pret(0.0), CapacitateCilindrica(0.0), Combustibil("undefined"),Ownerid(-1) {}

    Vehicul(const Vehicul& other)
        : Brand(other.Brand), Model(other.Model), An(other.An), KM(other.KM), Pret(other.Pret), CapacitateCilindrica(other.CapacitateCilindrica), Combustibil(other.Combustibil),Ownerid(other.Ownerid) {}

    string Getbrand() { return Brand; }
    string GetModel() { return Model; }
    int GetAn() { return An; }
    float GetKM() { return KM; }
    float GetPret() { return Pret; }
    float GetCapacitateCilindrica(){ return CapacitateCilindrica; }
    string GetCombustibil() { return Combustibil; }
    int GetOwnerId() { return Ownerid; }

    void SetBrand(string _brand) { Brand = _brand; }
    void SetModel(string _model) { Model = _model; }
    void SetAn(int _an) { An = _an; }
    void SetKm(int _km) { KM = _km; }
    void SetPret(float _pret) { Pret = _pret; }
    void SetCapacitateCilondrica(float _cap) { CapacitateCilindrica = _cap; }
    void SetCombustibil(string _combustibil) { Combustibil = _combustibil; }
    void SetOwnerId(int id) { Ownerid = id; }

    Vehicul& operator=(const Vehicul& other);
    bool operator==(const Vehicul& other);

    friend istream& operator>>(istream& in, Vehicul& veh);

    friend ostream& operator<<(ostream& out, const Vehicul& veh);
};

