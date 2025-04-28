#pragma once

#include<iostream>
#include"ClsBankClient.h"
#include"ClsScreen.h"
#include"ClsInputValidate.h"

using namespace std;

class ClsScreenAddNewClient : protected ClsScreen
{
private:
    static void _ReadClientInfo(ClsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = ClsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.LastName = ClsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.Email = ClsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.Phone = ClsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.PINCODE = ClsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = ClsInputValidate::ReadFloatNumber();
    }

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
    static void AddNewClient()
    {
        if (!CheckAccessRight(ClsBankUser::EnAccessPermission::AddNewClientAccess))
        {
            return;
        }

        _DrawScreenHeader("\n\t\tAdd New Client Screen");
        
        string AccountNumber = "";

        cout << "Enter your account number : ";
        AccountNumber = ClsInputValidate::ReadString();

        while (ClsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nThis account number is already exists , Try again : ";
            AccountNumber = ClsInputValidate::ReadString();
        }

        ClsBankClient NewClient = ClsBankClient::AddNewClient(AccountNumber);

        _ReadClientInfo(NewClient);

        ClsBankClient::enResults SaveResults;

        SaveResults = NewClient.Save();

        switch (SaveResults)
        {
        case  ClsBankClient::enResults::Succeed:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case ClsBankClient::enResults::Faile:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
        }

        }
    }
};

