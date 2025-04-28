#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsCurrency.h"
#include<iomanip>
#include"ClsInputValidate.h"

using namespace std;

class ClsShowFindCurrency : protected ClsScreen
{
private:

	static void _PrintCurrencyInfo(ClsCurrency C)
	{
		cout << "\n\nCurrency Card\n";
		cout << "_____________________________\n\n";
		cout << "Country   : " << C.GetCurrenty()     << endl;
		cout << "Code      : " << C.GetCurrencyCode() << endl;
		cout << "Name      : " << C.GetCurrencyName() << endl;
		cout << "Rate (1$) : " << C.GetRate()         << endl;
		cout << "\n_____________________________\n\n";
	}

	static void _FinalResult(ClsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\n\nCurrency found\n\n";
			_PrintCurrencyInfo(Currency);
		}
		else
		{
			cout << "\n\nCurrency was not found\n\n";
		}
		
	}

public :

	static void FindCurrencyScreen()
	{
		_DrawScreenHeader("\n\t\tFind Currency Screen\n");

		cout << "\n\nFind By : [1] Code OR [2] Country ? ";
		short Choice;
		cin >> Choice;

		if (Choice == 1)
		{
			cout << "\n\nEnter Currency Code : ";
			string CurrencyCode = ClsInputValidate::ReadString();
			ClsCurrency Currency = ClsCurrency::FindByCurrecyCode(CurrencyCode);
			_FinalResult(Currency);
		}
		else
		{
			cout << "\n\nEnter Country Name : ";
			string CountryName = ClsInputValidate::ReadString();
			ClsCurrency Country = ClsCurrency::FindByCountry(CountryName);
			_FinalResult(Country);
		}
	}
};

