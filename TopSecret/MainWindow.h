#pragma once

#include<Windows.h>

#include<d2d1.h>
#include<dwrite.h>

#include"D:\Work_Misha\Programing\Chill_Cloud\TopSecret\BaseWindow\BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{

public:
	PCWSTR ClassName() const { return L"Main window class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wPara, LPARAM lParam);
};

