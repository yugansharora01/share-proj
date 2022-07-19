#include "pch.h"
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
	createData();
	m_frame1 = new cMain();
	

	m_frame1->Show();

	return true;
}

void cApp::createData()
{
	if (!std::filesystem::exists("src/Assets/symbols/IndiajsonSymbols.json"))
	{
		//Generate 
		if (!std::filesystem::exists("src/Assets/symbols/INDIAData.json"))
			system("python src/Python/SymbolGenerator.py");

		JsonParser j;
		std::string ret = j.parseFromFile("src/Assets/symbols/INDIAData.json", "src/Assets/symbols/IndiajsonSymbols.json");
		//if (ret != "OK")
			//m_frame1->t->SetValue(ret);
		//j.parseFromFile("src/Assets/symbols/USData.json", "src/Assets/symbols/UsSymbols.txt");
	}

	//In future it will read some file and generate the dashboard according to that
	Manager m;
	m.make("TATAPOWER.NS", "2021-07-06", "2022-07-06");
}
