#include "pch.h"
#include "ApiFiles/yfapi.h"
#include "cApp.h"
#include "Manager.h"
#include "Util/JsonParser.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
	if (!std::filesystem::exists("src/Assets/symbols/INDIAData.json"))
	{
		//Generate 
		system("python src/Python/SymbolGenerator.py");

		JsonParser j;
		j.parseFromFile("src/Assets/symbols/INDIAData.json", "src/Assets/symbols/IndiaSymbols.txt");
		j.parseFromFile("src/Assets/symbols/USData.json", "src/Assets/symbols/UsSymbols.txt");
	}
	
	Manager m;
	m.make("TATAPOWER.NS", "2021-07-06", "2022-07-06");
	

	m_frame1 = new cMain();
	m_frame1->Show();

	return true;
}
