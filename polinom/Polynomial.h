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
	// Конструктор по умолчанию
	Polynomial();

	// Конструктор копирования
	Polynomial(const Polynomial& polynomial);

	// Конструктор с массивом мономов
	Polynomial(Monom* omnom, int size);

	// Деструктор
	~Polynomial();

	// Добавление монома в полином
	void AddMonom(Monom m);							

	// Для сложения полиномов
	Polynomial operator+(Polynomial& other);

	// Для вычитания полиномов
	Polynomial operator-(Polynomial& other);

	// Умножение полинома на константу
	Polynomial operator*(double constanta);

	// Умножение полинома на моном
	Polynomial operator*(Monom& m);

	// Сравнение
	bool operator==(Polynomial& other);

	void operator+=(Polynomial p);
	void operator-=(Polynomial p);
	Polynomial operator*(Polynomial& p);

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

// Ввод мономов в полином
std::istream& operator>>(std::istream& in, Polynomial& pol)		
{
	int numMonoms;
	std::cout << "Кол-во мономов: ";
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

void Polynomial:: operator+=(Polynomial p) {

	this->reset();
	p.reset();
	while (!p.isEnd() && !this->isEnd())
	{
		Monom m1 = this->pCurr->val;
		Monom m2 = p.pCurr->val;
		if (m2 > m1)
		{
			this->insCurr(m2);
			p.goNext();
		}
		else if (m2 < m1)
		{
			this->goNext();
		}
		else if (m1.coeff != (m2.coeff * -1.0))
		{
			this->pCurr->val.coeff = m1.coeff + m2.coeff;
			p.goNext();
			this->goNext();
		}
		else
		{
			this->delCurr();
			p.goNext();
		}
	}

	if (this->isEnd() && !p.isEnd())
	{
		for (; !p.isEnd(); p.goNext())
			this->insLast(p.pCurr->val);
	}
}


void Polynomial::operator-=(Polynomial p) 
{
	this->reset();
	p.reset();
	while (!p.isEnd() && !this->isEnd())
	{
		Monom m1 = this->pCurr->val;
		Monom m2 = p.pCurr->val;
		if (m2 > m1)
		{
			m2.coeff *= -1;
			this->insCurr(m2);
			p.goNext();
		}
		else if (m2 < m1)
		{
			this->goNext();
		}
		else if (m1.coeff != m2.coeff)
		{
			this->pCurr->val.coeff = m1.coeff - m2.coeff;
			p.goNext();
			this->goNext();
		}
		else
		{
			this->delCurr();
			p.goNext();
		}
	}

	if (this->isEnd() && !p.isEnd())
	{
		for (; !p.isEnd(); p.goNext())
		{
			Monom m = p.pCurr->val;
			m.coeff *= -1;
			this->insLast(m);
		}
	}
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