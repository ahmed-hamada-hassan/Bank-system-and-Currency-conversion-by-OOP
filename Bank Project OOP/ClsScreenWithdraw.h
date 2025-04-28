#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsInputValidate.h"
#include"ClsBankClient.h"

using namespace std;

class ClsScreenWithdraw : protected ClsScreen
{
private:

	static void _PrintClient(ClsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nPassword    : " << Client.PINCODE;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\n\t\tWithdraw Screen");

		string AccountNumber = "";

		cout << "Enter your Account Number : ";
		AccountNumber = ClsInputValidate::ReadString();

		while (!ClsBankClient::IsClientExist(AccountNumber))
		{
			cout << "This Account Number isn't exists , Try again : ";
			AccountNumber = ClsInputValidate::ReadString();
		}

		ClsBankClient Client = ClsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "\n\nEnter Withdraw Amount : ";
		Amount = ClsInputValidate::ReadDblNumber();

		cout << "\n\nAre you sure from Withdrawing this amount ? (y/n) ? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == tolower('Y'))
		{
			while (!Client.Withdraw(Amount))
			{
				cout << "\n\nYou cann't do this , Try again : ";
				Amount = ClsInputValidate::ReadDblNumber();
			}

			cout << "\n\nThe Amount Withdrawed Successfully\n";
			cout << "\nNew Balance : " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\n\nCancelled";
		}
	}
};

