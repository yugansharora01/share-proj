#include "pch.h"
#include "ApiFiles/yfapi.h"
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
	m.make("TATAPOWER.NS", "2021-07-06", "2022-07-06");
	

	m_frame1 = new cMain();
	m_frame1->Show();

	return true;
}
