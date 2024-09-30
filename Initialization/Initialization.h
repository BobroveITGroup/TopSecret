#pragma once

#include<windows.h>

class Initialization
{
public:

	HRESULT Get_System_Parameters();
	void	Create_and_write_parameters();

	//wchar_t* name_CPU, name_GPU, monitor_width, monitor_height;
	

	Initialization()
	{
		Get_System_Parameters();
	}

};

