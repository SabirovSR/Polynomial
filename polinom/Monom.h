#pragma once
#include <iostream>

using namespace std;

struct Monom
{
    double coeff;
    int x, y, z;
public:
    Monom();                              
    Monom(double _coeff, int x, int y, int z);

    void SetCoeff(double _coeff);
    void SetXYZ(int _x, int _y, int _z);

    bool operator<(const Monom& m) const;
    bool operator>(const Monom& m) const;
    bool operator==(const Monom& m) const;
    bool operator!=(const Monom& m) const;

    friend ostream& operator<<(ostream& out, const Monom& mon);
};

istream& operator>>(istream& in, Monom& mon);
