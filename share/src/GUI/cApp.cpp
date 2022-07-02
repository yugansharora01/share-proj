#include "pch.h"
#include "cApp.h"
#include "Manager.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{

	Manager m;
	m.make("TIME_SERIES_DAILY", "TATAPOWER.BSE", "compact");
	

	m_frame1 = new cMain();
	m_frame1->Show();

	return true;
}
