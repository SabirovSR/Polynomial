#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <string>
#include <sstream>
#include "List.h"
#include "Monom.h"

class Polynomial : public List<Monom>
{
public:
	// ����������� �� ���������
	Polynomial();

	// ����������� �����������
	Polynomial(const Polynomial& polynomial);

	// ����������� � �������� �������
	Polynomial(Monom* omnom, int size);

	// ����������
	~Polynomial();

	// ���������� ������ � �������
	void AddMonom(Monom m);							

	// ��� �������� ���������
	Polynomial operator+(Polynomial& other);

	// ��� ��������� ���������
	Polynomial operator-(Polynomial& other);

	// ��������� �������� �� ���������
	Polynomial operator*(double constanta);

	// ��������� �������� �� �����
	Polynomial operator*(Monom& m);

	// ���������
	bool operator==(Polynomial& other);

	Polynomial& operator+=(Polynomial& pol);
	Polynomial& operator-=(Polynomial& pol);
	Polynomial operator*(Polynomial& pol);

	friend std::ostream& operator<<(std::ostream& out, const Polynomial& p)
	{
		if (p.pFirst == nullptr)
		{
			out << "0";
			return out;
		}

		Node<Monom>* tmp = p.pFirst;
		bool isFirst = true;

		bool hasNoZero = false; 

		while (tmp != nullptr)
		{
			double coeff = tmp->val.coeff;

			if (coeff != 0)
			{
				hasNoZero = true;

				if (isFirst)
				{
					if (coeff < 0)
					{
						out << "-";
						coeff = -coeff;
					}
				}
				else
				{
					if (coeff > 0)
					{
						out << " + ";
					}
					else if (coeff < 0)
					{
						out << " - ";
						coeff = -coeff;
					}
				}

				out << coeff;

				out << "x^" << tmp->val.x;
				out << "y^" << tmp->val.y;
				out << "z^" << tmp->val.z;
			}

			tmp = tmp->pNext;
			isFirst = false;
		}

		if (!hasNoZero)
		{
			out << "0";
		}

		return out;
	}
};

// ���� ������� � �������
std::istream& operator>>(std::istream& in, Polynomial& pol)		
{
	int numMonoms;
	std::cout << "���-�� �������: ";
	in >> numMonoms;

	for (int i = 0; i < numMonoms; ++i) 
	{
		Monom mon;
		in >> mon;
		pol.AddMonom(mon);
	}
	return in;
}

std::string toString(const Polynomial& p)
{
	std::ostringstream oss;
	oss << p;
	return oss.str();
}

Polynomial::Polynomial() {}

Polynomial::Polynomial(const Polynomial& p) : List<Monom>(p){}

Polynomial::Polynomial(Monom* p, int size)
{
	pFirst = pLast = nullptr;
	sz = 0;
	for (int i = 0; i < size; i++)
	{
		AddMonom(p[i]);
	}
}

Polynomial::~Polynomial() {}

void Polynomial::AddMonom(Monom m)
{
	if (pFirst == nullptr)
	{
		insLast(m);
		return;
	}

	reset();							

	while (!isEnd() && pCurr->val > m)
	{	
		goNext();
	}

	if (!isEnd() && pCurr->val == m)
	{
		pCurr->val.coeff += m.coeff;

		if (pCurr->val.coeff == 0)
		{
			delCurr();
		}
	}
	else										
	{
		Node<Monom>* tmp = new Node<Monom>{ m, pCurr };

		if (pPrev == nullptr)					
			pFirst = tmp;
		else
			pPrev->pNext = tmp;					

		if (pCurr == nullptr)					
			pLast = tmp;

		sz++;
	}
}

Polynomial Polynomial::operator+(Polynomial& other)
{
	Polynomial res(*this);						

	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();
		res.AddMonom(tmp);					
	}
	return res;
}

Polynomial Polynomial::operator-(Polynomial& other)
{
	Polynomial res(*this);
	for (other.reset(); !other.isEnd(); other.goNext())
	{
		Monom tmp = other.getCurrent();
		tmp.coeff = -tmp.coeff;
		res.AddMonom(tmp);
	}
	return res;
}

Polynomial Polynomial::operator*(double constanta)
{
	Polynomial res;
	for (reset(); !isEnd(); goNext())
	{
		Monom tmp = getCurrent();
		tmp.coeff *= constanta;
		res.AddMonom(tmp);
	}
	return res;
}

Polynomial Polynomial:: operator*(Monom& m)
{
	Polynomial res;
	for (reset(); !isEnd(); goNext())
	{
		Monom tmp = getCurrent();
		tmp.coeff *= m.coeff;
		tmp.x += m.x;
		tmp.y += m.y;
		tmp.z += m.z;
		res.AddMonom(tmp);
	}
	return res;
}

bool Polynomial :: operator==(Polynomial& other)
{
	if (sz != other.sz)
	{
		return false;
	}
	reset();
	other.reset();
	while (!isEnd())
	{
		if (getCurrent() != other.getCurrent())
		{
			return false;
		}
		goNext();
		other.goNext();
	}
	return true;
}

// ������� �� �������� ���������
// �.�. ���� ����� �� ���� ���������
Polynomial& Polynomial:: operator+=(Polynomial& pol) {
	Polynomial res;
	this->reset();
	pol.reset();

	while (!this->isEnd() || !pol.isEnd())
	{
		if (this->isEnd())
		{
			if (!pol.isEnd())
			{
				res.AddMonom(pol.getCurrent());
				pol.goNext();
			}
		}
		else if (pol.isEnd())
		{
			res.AddMonom(this->getCurrent());
			this->goNext();
		}
		else if (pol.getCurrent() > this->getCurrent())
		{
			res.AddMonom(pol.getCurrent());
			pol.goNext();
		}
		else if (this->getCurrent() > pol.getCurrent()) 
		{
			res.AddMonom(this->getCurrent());
			this->goNext();
		}
		else											
		{
			Monom sum = this->getCurrent();				
			sum.coeff += pol.getCurrent().coeff;
			if (sum.coeff != 0)							
			{
				res.AddMonom(sum);
			}
			this->goNext();
			pol.goNext();
		}
	}
	*this = res;
	return *this;
}


Polynomial& Polynomial::operator-=(Polynomial& pol) 
{
	Polynomial res;
	this->reset();
	pol.reset();

	while (!this->isEnd() || !pol.isEnd()) 
	{
		if (this->isEnd()) 
		{
			if (!pol.isEnd()) 
			{
				Monom tmp = pol.getCurrent();
				tmp.coeff = -tmp.coeff;
				res.AddMonom(tmp);
				pol.goNext();
			}
		}
		else if (pol.isEnd())
		{
			res.AddMonom(this->getCurrent());
			this->goNext();
		}
		else if (pol.getCurrent() > this->getCurrent()) 
		{
			Monom tmp = pol.getCurrent();
			tmp.coeff = -tmp.coeff;
			res.AddMonom(tmp);
			pol.goNext();
		}
		else if (this->getCurrent() > pol.getCurrent()) 
		{
			res.AddMonom(this->getCurrent());
			this->goNext();
		}
		else 
		{
			Monom sum = this->getCurrent();
			sum.coeff -= pol.getCurrent().coeff;
			if (sum.coeff != 0) 
			{
				res.AddMonom(sum);
			}
			this->goNext();
			pol.goNext();
		}
	}
	*this = res;
	return *this;
}

Polynomial Polynomial::operator*(Polynomial& pol)
{
	Polynomial res;
	for (reset(); !isEnd(); goNext()) 
	{
		Monom m1 = getCurrent();
		pol.reset();
		while (!pol.isEnd())
		{
			Monom m2 = pol.getCurrent();
			Monom mult(m1.coeff * m2.coeff, m1.x + m2.x, m1.y + m2.y, m1.z + m2.z);
			res.AddMonom(mult);
			pol.goNext();
		}
	}
	return res;
}