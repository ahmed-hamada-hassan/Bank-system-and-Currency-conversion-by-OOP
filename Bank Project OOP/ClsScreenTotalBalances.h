#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankClient.h"
#include"ClsUtility.h"
#include<iomanip>

using namespace std;

class ClsScreenTotalBalances : protected ClsScreen
{
private:
    static void _PrintClientRecord(ClsBankClient Client)
    {
        cout << "|" << left << setw(15) << Client.GetAccountNumber();
        cout << "|" << left << setw(20) << Client.FullName();
        cout << "|" << left << setw(12) << Client.AccountBalance;
    }

public:

    static void ShowTotalBalances()
    {
        vector<ClsBankClient>vClients = ClsBankClient::GetClientsList();
        
        string Title = "\n\t\tTotal Balances Screen";
        string SubTitles = "\n\t\t(" + to_string(vClients.size()) + ") client(s)\n";

        _DrawScreenHeader(Title, SubTitles);

        cout << "\n---------------------------------------------------------------------";
        cout << "----------------------\n";
        cout << "|" << left << setw(15) << "Account Number";
        cout << "|" << left << setw(20) << "Client Name";
        cout << "|" << left << setw(12) << "Balance";
        cout << "\n---------------------------------------------------------------------";
        cout << "----------------------\n";

        float TotalBalances = ClsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\t\tNo Clients Available In The System !\n";
        else
        {
            for (ClsBankClient& C : vClients)
            {
                _PrintClientRecord(C);
                cout << endl;
            }
        }
        cout << "---------------------------------------------------------------------";
        cout << "----------------------\n";
        cout << "\n\t\t\t\tTotal Balances = " << TotalBalances << endl;
        cout << "\t\t\t(" << ClsUtility::NumberToText(TotalBalances) << ")\n";
    }
};