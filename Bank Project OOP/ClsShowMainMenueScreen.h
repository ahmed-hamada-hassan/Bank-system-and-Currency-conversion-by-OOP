#pragma once

#include<iostream>
#include"ClsScreen.h";
#include"ClsBankClient.h"
#include"ClsShowClientListScreen.h"
#include"ClsScreenAddNewClient.h"
#include"ClsScreenDeleteClientInfo.h"
#include"ClsScreenUpdateClientInfo.h"
#include"ClsScreenFindClient.h"
#include"ClsScreenTransactions.h"
#include"ClsScreenManageUsers.h"
#include"Global.h"
#include"ClsLoginRegistor.h"
#include"ClsShowCurrencyExchange.h"

class ClsShowMainMenueScreen:protected ClsScreen
{
private:
	enum enMainMenueOptions
	{
		showClientList = 1,
		AddNewClient = 2,
		DeleteClient = 3,
		UpdateClientInfo = 4,
		FindClient = 5,
		Transactions = 6,
		ManageUsers = 7,
		LoginRegister = 8,
		CurrencyExchange = 9,
		LogOut = 10
	};

	static short _ReadMainMenueOption()
	{
		cout << "Choose what you want from [1 to 10] : ";
		short Choice = ClsInputValidate::ReadIntNumberBetween(1, 10, "Enter Number between 1 to 10 : ");
		return Choice;
	}

	static void _GoBackToMainMenue()
	{
		cout << "\n\t\t\tPress any key to go back to Main Menue...\n";
		system("pause>0");
		MainMenueScreen();
	}

	static void _ShowClientList()
	{
		ClsShowClientListScreen::ShowClientList();
	}

	static void _ShowLoginRegistorScreen()
	{
		ClsLoginRegistor::ShowUserLoginList();
	}

	static void _AddNewClient()
	{
		ClsScreenAddNewClient::AddNewClient();
	}

	static void _DeleteClient()
	{
		ClsScreenDeleteClientInfo::DeleteClient();
	}

	static void _UpdateClientInfo()
	{
		ClsScreenUpdateClientInfo::UpdateClient();
	}

	static void _FindClient()
	{
		ClsScreenFindClient::FindClientInfo();
	}

	static void _Transactions()
	{
		ClsScreenTransactions::TransactionMenueScreen();
	}

	static void _ManageUsers()
	{
		ClsScreenManageUsers::ShowManageUsersScreen();
	}

	static void _CurrencyExchange()
	{
		ClsShowCurrencyExchange::CurrencyExchangeScreen();
	}

	static void _LogOut()
	{
		CurrentUser = ClsBankUser::Find("", "");
	}

	static void _PerformMainMenueScreen(enMainMenueOptions Choices)
	{
		switch (Choices)
		{
		case ClsShowMainMenueScreen::showClientList:
			system("cls");
			_ShowClientList();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::AddNewClient:
			system("cls");
			_AddNewClient();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::DeleteClient:
			system("cls");
			_DeleteClient();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::UpdateClientInfo:
			system("cls");
			_UpdateClientInfo();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::FindClient:
			system("cls");
			_FindClient();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::Transactions:
			system("cls");
			_Transactions();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::ManageUsers:
			system("cls");
			_ManageUsers();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::LoginRegister:
			system("cls");
			_ShowLoginRegistorScreen();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::CurrencyExchange:
			system("cls");
			_CurrencyExchange();
			_GoBackToMainMenue();
			break;

		case ClsShowMainMenueScreen::LogOut:
			system("cls");
			_LogOut();
			break;
		}
	}

public:
	static void MainMenueScreen()
	{
		system("cls");

		_DrawScreenHeader("\t\t\tMain Menue");

		cout << "============================================\n\n";
		cout << "\tMain Menue Screen\n\n";
		cout << "============================================\n\n";
		cout << "[1] Show Client List.\n";
		cout << "[2] Add New Client.\n";
		cout << "[3] Delete Client.\n";
		cout << "[4] Update Client Info.\n";
		cout << "[5] Find Client.\n";
		cout << "[6] Transactions.\n";
		cout << "[7] Manage Users.\n";
		cout << "[8] Login Register.\n";
		cout << "[9] Currency Exchange.\n";
		cout << "[10] LogOut.\n\n";
		cout << "============================================\n\n";
		_PerformMainMenueScreen(enMainMenueOptions(_ReadMainMenueOption()));
	}
};