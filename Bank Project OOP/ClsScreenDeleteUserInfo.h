#pragma once

#include<iostream>
#include"ClsScreenAddNewClient.h"
#include"ClsInputValidate.h"
#include"ClsBankUser.h"

using namespace std;

class ClsScreenDeleteUserInfo : protected ClsScreen
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

    static void DeleteClient()
    {
        _DrawScreenHeader("\n\t\t\tDelete User Screen");

        string UserName = "";

        cout << "Enter your User Name : ";
        getline(cin >> ws, UserName);

        while (!ClsBankUser::IsUserExist(UserName))
        {
            cout << "\nThis User Name isn't existed , Try again : ";
            getline(cin >> ws, UserName);
        }

        ClsBankUser User = ClsBankUser::Find(UserName);
        _PrintUser(User);

        char Answer = 'n';

        cout << "Are you sure for deleteing this account number ? (y/n)? ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            User = ClsBankUser::DeleteUser(User);
            ClsBankUser::enResults SaveResults;

            SaveResults = User.Save();

            switch (SaveResults)
            {
            case ClsBankUser::enResults::Succeed:
                cout << "\n\nThis Client deleted successfully.";
                _PrintUser(User);
                break;

            case ClsBankUser::enResults::Faile:
                cout << "\n\nThis client isn't deleted.";
                break;
            }
        }
    }

};

