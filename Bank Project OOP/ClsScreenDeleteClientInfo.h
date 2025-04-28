#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankClient.h"
#include"ClsInputValidate.h"

using namespace std;

class ClsScreenDeleteClientInfo : protected ClsScreen
{
private:
    static void _PrintClient(ClsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.PINCODE;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";


    }
   
public:
    static void DeleteClient()
    {
        if (!CheckAccessRight(ClsBankUser::EnAccessPermission::DeletClientAccess))
        {
            return;
        }
        
        _DrawScreenHeader("\n\t\t\tDelete Client Screen");
        
        string AccountNumber = "";

        cout << "Enter your Account Number : ";
        getline(cin >> ws, AccountNumber);

        while (!ClsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nThis Account isn't existed , Try again : ";
            getline(cin >> ws, AccountNumber);
        }

        ClsBankClient Client = ClsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Answer = 'n';

        cout << "Are you sure for deleteing this account number ? (y/n)? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client = ClsBankClient::DeleteClient(Client);
            ClsBankClient::enResults SaveResults;

            SaveResults = Client.Save();

            switch (SaveResults)
            {
            case ClsBankClient::enResults::Succeed:
                cout << "\n\nThis Client deleted successfully.";
                _PrintClient(Client);
                break;

            case ClsBankClient::enResults::Faile:
                cout << "\n\nThis client isn't deleted.";
                break;
            }
        }
    }
};

