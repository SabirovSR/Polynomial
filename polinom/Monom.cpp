#include "Monom.h"

Monom::Monom() : coeff(0), x(0), y(0), z(0) {}

Monom::Monom(double _coeff, int _x, int _y, int _z)
    : coeff(_coeff), x(_x), y(_y), z(_z) {}

void Monom::SetCoeff(double _coeff)
{
    coeff = _coeff;
}

void Monom::SetXYZ(int _x, int _y, int _z)
{
    x = _x;
    y = _y;
    z = _z;
}

bool Monom::operator<(const Monom& m) const
{
    if (x != m.x) return x < m.x;
    if (y != m.y) return y < m.y;
    return z < m.z;
}

bool Monom::operator>(const Monom& m) const
{
    if (x != m.x) return x > m.x;
    if (y != m.y) return y > m.y;
    return z > m.z;
}

bool Monom::operator==(const Monom& m) const
{
    return (x == m.x) && (y == m.y) && (z == m.z);
}

bool Monom::operator!=(const Monom& m) const
{
    return !(*this == m);
}

istream& operator>>(istream& in, Monom& mon)
{
    cout << "Коэффициент: ";
    in >> mon.coeff;
    cout << "Степень x: ";
    in >> mon.x;
    cout << "Степень y: ";
    in >> mon.y;
    cout << "Степень z: ";
    in >> mon.z;
    return in;
}

ostream& operator<<(ostream& out, const Monom& mon)
{
    if (mon.coeff == 0)
    {
        out << "0";
    }
    else
    {
        out << mon.coeff << "x^" << mon.x << "y^" << mon.y << "z^" << mon.z;
    }
    return out;
}
