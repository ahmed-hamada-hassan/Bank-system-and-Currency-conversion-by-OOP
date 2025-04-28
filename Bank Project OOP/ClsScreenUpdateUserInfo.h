#pragma once

#include<iostream>
#include"ClsScreen.h"
#include"ClsBankUser.h"
#include"ClsInputValidate.h"

using namespace std;

class ClsScreenUpdateUserInfo : protected ClsScreen
{
private:

    static void _ReadUserInfo(ClsBankUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = ClsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = ClsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = ClsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = ClsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = ClsInputValidate::ReadString();

        cout << "\nEnter Permissions: ";
        User.Permission = _ReadPermissionToSet();
    }

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

    static short _ReadPermissionToSet()
    {
        short PermissionCounter = 0;
        char Answer = 'n';

        cout << "Do you want to give full access? y/n?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n";

        cout << "\nShow List Client (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::ShowClientAccess;
        }

        cout << "\nShow Login Registor History (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::LoginRegistorHistory;
        }

        cout << "\nAdd New Client (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::AddNewClientAccess;
        }

        cout << "\nDelet Client (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::DeletClientAccess;
        }

        cout << "\nUpdate Client (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::UpdateClientAccess;
        }

        cout << "\nFind Client (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::FindClientAccess;
        }

        cout << "\nTransactions (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::TransactionsAccess;
        }

        cout << "\nManage Users (y/n) ?";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            PermissionCounter += ClsBankUser::EnAccessPermission::ManageUsersAccess;
        }

        return PermissionCounter;
    }

public:

    static void UpdateUser()
    {
        _DrawScreenHeader("\n\t\t\tUpdate Client Info Screen");

        string UserName = "";

        cout << "\nPlease Enter User Name : ";
        UserName = ClsInputValidate::ReadString();

        while (!ClsBankUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = ClsInputValidate::ReadString();
        }

        ClsBankUser User = ClsBankUser::Find(UserName);
        _PrintUser(User);

        cout << "\n\nUpdate User Info:";
        cout << "\n____________________\n";


        _ReadUserInfo(User);

        ClsBankUser::enResults SaveResult;

        SaveResult = User.Save();

        switch (SaveResult)
        {
        case  ClsBankUser::enResults::Succeed:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintUser(User);
            break;
        }
        case ClsBankUser::enResults::Faile:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }

        }
    }
};

