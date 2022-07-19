#pragma once
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();
	virtual bool OnInit();
	void createData();

private:
	cMain* m_frame1 = nullptr;
};