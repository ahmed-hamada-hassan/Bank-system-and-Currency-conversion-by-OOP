#pragma once

#include<iostream>
#include"ClsBankUser.h"
#include"ClsInputValidate.h"
#include"ClsScreen.h"
#include"iomanip"

using namespace std;

class ClsLoginRegistor : protected ClsScreen
{
private:

	static void _PrintUserLoginRecord(ClsBankUser::StLoginRegistorInfo Login)
	{
		cout << "|" << left << setw(25) << Login.DateTime;
		cout << "|" << left << setw(10) << Login.UserName;
		cout << "|" << left << setw(10) << Login.Password;
		cout << "|" << left << setw(5)  << Login.Permission;
	}

public:

	static void ShowUserLoginList()
	{
		if (!CheckAccessRight(ClsBankUser::EnAccessPermission::LoginRegistorHistory))
		{
			return;
		}

		vector<ClsBankUser::StLoginRegistorInfo>vUserLoginList = ClsBankUser::GetLoginInfo();

		string SubTitle = "\n\t\t (" + to_string(vUserLoginList.size()) + ") client(s)\n";
		_DrawScreenHeader("\n\t\tShow User Login List", SubTitle);


		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";

		cout << "|" << left << setw(25) << "Date / Time";
		cout << "|" << left << setw(10) << "UserName";
		cout << "|" << left << setw(10) << "Password";
		cout << "|" << left << setw(5)  << "Permission";

		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";

		if (vUserLoginList.size() == 0)
			cout << "\t\t\t\t\tNo History for logining !\n";

		for (ClsBankUser::StLoginRegistorInfo& C : vUserLoginList)
		{
			_PrintUserLoginRecord(C);
			cout << endl;
		}

		cout << "\n\n____________________________________________________________";
		cout << "____________________________________________________________\n\n";
	}
};

