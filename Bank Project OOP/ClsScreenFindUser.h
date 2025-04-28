#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsInputValidate.h"
#include"ClsBankUser.h"

using namespace std;

class ClsScreenFindUser : protected ClsScreen
{
private:

	static void _PrintUser(ClsBankUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermision   : " << User.Permission;
		cout << "\n___________________\n";
	}

public:
	static void FindClientInfo()
	{
		_DrawScreenHeader("\n\t\t\tFind User Info Screen");

		string UserName = "";

		cout << "Enter your User Name : ";
		UserName = ClsInputValidate::ReadString();

		while (!ClsBankUser::IsUserExist(UserName))
		{
			cout << "This Account Number isn't exists , Try again : ";
			UserName = ClsInputValidate::ReadString();
		}

		ClsBankUser User = ClsBankUser::Find(UserName);

		if (!User.IsEmpty())
		{
			cout << "\n\nUser found already :-)\n";
		}
		else
		{
			cout << "\n\nUser isn't find :-(\n";
		}

		_PrintUser(User);
	}
};

