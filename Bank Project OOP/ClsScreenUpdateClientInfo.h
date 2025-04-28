#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankClient.h"
#include"ClsInputValidate.h"

class ClsScreenUpdateClientInfo:protected ClsScreen
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
public:
    static void UpdateClient()
    {
        if (!CheckAccessRight(ClsBankUser::EnAccessPermission::UpdateClientAccess))
        {
            return;
        }
        
        _DrawScreenHeader("\n\t\t\tUpdate Client Info Screen");
        
        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = ClsInputValidate::ReadString();

        while (!ClsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = ClsInputValidate::ReadString();
        }

        ClsBankClient Client1 = ClsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        cout << "\n\nUpdate Client Info:";
        cout << "\n____________________\n";


        _ReadClientInfo(Client1);

        ClsBankClient::enResults SaveResult;

        SaveResult = Client1.Save();

        switch (SaveResult)
        {
        case  ClsBankClient::enResults::Succeed:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(Client1);
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