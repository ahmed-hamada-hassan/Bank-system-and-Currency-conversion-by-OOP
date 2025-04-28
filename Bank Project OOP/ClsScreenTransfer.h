#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankClient.h"
#include"ClsInputValidate.h"

using namespace std;

class ClsScreenTransfer : protected ClsScreen
{
private:

	static void _PrintClient(ClsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nAcc. Number     : " << Client.GetAccountNumber();
		cout << "\nAccount Balance : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber()
	{
		string _AccountNumber;

		cout << "\n\nPlease enter an account numbet to transfer from : ";
		_AccountNumber = ClsInputValidate::ReadString();
		
		while (!ClsBankClient::IsClientExist(_AccountNumber))
		{
			cout << "\n\nAccount Number is not found , Try again : ";
			_AccountNumber = ClsInputValidate::ReadString();
		}

		return _AccountNumber;
	}

	static float _ReadAmount(ClsBankClient ClientFrom)
	{
		float _Amount;

		cout << "\n\nEnter transfer amount : ";
		_Amount = ClsInputValidate::ReadFloatNumber();

		while (_Amount > ClientFrom.AccountBalance)
		{
			cout << "\n\nThis amount exceeds the available balance , Try again : ";
			_Amount = ClsInputValidate::ReadFloatNumber();
		}

		return _Amount;
	}

public:

	static void TransferScreen()
	{
		_DrawScreenHeader("\n\t\t\tTransfer Screen\n");

		ClsBankClient ClientTransferFrom = ClsBankClient::Find(_ReadAccountNumber());
		_PrintClient(ClientTransferFrom);

		ClsBankClient ClientTransferTo = ClsBankClient::Find(_ReadAccountNumber());
		_PrintClient(ClientTransferTo);

		float Amount = _ReadAmount(ClientTransferFrom);

		cout << "\n\nAre you sure from performing this operation ? (y/n) ? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == tolower('Y'))
		{
			if (ClientTransferFrom.Transfer(Amount, ClientTransferTo,CurrentUser.UserName))
			{
				cout << "\n\nThe operation done successfully!\n";
			}
			else
			{
				cout << "\n\nThe operation isn't done successfully!\n";
			}
		}
		else
		{
			cout << "\n\nThe operation isn't done .\n";
		}

		_PrintClient(ClientTransferFrom);
		_PrintClient(ClientTransferTo);
	}
};

