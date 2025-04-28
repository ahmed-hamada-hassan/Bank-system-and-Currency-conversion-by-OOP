#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsInputValidate.h"
#include"ClsShowListCurrencies.h"
#include"ClsShowFindCurrency.h"
#include"ClsShowUpdateRate.h"
#include"ClsShowCurrencyCalculator.h"

using namespace std;

class ClsShowCurrencyExchange : protected ClsScreen
{
private:

	enum enCurrencyExchangeInfo
	{
		showListCurrencies = 1,
		FindCurrency = 2,
		UpdateRate = 3,
		CurrencyCalculator = 4,
		MainMenue = 5
	};

	static short _ReadCurrencyExchangeOptions()
	{
		cout << "Choose what you want from [1 to 5] : ";
		short Choice = ClsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5 : ");
		return Choice;
	}

	static void _GoBackToCurrencyExchangeScreen()
	{
		cout << "\n\t\t\tPress any key to go back to Currency Exchange Screen...\n";
		system("pause>0");
		CurrencyExchangeScreen();
	}

	static void _ShowListCurrencies()
	{
		ClsShowListCurrencies::ShowCurrenciesList();
	}

	static void _ShowFindCurrency()
	{
		ClsShowFindCurrency::FindCurrencyScreen();
	}

	static void _ShowUpdateRate()
	{
		ClsShowUpdateRate::ShowUpdateRateScreen();
	}

	static void _ShowCurrencyCalculator()
	{
		ClsShowCurrencyCalculator::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrencyExchangeScreen(enCurrencyExchangeInfo Currency)
	{
		switch (Currency)
		{
		case ClsShowCurrencyExchange::showListCurrencies:
			system("cls");
			_ShowListCurrencies();
			_GoBackToCurrencyExchangeScreen();
			break;

		case ClsShowCurrencyExchange::FindCurrency:
			system("cls");
			_ShowFindCurrency();
			_GoBackToCurrencyExchangeScreen();
			break;

		case ClsShowCurrencyExchange::UpdateRate:
			system("cls");
			_ShowUpdateRate();
			_GoBackToCurrencyExchangeScreen();
			break;

		case ClsShowCurrencyExchange::CurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculator();
			_GoBackToCurrencyExchangeScreen();
			break;

		case ClsShowCurrencyExchange::MainMenue:

			break;
		}
	}

public:

	static void CurrencyExchangeScreen()
	{
		system("cls");

		_DrawScreenHeader("\n\t\tCurrency Exchange Screen\n");

		cout << "\n\n==============================================================\n\n";
		cout << "\t\tCurrency Exchange Screen\n";
		cout << "\n==============================================================\n\n";
		cout << "[1] Show Currencies List.\n";
		cout << "[2] Find Currency.\n";
		cout << "[3] Update Rate.\n";
		cout << "[4] Currency Calculator.\n";
		cout << "[5] Main Menue Screen.\n";
		cout << "\n==============================================================\n\n";
		_PerformCurrencyExchangeScreen(enCurrencyExchangeInfo(_ReadCurrencyExchangeOptions()));
	}
};

