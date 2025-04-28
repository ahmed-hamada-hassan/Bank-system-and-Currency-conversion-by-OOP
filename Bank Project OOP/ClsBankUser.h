#pragma once

#include<iostream>
#include"ClsPerson.h"
#include"ClsInputValidate.h"
#include"fstream"
#include<vector>
#include"ClsUtility.h"

using namespace std;

class ClsBankUser : public clsPerson
{
private:

	enum enMode
	{
		EmptyMode = 1,
		UpdateMode = 2,
		AddMode = 3,
		DeleteMode = 4,
	};

	struct StLoginRegistorInfo;
	enMode _Mode;
	string _UserName;
	string _Password;
	short _Permission;

	static ClsBankUser _ConvertLineToObject(string Line, string Seperator = "#//#")
	{
		vector<string>_VuserssInfo;
		_VuserssInfo = ClsString::Split(Line, Seperator);

		return ClsBankUser(enMode::UpdateMode, _VuserssInfo[0], _VuserssInfo[1], _VuserssInfo[2],
			_VuserssInfo[3], _VuserssInfo[4], ClsUtility::Decryption(_VuserssInfo[5]) , stoi(_VuserssInfo[6]));
	}

	static StLoginRegistorInfo _ConvertLoginLineToRecord(string Line, string Seperator = "#//#")
	{
		vector<string>_VloginInfo = ClsString::Split(Line, Seperator);

		StLoginRegistorInfo LoginInfo;

		LoginInfo.DateTime = _VloginInfo[0];
		LoginInfo.UserName = _VloginInfo[1];
		LoginInfo.Password = ClsUtility::Decryption(_VloginInfo[2]);
		LoginInfo.Permission = stoi(_VloginInfo[3]);

		return LoginInfo;
	}

	static string _ConvertObjectToLine(ClsBankUser User, string Seperator = "#//#")
	{
		string Line = "";
		Line += User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User.UserName + Seperator;
		Line += ClsUtility::Encryption(User.Password) + Seperator;
		Line += to_string(User.Permission) + Seperator;

		return Line.substr(0, Line.length() - Seperator.length());
	}

	static vector<ClsBankUser> _LoadUserDataFromFile()
	{
		vector<ClsBankUser>_VuseresInfos;

		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsBankUser User = _ConvertLineToObject(Line);
				_VuseresInfos.push_back(User);
			}

			MyFile.close();
		}

		return _VuseresInfos;
	}

	static void _SaveDataToFile(vector<ClsBankUser>_VuseresInfos)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;

			for (ClsBankUser& C : _VuseresInfos)
			{
				Line = _ConvertObjectToLine(C);
				MyFile << Line << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector<ClsBankUser>User;
		User = _LoadUserDataFromFile();

		for (ClsBankUser& C : User)
		{
			if (C.UserName == UserName)
			{
				C = *this;
				break;
			}
		}

		_SaveDataToFile(User);
	}

	void _Add()
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			string Line = _ConvertObjectToLine(*this);
			MyFile << Line << endl;

			MyFile.close();
		}
	}

	void _Delete()
	{
		vector<ClsBankUser>Vuser;
		Vuser = _LoadUserDataFromFile();

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			vector<ClsBankUser>NewDataForUser;
			for (ClsBankUser& C : Vuser)
			{
				if (C.UserName != UserName)
				{
					NewDataForUser.push_back(C);
				}
			}

			_SaveDataToFile(NewDataForUser);
			*this = _GetAnEmptyObject();
			MyFile.close();
		}
	}

	string _RegisterLogInFile(string Seperator = "#//#")
	{
		string Line = "";

		Line += ClsData::GetSystemDateString() + Seperator;
		Line += UserName + Seperator;
		Line += ClsUtility::Encryption(Password) + Seperator;
		Line += to_string(Permission);

		return Line;
	}

	static ClsBankUser _GetAnEmptyObject()
	{
		return ClsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	ClsBankUser(enMode Mode , string FirstNmae,string LastName,string Email,string Phone,string UserName,
		string Password,short Permission):clsPerson(FirstNmae,LastName,Email,Phone),_Mode{Mode},
		_UserName{UserName},_Password{Password},_Permission{Permission}{ }


	struct StLoginRegistorInfo
	{
		string DateTime;
		string UserName;
		string Password;
		short Permission = 0;
	};


	enum EnAccessPermission
	{
		AllAccess = -1, ShowClientAccess = 1,
		AddNewClientAccess = 2, DeletClientAccess = 4,
		UpdateClientAccess = 8, FindClientAccess = 16,
		TransactionsAccess = 32, ManageUsersAccess = 64,
		LoginRegistorHistory = 128
	};

	// Set & Get for User Name
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName))string UserName;

	// Set & Get for Password
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword))string Password;

	// Set & Get for Permission
	void SetPermission(short Permission)
	{
		_Permission = Permission;
	}
	short GetPermission()
	{
		return _Permission;
	}
	__declspec(property(get = GetPermission, put = SetPermission))short Permission;

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static ClsBankUser Find(string UserName)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsBankUser User = _ConvertLineToObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetAnEmptyObject();
	}

	static ClsBankUser Find(string UserName, string Password)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsBankUser User = _ConvertLineToObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetAnEmptyObject();
	}

	static bool IsUserExist(string UserName)
	{
		ClsBankUser Client = ClsBankUser::Find(UserName);
		return (!Client.IsEmpty());
	}

	enum enResults
	{
		Faile = 0,
		Succeed = 1
	};

	enResults Save()
	{
		switch (_Mode)
		{
		case ClsBankUser::EmptyMode:
			return enResults::Faile;

		case ClsBankUser::UpdateMode:
			_Update();
			return enResults::Succeed;

		case ClsBankUser::AddMode:
			if (ClsBankUser::IsUserExist(_UserName))
			{
				return enResults::Faile;
			}
			else
			{
				_Add();
				_Mode = enMode::UpdateMode;
				return enResults::Succeed;
			}
			break;

		case ClsBankUser::DeleteMode:

			_Delete();
			*this = _GetAnEmptyObject();
			_Mode = enMode::EmptyMode;
			return enResults::Succeed;

		default:
			return enResults::Faile;
			break;
		}
	}

	static ClsBankUser AddNewUser(string UserName)
	{
		return ClsBankUser(enMode::AddMode, "", "", "", "", UserName, "", 0);
	}

	static ClsBankUser DeleteUser(ClsBankUser& User)
	{
		return ClsBankUser(enMode::DeleteMode, User.FirstName, User.LastName, User.Email,
			User.Phone, User.UserName, User.Password, User.Permission);
	}

	static vector<ClsBankUser> GetUserList()
	{
		return _LoadUserDataFromFile();
	}

	 bool CheckIfHavePermissionOrNo(EnAccessPermission HavePermission)
	{


		if (this->Permission == EnAccessPermission::AllAccess)
			return true;

		else if ((HavePermission & this->Permission) == HavePermission)
			return true;

		else
			return false;
	}

	 void RegisterLogIn()
	 {
		 string Line = _RegisterLogInFile();

		 fstream MyFile;

		 MyFile.open("LoginFile.txt", ios::out | ios::app);

		 if (MyFile.is_open())
		 {
		
			 MyFile << Line << endl;

			 MyFile.close();
			
		 }
	 }

	 static  vector<StLoginRegistorInfo> GetLoginInfo()
	 {
		 vector<StLoginRegistorInfo>VusersLoginInfo;

		 fstream MyFile;

		 MyFile.open("LoginFile.txt", ios::in);

		 if (MyFile.is_open())
		 {
			 string Line;

			 StLoginRegistorInfo LoginLine;

			 while (getline(MyFile, Line))
			 {
				 LoginLine = _ConvertLoginLineToRecord(Line);
				 VusersLoginInfo.push_back(LoginLine);
			 }

			 MyFile.close();
		 }

		 return VusersLoginInfo;
	}
};

