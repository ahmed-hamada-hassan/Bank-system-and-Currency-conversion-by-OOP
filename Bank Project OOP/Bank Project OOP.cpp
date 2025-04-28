#include <iostream>
#include"ClsLoginScreen.h"

int main()
{
    while (true)
    {
        if (!ClsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    return 0;
}