#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsInputValidate.h"
#include"ClsCurrency.h"

using namespace std;

class ClsShowCurrencyCalculator : protected ClsScreen
{

private:

	static void _PrintCurrencyInfo(ClsCurrency C,string Title)
	{
		cout << "\n\n" << Title << endl;
		cout << "_____________________________\n\n";
		cout << "Country   : " << C.GetCurrenty() << endl;
		cout << "Code      : " << C.GetCurrencyCode() << endl;
		cout << "Name      : " << C.GetCurrencyName() << endl;
		cout << "Rate (1$) : " << C.GetRate() << endl;
		cout << "\n_____________________________\n\n";
	}

	static ClsCurrency _ReadCurrencyCode(string Message)
	{
		cout << Message;
		string CurrencyCode = ClsInputValidate::ReadString();
		while (!ClsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\n\nTry again this currency code isn't exist! , Enter Currency code again : ";
			CurrencyCode = ClsInputValidate::ReadString();
		}
		ClsCurrency C = ClsCurrency::FindByCurrecyCode(CurrencyCode);

		return C;
	}

	static float _ReadAmount()
	{
		cout << "\n\nEnter the amount that you need to convert it : ";
		float Amount = ClsInputValidate::ReadFloatNumber();

		return Amount;
	}

	static void _PrintFinalResult(ClsCurrency C1, ClsCurrency C2, float Amount)
	{
		_PrintCurrencyInfo(C1, "Convert From:");
		float AmountInUSD = C1.ConvertToUSD(Amount);
		cout << Amount << " " << C1.GetCurrencyCode() << " = " << AmountInUSD << " USD \n";

		if (C2.GetCurrencyCode() == "USD")
		{
			return;
		}

		cout << endl << endl << "Converting from USD to :\n\n";
		_PrintCurrencyInfo(C2, "To:");
		float AmountInOtherCurrency = C1.ConvertToOtherCurrencies(C2, Amount);
		cout << endl << Amount << C1.GetCurrencyCode() << " = " << AmountInOtherCurrency
			<< C2.GetCurrencyCode() << endl;
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		char DoAgain = 'y';

		while (DoAgain == tolower('Y'))
		{
			system("cls");
			_DrawScreenHeader("\n\t\tShow Currency Calculator Screen\n");

			ClsCurrency C1 = _ReadCurrencyCode("\n\nEnter Currency 1 Code : ");
			ClsCurrency C2 = _ReadCurrencyCode("\n\nEnter Currency 2 Code : ");
			float Amount = _ReadAmount();

			_PrintFinalResult(C1, C2, Amount);

			cout << "\n\nDo you need to do this operation again ? ";
			cin >> DoAgain;
		}
	}
};

