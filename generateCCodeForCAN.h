
// generateCCodeForCAN.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CgenerateCCodeForCANApp: 
// �йش����ʵ�֣������ generateCCodeForCAN.cpp
//

class CgenerateCCodeForCANApp : public CWinApp
{
public:
	CgenerateCCodeForCANApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CgenerateCCodeForCANApp theApp;