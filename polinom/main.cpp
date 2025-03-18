#include <iostream>
#include <vector>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include "Polynomial.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	vector<Polynomial> Polynomials;

	while (true)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		cout << "<<Выберите действие>>" << endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << " [1]  Добавить полином" << endl;
		cout << " [2]  Операции над полиномами" << endl;
		cout << " [3]  Напечатать все полиномы" << endl;
		cout << "[ESC] Уйти" << endl;

		unsigned char num;
		num = _getch();
		system("cls");

		// [ESC] Уйти
		if (num == 27)
			break;

		switch (num)
		{
		// [1] Добавить полином
		case 49:
		{
			Polynomial p;

			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			cout << "<<Введите полином>>" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			cin >> p;
			Polynomials.push_back(p);

			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			cout << "^^Полином добавлен^^" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			break;
		}
		// [2] Операции над полиномами
		case 50:
		{
			if (Polynomials.empty())
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
				cout << "[WAR] Необходимо ввести хотя бы один полином" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				break;
			}

			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			cout << "<<Выберите операцию>>" << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			cout << "[1] Сложение полиномов" << endl;
			cout << "[2] Вычитание полиномов" << endl;
			cout << "[3] Умножение полинома на константу" << endl;
			cout << "[4] Умножение полинома на моном" << endl;
			cout << "[5] Умножение полиномов" << endl;

			unsigned char operation;
			operation = _getch();
			system("cls");

			if (operation == 49 || operation == 50 || operation == 53) // 1 2 5
			{
				if (Polynomials.size() < 2)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
					cout << "[WAR] Для этой операции необходимо минимум два полинома" << endl;
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

					break;
				}
			}

			cout << "Введите номер первого полинома: ";
			int index1, index2 = 0;
			cin >> index1;

			if (index1 < 1 || index1 > Polynomials.size())
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
				cout << "[WAR] Некорректный индекс полинома" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				break;
			}

			if (operation == 49 || operation == 50 || operation == 53) // 1 2 5
			{
				cin >> index2;
				if (index2 < 1 || index2 > Polynomials.size())
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
					cout << "[WAR] Некорректный индекс полинома." << endl;
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

					break;
				}
			}

			switch (operation)
			{
			case 49: // [1]
			{
				Polynomial sum = Polynomials[index1-1] + Polynomials[index2-1];
				cout << "Сумма полиномов: " << sum << endl;

				Polynomials.push_back(sum);

				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				cout << "Результат записан" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				break;
			}
			case 50: // [2]
			{
				Polynomial sub = Polynomials[index1-1] - Polynomials[index2-1];
				cout << "Разность полиномов: " << sub << endl;

				Polynomials.push_back(sub);

				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				cout << "Результат записан" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				break;
			}
			case 51: // [3]
			{
				double constant;
				cout << "Введите константу: ";
				cin >> constant;
				Polynomial mulByConst = Polynomials[index1-1] * constant;
				cout << "Результат умножения на константу: " << mulByConst << endl;

				Polynomials.push_back(mulByConst);

				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				cout << "Результат записан" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				break;
			}
			case 52: // [4]
			{
				Monom mon;
				cout << "Введите моном для умножения: " << endl;
				cin >> mon;
				Polynomial mulByMonom = Polynomials[index1-1] * mon;
				cout << "Результат умножения на моном: " << mulByMonom << endl;

				Polynomials.push_back(mulByMonom);

				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				cout << "Результат записан" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				break;
			}
			case 53: // [5]
			{
				Polynomial mulByPolynomial = Polynomials[index1-1] * Polynomials[index2-1];
				cout << "Результат умножения полиномов: " << mulByPolynomial << endl;

				Polynomials.push_back(mulByPolynomial);

				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				cout << "Результат записан" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

				break;
			}
			}
			break;
		}
		// [3] Напечатать все полиномы
		case 51:
		{
			if (Polynomials.empty())
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
				cout << "[WAR] Полиномы отсутствуют" << endl;
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else
			{
				for (int i = 0; i < Polynomials.size(); i++)
				{
					cout << "Полином " << i+1 << ": " << Polynomials[i] << endl;
				}
			}
			break;
		}
		}
	}
}