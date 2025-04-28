#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "Global.h"

using namespace std;

class ClsBankClient : public clsPerson
{
private:

	enum enMode
	{
		EmptyMode = 0,
		UpdateMode = 1,
		AddMode = 2,
		DeleteMode = 3
	};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float  _AccountBalance;
	struct StTransferInfo;

	string _ConverRcordToLine(float Amount, ClsBankClient ClientTo, string UserName, string Seperator = "#//#")
	{
		string Line;

		Line += ClsData::GetSystemDateString() + Seperator;
		Line += GetAccountNumber() + Seperator;
		Line += ClientTo.GetAccountNumber() + Seperator;
		Line += to_string(Amount) + Seperator;
		Line += to_string(AccountBalance) + Seperator;
		Line += to_string(ClientTo.AccountBalance) + Seperator;
		Line += UserName;

		return Line;
	}

	static StTransferInfo _ConvertLineToRecord(string Line, string Seperator = "#//#")
	{
		vector<string>_vTransferInfo = ClsString::Split(Line, Seperator);
		StTransferInfo Info;

		Info.DateTime = _vTransferInfo[0];
		Info.ClientFromAccountNumber = _vTransferInfo[1];
		Info.ClientToAccountNumber = _vTransferInfo[2];
		Info.Amount = stof(_vTransferInfo[3]);
		Info.NewBalanceClientForm = stof(_vTransferInfo[4]);
		Info.NewBalanceClietnTo = stof(_vTransferInfo[5]);
		Info.UserNew = _vTransferInfo[6];

		return Info;
	}
	
	static ClsBankClient _ConvertLineToObject(string Line, string Seperator = "#//#")
	{
		vector<string>_VclientsInfo;
		_VclientsInfo = ClsString::Split(Line, Seperator);

		return ClsBankClient(enMode::UpdateMode, _VclientsInfo[0], _VclientsInfo[1], _VclientsInfo[2],
			_VclientsInfo[3], _VclientsInfo[4], _VclientsInfo[5], stof(_VclientsInfo[6]));
	}

	static string _ConvertObjectToLine(ClsBankClient Client, string Seperator = "#//#")
	{
		string Line = "";
		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.GetAccountNumber() + Seperator;
		Line += Client.PINCODE + Seperator;
		Line += to_string(Client.AccountBalance) + Seperator;

		return Line.substr(0, Line.length() - Seperator.length());
	}

	static vector<ClsBankClient> _LoadClientDataFromFile()
	{
		vector<ClsBankClient>_VclientsInfos;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsBankClient Client = _ConvertLineToObject(Line);
				_VclientsInfos.push_back(Client);
			}

			MyFile.close();
		}

		return _VclientsInfos;
	}

	static vector<StTransferInfo> _GetTransferLogInfo()
	{
		vector<StTransferInfo>_vTransfer;

		fstream MyFile;

		MyFile.open("TransferInfo.txt", ios::out | ios::in);

		if (MyFile.is_open())
		{
			string Line;
			StTransferInfo TransferInfo;

			while (getline(MyFile, Line))
			{
				TransferInfo = _ConvertLineToRecord(Line);
				_vTransfer.push_back(TransferInfo);
			}

			MyFile.close();
		}

		return _vTransfer;
	}

	static void _SaveDataToFile(vector<ClsBankClient>_VclientsInfo)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;

			for (ClsBankClient& C : _VclientsInfo)
			{
				Line = _ConvertObjectToLine(C);
				MyFile << Line << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector<ClsBankClient>Client;
		Client = _LoadClientDataFromFile();

		for (ClsBankClient& C : Client)
		{
			if (C.GetAccountNumber() == GetAccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveDataToFile(Client);
	}

	void _Add()
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			string Line = _ConvertObjectToLine(*this);
			MyFile << Line << endl;

			MyFile.close();
		}
	}

	void _Delete()
	{
		vector<ClsBankClient>Vclient;
		Vclient = _LoadClientDataFromFile();

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			vector<ClsBankClient>NewDataForClient;
			for (ClsBankClient& C : Vclient)
			{
				if (C.GetAccountNumber() != GetAccountNumber())
				{
					NewDataForClient.push_back(C);
				}
			}

			_SaveDataToFile(NewDataForClient);
			*this = _GetAnEmptyObject();
			MyFile.close();
		}

		
	}

	void _SaveTransferInfo(float Amount, ClsBankClient ClientTo, string UserName, string Seperator = "#//#")
	{
		string Line = _ConverRcordToLine(Amount, ClientTo, UserName);

		fstream MyFile;

		MyFile.open("TransferInfo.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;

			MyFile.close();
		}
	}

	static ClsBankClient _GetAnEmptyObject()
	{
		return ClsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	ClsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PINcode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone), _Mode{ Mode },
		_AccountNumber{ AccountNumber }, _AccountBalance{ AccountBalance }, _PinCode{ PINcode } {
	}


	struct StTransferInfo
	{
		string DateTime;
		string ClientFromAccountNumber;
		string ClientToAccountNumber;
		float  Amount;
		float  NewBalanceClientForm;
		float  NewBalanceClietnTo;
		string UserNew;
	};

	// Set & Get For PIN Code
	void SetPINcode(string PINcode)
	{
		_PinCode = PINcode;
	}
	string GetPINcode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPINcode, put = SetPINcode))string PINCODE;

	// Set & Get For AccountBalance
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

	// only Get For Account Number
	string GetAccountNumber()
	{
		return _AccountNumber;
	}

	static ClsBankClient Find(string AccountNumber)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsBankClient Client = _ConvertLineToObject(Line);
				if (Client.GetAccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetAnEmptyObject();
	}

	static ClsBankClient Find(string AccountNumber,string PINCODE)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				ClsBankClient Client = _ConvertLineToObject(Line);
				if (Client.GetAccountNumber() == AccountNumber && Client.PINCODE == PINCODE)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetAnEmptyObject();
	}

	 bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static bool IsClientExist(string AccountNumber)
	{
		ClsBankClient Client = ClsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	enum enResults
	{
		Faile  = 0,
		Succeed = 1
	};

	enResults Save()
	{
		switch (_Mode)
		{
		case ClsBankClient::EmptyMode:
			return enResults::Faile;

		case ClsBankClient::UpdateMode:
			_Update();
			return enResults::Succeed;

		case ClsBankClient::AddMode:
			if (ClsBankClient::IsClientExist(_AccountNumber))
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

		case ClsBankClient::DeleteMode:

			_Delete();
			*this = _GetAnEmptyObject();
			_Mode = enMode::EmptyMode;
			return enResults::Succeed;

		default:
			return enResults::Faile;
			break;
		}
	}

	static ClsBankClient AddNewClient(string AccountNumber)
	{
		return ClsBankClient(enMode::AddMode, "", "", "", "", AccountNumber, "", 0);
	}

	static ClsBankClient DeleteClient(ClsBankClient& Client)
	{
		return ClsBankClient(enMode::DeleteMode, Client.FirstName, Client.LastName, Client.Email,
			Client.Phone, Client.GetAccountNumber(), Client.PINCODE, Client.AccountBalance);
		
	}

	static vector<ClsBankClient> GetClientsList()
	{
		return _LoadClientDataFromFile();
	}

	static float GetTotalBalances()
	{
		float TotalBalances = 0;

		vector<ClsBankClient>vClients = _LoadClientDataFromFile();

		for (ClsBankClient& C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposite(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
		return true;
	}

	bool Transfer(double Amount, ClsBankClient& DestinationClient,string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposite(Amount);
		_SaveTransferInfo(Amount, DestinationClient, UserName);
		return true;
	}

	static vector<StTransferInfo> GetTransferInfo()
	{
		return _GetTransferLogInfo();
	}
};