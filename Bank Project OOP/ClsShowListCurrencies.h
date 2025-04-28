#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsCurrency.h"
#include<iomanip>

using namespace std;

class ClsShowListCurrencies : protected ClsScreen
{
private:
	
	static void _PrintCurrenciesInfo(ClsCurrency C)
	{
		cout << "|" << left << setw(40) << C.GetCurrenty();
		cout << "|" << left << setw(7)  << C.GetCurrencyCode();
		cout << "|" << left << setw(50) << C.GetCurrencyName();
		cout << "|" << left << setw(16) << C.GetRate();
	}

public:

	static void ShowCurrenciesList()
	{
		vector<ClsCurrency>Vcurrency = ClsCurrency::GetCurrencyList();
		string SubTitle = "\n\t\t (" + to_string(Vcurrency.size()) + ") Currency(s)\n";
		_DrawScreenHeader("\n\t\tShow Currencies List", SubTitle);

		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";
		cout << "|" << left << setw(40) << "Country";
		cout << "|" << left << setw(7)  << "Code";
		cout << "|" << left << setw(50) << "Currency Name";
		cout << "|" << left << setw(16) << "Rate/(1$)";
		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";

		if (Vcurrency.size() == 0)
		{
			cout << "\n\n\t\tThere aren't Currencies!\n\n";
		}
		else
		{
			for (ClsCurrency& C : Vcurrency)
			{
				_PrintCurrenciesInfo(C);
				cout << endl;
			}
		}
		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";
	}
};

