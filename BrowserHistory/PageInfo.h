#include <atlstr.h>
#include <ATLComTime.h>

using namespace ATL;

#pragma once
class PageInfo
{
public:
	PageInfo(void);
	~PageInfo(void);

	CString outputPath;
	COleDateTime outputDate;
	COleDateTime lastAccessed;
};

