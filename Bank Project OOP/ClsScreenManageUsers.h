#pragma once

#include<iostream>
#include"ClsInputValidate.h"
#include"ClsScreen.h"
#include"ClsScreenShowUsersList.h"
#include"ClsScreenAddNewUser.h"
#include"ClsScreenDeleteUserInfo.h"
#include"ClsScreenUpdateUserInfo.h"
#include"ClsScreenFindUser.h"

using namespace std;

class ClsScreenManageUsers : protected ClsScreen
{
private:

	enum enManageUserScreenOptions
	{
		ListUsers = 1,
		AddNewUser = 2,
		DeleteUser = 3,
		UpdateUser = 4,
		FindUser = 5,
		MainMenue = 6
	};

	static short _ReadManageUsersOption()
	{
		cout << "Choose what you want from [1 to 6] : ";
		short Choice = ClsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6 : ");
		return Choice;
	}

	static void _GoBackToManageUsersScreen()
	{
		cout << "\n\t\t\tPress any key to go back to Manage Users Screen...\n";
		system("pause>0");
		ShowManageUsersScreen();
	}

	static void _ShowListUsersScreen()
	{
		ClsScreenShowUsersList::ShowUserList();
	}

	static void _ShowAddUsersScreen()
	{
		ClsScreenAddNewUser::AddNewUser();
	}

	static void _ShowDeleteUsersScreen()
	{
		ClsScreenDeleteUserInfo::DeleteClient();
	}

	static void _ShowUpdateUsersScreen()
	{
		ClsScreenUpdateUserInfo::UpdateUser();
	}

	static void _ShowFindUsersScreen()
	{
		ClsScreenFindUser::FindClientInfo();
	}

	static void _PerformManageUserScreen(enManageUserScreenOptions Choice)
	{
		switch (Choice)
		{
		case ClsScreenManageUsers::ListUsers:
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersScreen();
			break;

		case ClsScreenManageUsers::AddNewUser:
			system("cls");
			_ShowAddUsersScreen();
			_GoBackToManageUsersScreen();
			break;

		case ClsScreenManageUsers::DeleteUser:
			system("cls");
			_ShowDeleteUsersScreen();
			_GoBackToManageUsersScreen();
			break;

		case ClsScreenManageUsers::UpdateUser:
			system("cls");
			_ShowUpdateUsersScreen();
			_GoBackToManageUsersScreen();
			break;

		case ClsScreenManageUsers::FindUser:
			system("cls");
			_ShowFindUsersScreen();
			_GoBackToManageUsersScreen();
			break;
		case ClsScreenManageUsers::MainMenue:
			break;
		}
	}


public:

	static void ShowManageUsersScreen()
	{
		system("cls");

		if (!CheckAccessRight(ClsBankUser::EnAccessPermission::ManageUsersAccess))
		{
			return;
		}
		
		_DrawScreenHeader("\t\t\tManage Users Screen");

		cout << "============================================\n\n";
		cout << "\tManage Users Screen\n\n";
		cout << "============================================\n\n";
		cout << "[1] List Users.\n";
		cout << "[2] Add New User.\n";
		cout << "[3] Delete User.\n";
		cout << "[4] Update User Info.\n";
		cout << "[5] Find User.\n";
		cout << "[6] Main Menue.\n";
		cout << "============================================\n\n";
		_PerformManageUserScreen(enManageUserScreenOptions(_ReadManageUsersOption()));
	}
};
