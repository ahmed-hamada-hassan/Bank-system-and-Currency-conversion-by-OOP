#pragma once

#include<iostream>
#include"ClsBankClient.h"
#include"Global.h"
#include"ClsInputValidate.h"
#include"iomanip"
#include"ClsScreen.h"

using namespace std;

class ClsScreenLogTransferInfo : protected ClsScreen
{
private:

	static void _PrintTransferIfo(ClsBankClient::StTransferInfo TransferInfo)
	{
		cout<< "|" << left << setw(25) << TransferInfo.DateTime;
		cout<< "|" << left << setw(10) << TransferInfo.ClientFromAccountNumber;
		cout<< "|" << left << setw(10) << TransferInfo.ClientToAccountNumber;
		cout<< "|" << left << setw(16) << TransferInfo.Amount;
		cout<< "|" << left << setw(16) << TransferInfo.NewBalanceClientForm;
		cout<< "|" << left << setw(16) << TransferInfo.NewBalanceClietnTo;
		cout<< "|" << left << setw(10) << TransferInfo.UserNew;
	}

public:

	static void _ShowTransferLogInfo()
	{
		vector<ClsBankClient::StTransferInfo>VtransferInfo = ClsBankClient::GetTransferInfo();
		string Title = "\n\t\t\tTransfer Log Screen\n";
		string SubTitle = "\n\t\t\t(" + to_string(VtransferInfo.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\n--------------------------------------------------------------------";
		cout << "----------------------------------------------------\n\n";
		cout<< "|" << left << setw(25) << "Date / Time";
		cout<< "|" << left << setw(10) << "S.Acc";
		cout<< "|" << left << setw(10) << "D.Acc";
		cout<< "|" << left << setw(16) << "Amount";
		cout<< "|" << left << setw(16) << "S.Balance";
		cout<< "|" << left << setw(16) << "D.Balance";
		cout<< "|" << left << setw(10)  << "User Name";
		cout << "\n\n--------------------------------------------------------------------";
		cout << "----------------------------------------------------\n\n";

		if (VtransferInfo.size() == 0)
		{
			cout << "\n\t\tThere aren't any records\n\n";
		}
		else
		{
			for (ClsBankClient::StTransferInfo& T : VtransferInfo)
			{
				_PrintTransferIfo(T);
				cout << endl;
			}

			cout << "\n\n--------------------------------------------------------------------";
			cout << "----------------------------------------------------\n\n";
		}
	}
};

