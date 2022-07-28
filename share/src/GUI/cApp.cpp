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
	console = new Console();
	console->Show();
	createData();
	m_frame1 = new DashBoard();
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
		if (ret != "OK")
			console->add(LogType::ERROR_STRING,ret);
		//j.parseFromFile("src/Assets/symbols/USData.json", "src/Assets/symbols/UsjsonSymbols.txt");
	}

	//In future it will read some file and generate the dashboard according to that
	Manager m;
	m.make("TATAPOWER.NS", "2021-07-06", "2022-07-06");
}
