#pragma once

#include<iostream>
#include<string>
#include"ClsString.h"
#include<vector>
#include<fstream>

using namespace std;

class ClsCurrency
{

private:

	enum enMode { EmptyMode = 0, UpdatedMode = 1 };

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float  _Rate;

	static ClsCurrency _ConvertLineToObject(string Line, string Seperator = "#//#")
	{
		vector<string>_Vcurrency = ClsString::Split(Line, Seperator);

		return ClsCurrency(enMode::UpdatedMode, _Vcurrency[0], _Vcurrency[1], _Vcurrency[2],
			stof(_Vcurrency[3]));
	}

	static string _ConverObjectToLine(ClsCurrency Currency, string Seperator = "#//#")
	{
		string Line = "";

		Line += Currency._Country + Seperator;
		Line += Currency._CurrencyCode + Seperator;
		Line += Currency._CurrencyName + Seperator;
		Line += to_string(Currency._Rate);

		return Line;
	}

	static vector<ClsCurrency> _LoadCurrencyDataFromFile()
	{
		vector<ClsCurrency>_VcurrencyInfo;

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsCurrency Currency = _ConvertLineToObject(Line);
				_VcurrencyInfo.push_back(Currency);
			}

			MyFile.close();
		}

		return _VcurrencyInfo;
	}

	static void _SaveDataToFile(vector<ClsCurrency>_VcurrencyInfo)
	{
		fstream MyFile;

		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;

			for (ClsCurrency& C : _VcurrencyInfo)
			{
				Line = _ConverObjectToLine(C);
				MyFile << Line << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector<ClsCurrency>_VcurrencyInfo;

		_VcurrencyInfo = _LoadCurrencyDataFromFile();

		for (ClsCurrency& C : _VcurrencyInfo)
		{
			if (C.GetCurrencyName() == GetCurrencyName())
			{
				C = *this;
				break;
			}
		}

		_SaveDataToFile(_VcurrencyInfo);
	}

	static ClsCurrency _GetAnEmptyObject()
	{
		return ClsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	ClsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
		:_Mode{ Mode }, _Country{ Country }, _CurrencyName{ CurrencyName }, _CurrencyCode{ CurrencyCode },
		_Rate{ Rate } {
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	string GetCurrenty()
	{
		return _Country;
	}

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	float GetRate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static ClsCurrency FindByCurrecyCode(string CurrencyCode)
	{

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsCurrency Currency = _ConvertLineToObject(Line);

				if (ClsString::UpperAllString(Currency.GetCurrencyCode()) == ClsString::UpperAllString(CurrencyCode))
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetAnEmptyObject();
	}

	static ClsCurrency FindByCountry(string Country)
	{

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsCurrency CountryName = _ConvertLineToObject(Line);

				if (ClsString::UpperAllString(CountryName.GetCurrenty()) == ClsString::UpperAllString(Country))
				{
					MyFile.close();
					return CountryName;
				}
			}

			MyFile.close();
		}

		return _GetAnEmptyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		ClsCurrency Currency = ClsCurrency::FindByCurrecyCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static vector<ClsCurrency>GetCurrencyList()
	{
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return float(Amount /=GetRate());
	}

	float ConvertToOtherCurrencies(ClsCurrency ToCurrency, float Amount)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (ToCurrency.GetCurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return float(AmountInUSD * ToCurrency.GetRate());
	}
};