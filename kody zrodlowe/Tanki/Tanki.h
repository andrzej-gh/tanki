// Tanki.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/**
* \file Tani.h
* \author Ró¿añski Piotr
* \author Wilczyñski Andrzej
* \author Witkowski Stefan
* \date 21-06-2007
*/


// CTankiApp:
// See Tanki.cpp for the implementation of this class
//
///klasa glowna programu
class CTankiApp : public CWinApp
{


public:
	CTankiApp();
// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};
extern CTankiApp theApp;