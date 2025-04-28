#pragma once

#include<iostream>
#include"ClsCurrency.h"
#include"ClsScreen.h"
#include"ClsInputValidate.h"
#include"ClsString.h"

using namespace std;

class ClsShowUpdateRate : protected ClsScreen
{
private:

	static void _PrintCurrencyInfo(ClsCurrency C)
	{
		cout << "\n\nCurrency Card\n";
		cout << "_____________________________\n\n";
		cout << "Country   : " << C.GetCurrenty() << endl;
		cout << "Code      : " << C.GetCurrencyCode() << endl;
		cout << "Name      : " << C.GetCurrencyName() << endl;
		cout << "Rate (1$) : " << C.GetRate() << endl;
		cout << "\n_____________________________\n\n";
	}

public:

	static void ShowUpdateRateScreen()
	{
		_DrawScreenHeader("\n\t\tUpdate Rate Screen\n");

		cout << "\n\nPlease enter currency code : ";
		string CurrencyCode = ClsInputValidate::ReadString();
		while (!ClsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\n\nThis Currency isn't exist , Try again : ";
			CurrencyCode = ClsInputValidate::ReadString();
		}
		ClsCurrency C = ClsCurrency::FindByCurrecyCode(CurrencyCode);
		_PrintCurrencyInfo(C);
		cout << "\n\nAre you sure from updateing this 'Rate' ? (y/n) ? ";
		char A;
		cin >> A;

		if (A == tolower('Y'))
		{
			cout << "\n\nUpdate Currency Rate\n";
			cout << "--------------------------------\n";
			cout << "Enter New Rate : ";
			float NewRate;
			cin >> NewRate;

			C.UpdateRate(NewRate);

			cout << "\n\nCurrency Updated Successfully.\n";
			_PrintCurrencyInfo(C);
		}
		else
		{
			_PrintCurrencyInfo(C);
		}
	}
};

