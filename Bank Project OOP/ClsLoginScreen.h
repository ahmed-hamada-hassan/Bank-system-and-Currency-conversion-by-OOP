#pragma once

#include<iostream>
#include"ClsBankUser.h"
#include"ClsShowMainMenueScreen.h"
#include"ClsScreen.h"
#include"ClsInputValidate.h"
#include"Global.h"

using namespace std;

class ClsLoginScreen : protected ClsScreen
{
private:

	static bool _Login()
	{
		string UserName, Password;
		bool LoginFaild = false;
		short LoginFaildCounter = 0;

		do
		{
			if (LoginFaild)
			{
				LoginFaildCounter++;
				cout << "\nInvalid User Name and Password!";
				cout << "\n\nYou have " << (3 - LoginFaildCounter) << " Trail(s) to login.";

				if (LoginFaildCounter == 3)
				{
					cout << "\n\n\t\t-----------------------------------------------";
					cout << "\n\n\t\t\tLocked after 3 times login\n\n";
					cout << "\t\t-----------------------------------------------\n\n";
					system("pause>0");
					return false;
				}
			}

			cout << "\n\nEnter User Name : ";
			UserName = ClsInputValidate::ReadString();

			cout << "\n\nEnter Password : ";
			Password = ClsInputValidate::ReadString();

			CurrentUser = ClsBankUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild == true);

		CurrentUser.RegisterLogIn();

		ClsShowMainMenueScreen::MainMenueScreen();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		_DrawScreenHeader("\n\t\t\tLogin User Screen\n");

		return _Login();
	}
};

