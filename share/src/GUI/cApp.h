#pragma once
#include "DashBoard.h"
#include "Console.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();
	virtual bool OnInit();
	void createData();

private:
	DashBoard* m_frame1 = nullptr;
	Console* console = nullptr;
};