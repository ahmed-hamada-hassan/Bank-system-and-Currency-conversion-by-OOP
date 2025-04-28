#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankClient.h"
#include"ClsInputValidate.h"
#include"ClsScreen.h"
#include"ClsScreenDeposite.h"
#include"ClsScreenWithdraw.h"
#include"ClsScreenTotalBalances.h"
#include"ClsScreenTransfer.h"
#include"ClsScreenLogTransferInfo.h"

using namespace std;

class ClsScreenTransactions : protected ClsScreen
{
private:

	enum enTransactionsScreenOptions
	{
		Deposite = 1,
		WithDraw = 2,
		TotalBalances = 3,
		Transfer = 4,
		LogTransferInfo = 5,
		MainMenue = 6
	};

	static short _ReadTransactionsMenueOption()
	{
		cout << "Choose what you want from [1 to 6] : ";
		short Choice = ClsInputValidate::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6 : ");
		return Choice;
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\t\t\tPress any key to go back to Transactions Menue...\n";
		system("pause>0");
		TransactionMenueScreen();
	}

	static void _DepositeScreen()
	{
		ClsScreenDeposite::ShowDepositeScreen();
	}

	static void _WithdrawScreen()
	{
		ClsScreenWithdraw::ShowWithdrawScreen();
	}

	static void _TotalBalancesScreen()
	{
		ClsScreenTotalBalances::ShowTotalBalances();
	}

	static void _TransferScreen()
	{
		ClsScreenTransfer::TransferScreen();
	}

	static void _TransferLogInfo()
	{
		ClsScreenLogTransferInfo::_ShowTransferLogInfo();
	}

	static void _PerformTransactionsMenueScreen(enTransactionsScreenOptions Choice)
	{
		switch (Choice)
		{
		case ClsScreenTransactions::Deposite:
			system("cls");
			_DepositeScreen();
			_GoBackToTransactionsMenue();
			break;

		case ClsScreenTransactions::WithDraw:
			system("cls");
			_WithdrawScreen();
			_GoBackToTransactionsMenue();
			break;

		case ClsScreenTransactions::TotalBalances:
			system("cls");
			_TotalBalancesScreen();
			_GoBackToTransactionsMenue();
			break;

		case ClsScreenTransactions::Transfer:
			system("cls");
			_TransferScreen();
			_GoBackToTransactionsMenue();
			break;

		case ClsScreenTransactions::LogTransferInfo:
			system("cls");
			_TransferLogInfo();
			_GoBackToTransactionsMenue();

		case ClsScreenTransactions::MainMenue:
			
			break;
		}
	}

public:

	static void TransactionMenueScreen()
	{
		system("cls");

		if (!CheckAccessRight(ClsBankUser::EnAccessPermission::TransactionsAccess))
		{
			return;
		}
		
		_DrawScreenHeader("\t\t\tTransactios Menue");

		cout << "============================================\n\n";
		cout << "\tTransactios Menue\n\n";
		cout << "============================================\n\n";
		cout << "[1] Deposite.\n";
		cout << "[2] Withdraw.\n";
		cout << "[3] Total Balances.\n";
		cout << "[4] Transfer.\n";
		cout << "[5] Transfer Log Info.\n";
		cout << "[6] Main Menue.\n";
		cout << "============================================\n\n";
		_PerformTransactionsMenueScreen(enTransactionsScreenOptions(_ReadTransactionsMenueOption()));
	}
};

