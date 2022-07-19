#include "pch.h"
#include "cMain.h"
#include "Util/JsonParser.h"
#include "Manager.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"App",wxPoint(100,100),wxSize(800,600), wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN )
{
	std::ifstream file;
	file.open("imageName.txt");
	std::string line;
	std::getline(file, line);
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(line, wxBITMAP_TYPE_PNG), wxPoint(50, 100), wxSize(800, 500));

	createSymbolMap();
	wxArrayString choices;
	for (auto i = symbols.begin(); i != symbols.end(); i++)
	{
		choices.push_back(i->first);
	}

	std::string str = choices[0].ToStdString();
	wxArrayString choices1;
	for (int i = 0; i < 5; i++)
	{
		auto it = symbols[str].begin();
		std::advance(it, i);
		choices1.push_back(it->first);
	}

	exchangeDropdown = new wxComboBox(this, wxID_ANY, wxEmptyString, wxPoint(350, 10), wxSize(100, 20), choices);
	exchangeDropdown->SetValue(choices[0]);

	search = new wxComboBox(this, wxID_ANY, wxEmptyString, wxPoint(10, 10), wxSize(200, 30), choices1, wxTE_PROCESS_ENTER);

	search->Bind(wxEVT_TEXT, &cMain::OnTxtChangeInSearchBar, this);
	search->Bind(wxEVT_TEXT_ENTER, &cMain::OnTxtEnterInSearchBar, this);


	wxGridBagSizer* sizer = new wxGridBagSizer();
	sizer->Add(search,wxGBPosition(1,10),wxGBSpan(3,20), wxALL);
	sizer->Add(exchangeDropdown, wxGBPosition(1, 35), wxGBSpan(2, 10), wxALL);
	sizer->Add(image,wxGBPosition(10,3),wxGBSpan(50,80), wxALL);
	this->SetSizer(sizer);
	
}

cMain::~cMain()
{
}

void cMain::RefreshDashboard(std::string companyName,std::string symbol)
{
	if (companyName != getCurrentCompany())
	{
		Manager m;
		m.make(symbol, "2021-07-06", "2022-07-06");
	}
}

std::string cMain::getCurrentCompany()
{
	std::ifstream file;
	file.open("imageName.txt");
	std::string line;
	std::getline(file, line);
	std::filesystem::path p(line);
	line = p.filename().string();
	int i;
	for (i = 0; i < line.size(); i++)
	{
		if (line[i] == '_')
			break;
	}

	return line.substr(0,i);
}

void cMain::createSymbolMap()
{
	JsonParser j;
	j.GetMapofData("src/Assets/symbols/IndiajsonSymbols.json",symbols);
	for (auto i = symbols.begin(); i != symbols.end(); i++)
		symbols[i->first].erase("");

	int depth = searchDepth;
	for (auto i = symbols.begin(); i != symbols.end(); i++)
	{
		//In future there will be something which will fill up the information, till then just deleting the empty entries
		symbols[i->first].erase(""); 
		std::string prevstr;
		int index = 0;
		for (auto j = symbols[i->first].begin(); j != symbols[i->first].end(); j++)
		{
			if (j->first.find("tata p") != std::string::npos)
			{
				std::cout << "LOL";
			}
			for (int k = 0; k < depth; k++)
			{
				
				if (j->first.size() > k) // insert only if the string is long enough to call j->first[k]
				{
					if (prevstr.size() <= k)
					{
						mapOfStrings[i->first].insert({ j->first.substr(0,k+1),index });
					}
					else
					{
						if (prevstr[k] != j->first[k])
						{
							mapOfStrings[i->first].insert({ j->first.substr(0,k+1),index });
						}
					}
				}
				

			}
			prevstr = j->first.substr(0, depth);
			index++;
		}
		
	}
}



void cMain::OnTxtChangeInSearchBar(wxCommandEvent& event)
{
	int depth = searchDepth,index = 0,nextIndex = 0;
	std::string searchstr = search->GetValue().ToStdString();
	for (int i = 0; i < searchstr.length(); i++)
	{
		searchstr[i] = std::tolower(searchstr[i]);
	}
	std::string exchange = exchangeDropdown->GetValue().ToStdString();
	std::string str = searchstr.substr(0, depth);
	for (int i = 0; i < depth; i++)
	{
		auto it = mapOfStrings[exchange].find(str);
		if (it != mapOfStrings[exchange].end())
		{
			index = it->second;
			break;
		}
		if(!str.empty())
			str.pop_back();
	}

	auto it = symbols[exchange].begin();
	std::advance(it, index);

	// the index might become more accurate (for the characters after the depth)
	if (str == searchstr.substr(0, depth) && searchstr.size() > depth)
	{
		
		while (nextIndex == 0)
		{
			std::multimap<std::string, int>::iterator k;
			//for(int )
			if (str[depth - 1] != 'z')
			{
				str[depth - 1] = str[depth - 1] + 1;
				k = mapOfStrings[exchange].find(str);
			}
			else
			{
				if (depth - 1 != 0)
				{
					depth--;
					str[depth - 1] = str[depth - 1] + 1;
					k = mapOfStrings[exchange].find(str);
				}
				else
				{
					k = mapOfStrings[exchange].end();
				}
			}
			
			if (k != mapOfStrings[exchange].end())
			{
				nextIndex = k->second;
			}
			else
			{
				if(depth == 0)
					nextIndex = symbols[exchange].size() - 1;
			}
		}
		
		auto iterator = symbols[exchange].begin();
		std::advance(iterator, nextIndex);


		for (auto j = it; j != iterator; j++)
		{
			auto i = j->first.find(searchstr);
			if (i != std::string::npos)
			{
				it = j;
				break;
			}
		}
		
	}

	for (int i = 0; i < 5; i++)
	{
		search->SetString(i, it->first);
		it++;
	}
	
}

void cMain::OnTxtEnterInSearchBar(wxCommandEvent& event)
{
	std::string value = search->GetValue().ToStdString();
	std::string exchange = exchangeDropdown->GetValue().ToStdString();
	auto it = symbols[exchange].find(value);
	if (it != symbols[exchange].end())
	{
		RefreshDashboard(it->first,it->second);
	}
}


