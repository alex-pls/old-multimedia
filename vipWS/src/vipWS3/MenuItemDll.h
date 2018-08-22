#pragma once

#include "loaderDLL.h"


	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Collections;


namespace vipWS3
{
	__gc class MenuItemDll : public System::Windows::Forms::MenuItem
	{
	public:
//		MenuItemDll(void)
//		{
//			InitializeComponent();
//		}
	//	~MenuItemDll(void);

		MenuItemDll(System::String * text) : MenuItem(text)
		{
//ciao
		}


	public: loaderDLL* myObject;
	};
}