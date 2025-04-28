#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankUser.h"
#include<iomanip>
#include"ClsUtility.h"

using namespace std;

class ClsScreenShowUsersList : protected ClsScreen
{
private:

	static void _PrintUserRecord(ClsBankUser User)
	{
		cout << "|" << left << setw(15) << User.UserName;
		cout << "|" << left << setw(25) << User.FullName();
		cout << "|" << left << setw(15) << User.Phone;
		cout << "|" << left << setw(30) << User.Email;
		cout << "|" << left << setw(10) << User.Password;
		cout << "|" << left << setw(15) << User.Permission;
	}

public:

	static void ShowUserList()
	{
		vector<ClsBankUser>vUsersList = ClsBankUser::GetUserList();

	string SubTitle = "\n\t\t (" + to_string(vUsersList.size()) + ") user(s)\n";
	_DrawScreenHeader("\n\t\tShow User List", SubTitle);


	cout << "\n\n____________________________________________________________";
	cout << "____________________________________________________________\n\n";

	cout << "|" << left << setw(15) << "User Name";
	cout << "|" << left << setw(25) << "Full Name";
	cout << "|" << left << setw(15) << "Phone";
	cout << "|" << left << setw(30) << "Email";
	cout << "|" << left << setw(10) << "Password";
	cout << "|" << left << setw(15) << "Permission";

	cout << "\n\n____________________________________________________________";
	cout << "____________________________________________________________\n\n";

	if (vUsersList.size() == 0)
		cout << "\t\t\t\t\tNo Users Available In The System !\n";

	for (ClsBankUser& C : vUsersList)
	{
		_PrintUserRecord(C);
		cout << endl;
	}

	cout << "\n\n____________________________________________________________";
	cout << "____________________________________________________________\n\n";
}
};

