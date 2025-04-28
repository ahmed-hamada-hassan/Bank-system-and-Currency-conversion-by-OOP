#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankClient.h"
#include<iomanip>

class ClsShowClientListScreen : protected ClsScreen
{
private:
	static void _PrintClientRecord(ClsBankClient Client)
	{
		cout << "|" << left << setw(15) << Client.GetAccountNumber();
		cout << "|" << left << setw(25) << Client.FullName();
		cout << "|" << left << setw(15) << Client.Phone;
		cout << "|" << left << setw(30) << Client.Email;
		cout << "|" << left << setw(10) << Client.PINCODE;
		cout << "|" << left << setw(15) << Client.AccountBalance;
	}
public:
	static void ShowClientList()
	{
		if (!CheckAccessRight(ClsBankUser::EnAccessPermission::ShowClientAccess))
		{
			return;
		}

		vector<ClsBankClient>vClientsList = ClsBankClient::GetClientsList();

		string SubTitle = "\n\t\t (" + to_string(vClientsList.size()) + ") client(s)\n";
		_DrawScreenHeader("\n\t\tShow Client List",SubTitle);
		
		
		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";

		cout << "|" << left << setw(15) << "Account Number";
		cout << "|" << left << setw(25) << "Full Name";
		cout << "|" << left << setw(15) << "Phone";
		cout << "|" << left << setw(30) << "Email";
		cout << "|" << left << setw(10) << "PIN Code";
		cout << "|" << left << setw(15) << "Account Balance";

		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";

		if (vClientsList.size() == 0)
			cout << "\t\t\t\t\tNo Clients Available In The System !\n";
		
		for (ClsBankClient& C : vClientsList)
		{
			_PrintClientRecord(C);
			cout << endl;
		}

		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";
	}
};

