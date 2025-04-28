#pragma once

#include<iostream>
#include"ClsBankUser.h"
#include"Global.h"
#include"ClsData.h"

using namespace std;

class ClsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\n____________________________________________________________\n";
		cout << endl << Title;
		if(SubTitle!="")
			cout << "\n" << SubTitle;
		cout << "\n\n____________________________________________________________\n\n";

		cout << "\n\t\tUser : " << CurrentUser.UserName ;
		cout << "\t\tDate : "; ClsData().Print(); cout << endl << endl;
	}

	static bool CheckAccessRight(ClsBankUser::EnAccessPermission HavePermission)
	{
		if (!CurrentUser.CheckIfHavePermissionOrNo(HavePermission))
		{
			_DrawScreenHeader("\n\t\tAccess Denied! Contact your Admin\n");
			return false;
		}
		else
		{
			return true;
		}
	}
};

