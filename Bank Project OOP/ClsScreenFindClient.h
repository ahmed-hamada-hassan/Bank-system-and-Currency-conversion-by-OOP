#pragma once

#include<iostream>
#include"ClsBankClient.h"
#include"ClsInputValidate.h"
#include"ClsScreen.h"

using namespace std;

class ClsScreenFindClient : protected ClsScreen
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
	static void FindClientInfo()
	{
		if (!CheckAccessRight(ClsBankUser::EnAccessPermission::FindClientAccess))
		{
			return;
		}
		
		_DrawScreenHeader("\n\t\t\tFind Client Info Screen");

		string AccountNumber = "";

		cout << "Enter your Account Number : ";
		AccountNumber = ClsInputValidate::ReadString();

		while (!ClsBankClient::IsClientExist(AccountNumber))
		{
			cout << "This Account Number isn't exists , Try again : ";
			AccountNumber = ClsInputValidate::ReadString();
		}

		ClsBankClient Client = ClsBankClient::Find(AccountNumber);

		if (!Client.IsEmpty())
		{
			cout << "\n\nClient found already :-)\n";
		}
		else
		{
			cout << "\n\nClient isn't find :-(\n";
		}

		_PrintClient(Client);
	}
};

