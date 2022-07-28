#include "pch.h"
#include "DashBoard.h"
#include "Util/JsonParser.h"
#include "Manager.h"

wxBEGIN_EVENT_TABLE(DashBoard, wxFrame)

wxEND_EVENT_TABLE()


DashBoard::DashBoard() : wxFrame(nullptr,wxID_ANY,"App",wxPoint(100,100),wxSize(800,600), wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN | wxVSCROLL)
{
	std::ifstream file;
	file.open("imageName.txt");
	std::string line;
	std::getline(file, line);
	auto handler = wxImage::FindHandler(wxBITMAP_TYPE_PNG);
	if (!handler)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
	}
	image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(line, wxBITMAP_TYPE_PNG), wxPoint(50, 100), wxSize(800, 500));

	createSymbolMap();
	wxArrayString choices;
	for (auto i = symbols.begin(); i != symbols.end(); i++)
	{
		choices.push_back(i->first);
	}

	std::string str = choices[0].ToStdString();
	wxArrayString choices1;
	std::vector<std::string> list;
	auto it = symbols[str].begin();
	for (int i = 0; i < 5; i++)
	{
		choices1.push_back(it->first);
		list.push_back(it->first);
		it++;
	}

	exchangeDropdown = new wxComboBox(this, wxID_ANY, wxEmptyString, wxPoint(350, 10), wxSize(100, 20), choices);
	exchangeDropdown->SetValue(choices[0]);

	search = new wxComboBox(this, wxID_ANY, wxEmptyString, wxPoint(10, 10), wxSize(200, 30), choices1, wxTE_PROCESS_ENTER);
	search->AutoComplete(NULL);
	search->Bind(wxEVT_TEXT, &DashBoard::OnTxtChangeInSearchBar, this);
	search->Bind(wxEVT_TEXT_ENTER, &DashBoard::OnTxtEnterInSearchBar, this);
	search->Bind(wxEVT_COMBOBOX_DROPDOWN, &DashBoard::OnDropDown, this);

	searchBar = new SearchBar(this, wxID_ANY, wxPoint(50, 50), wxSize(200, 20));
	searchBar->setList(list);
	searchBar->BindEvent(EVENT::TEXT, std::bind(&DashBoard::OnTxtChangeInSearchBar1, this));
	searchBar->BindEvent(EVENT::TEXT_ENTER, std::bind(&DashBoard::OnTxtEnterInSearchBar1, this));

	wxGridBagSizer* sizer = new wxGridBagSizer();
	sizer->Add(search,wxGBPosition(1,10),wxGBSpan(3,20), wxALL);
	sizer->Add(exchangeDropdown, wxGBPosition(1, 35), wxGBSpan(2, 10), wxALL);
	sizer->Add(image,wxGBPosition(10,3),wxGBSpan(50,80), wxALL);
	this->SetSizer(sizer);
	
}

DashBoard::~DashBoard()
{
	search->Destroy();
	exchangeDropdown->Destroy();
	image->Destroy();
	delete searchBar;
}

void DashBoard::RefreshDashboard(std::string companyName,std::string symbol)
{
	if (companyName != getCurrentCompany())
	{
		Manager m;
		m.make(symbol, "2021-07-06", "2022-07-06");
		std::ifstream file;
		file.open("imageName.txt");
		std::string line;
		std::getline(file, line);
		auto handler = wxImage::FindHandler(wxBITMAP_TYPE_PNG);
		if (!handler)
		{
			wxPNGHandler* handler = new wxPNGHandler;
			wxImage::AddHandler(handler);
		}
		image->SetBitmap(wxBitmap(line, wxBITMAP_TYPE_PNG));
	}
}

std::string DashBoard::getCurrentCompany()
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

void DashBoard::createSymbolMap()
{
	JsonParser j;
	j.GetMapofData("src/Assets/symbols/IndiajsonSymbols.json",symbols);
	for (auto i = symbols.begin(); i != symbols.end(); i++)
		symbols[i->first].erase("");

	for (auto i = symbols.begin(); i != symbols.end(); i++)
	{
		int index = 0;
		for (auto j = symbols[i->first].begin(); j != symbols[i->first].end(); j++)
		{
			std::string companyName = j->first;
			for (int i = 0; i < companyName.length(); i++)
			{
				companyName[i] = std::tolower(companyName[i]);
			}

			std::vector<std::string> wordList;

			std::stringstream ss(companyName);
			std::string item;
			while (std::getline(ss, item, ' ')) 
			{
				wordList.push_back(item);
			}
			for (int k = 0; k < wordList.size(); k++)
			{
				std::shared_ptr<Node> node;
				if (!nodeTree.contains(i->first))
				{
					std::shared_ptr<Node> temp = std::make_shared<Node>();
					nodeTree.insert({ i->first,temp });
				}
				node = nodeTree[i->first];

				for (int x = 0; x < wordList[k].size(); x++)
				{
					char ch = wordList[k].at(x);
					ch = std::tolower(ch);
					if (!node->nodes.contains(ch))
					{
						std::shared_ptr<Node> temp = std::make_shared<Node>(node->str + ch);
						//temp->setChar(node->str + ch);
						node->nodes.insert({ ch,temp });
					}

					node = node->nodes[ch];
					if (node->indices.size() <= k)
					{
						node->indices.resize(k + 1);
					}
					node->indices[k].push_back(index);
				}
			}

			index++;
		}
	}
}

void DashBoard::OnTxtChangeInSearchBar(wxCommandEvent& event)
{
	int depth = searchDepth,index = 0,nextIndex = 0;
	std::string searchstr = search->GetValue().ToStdString();
	for (int i = 0; i < searchstr.length(); i++)
	{
		searchstr[i] = std::tolower(searchstr[i]);
	}
	std::string exchange = exchangeDropdown->GetValue().ToStdString();

	std::vector<std::string> wordList;

	std::stringstream ss(searchstr);
	std::string item;
	while (std::getline(ss, item, ' '))
	{
		wordList.push_back(item);
	}

	std::vector<int> indices;

	for (std::vector<std::string>::iterator word = wordList.begin(); word != wordList.end(); word++)
	{
		std::shared_ptr<Node> node;
		node = nodeTree[exchange];
		for (int x = 0; x < word->size(); x++)
		{
			char ch = word->at(x);
			if (!node->nodes.contains(ch))
			{
				break;
			}
			node = node->nodes[ch];
		}
		for (auto it = node->indices.begin(); it != node->indices.end(); it++)
		{
			for (auto it1 = it->begin(); it1 != it->end(); it1++)
			{
				auto pos = std::find(indices.begin(), indices.end(), *it1);
				if (pos != indices.end())
				{
					indices.erase(pos);
					indices.insert(indices.begin(), *it1);
				}
				else
				{
					indices.push_back(*it1);
				}					
			}
			
		}
	}

	auto it = symbols[exchange].begin();
	std::advance(it, index);

	for (int i = 0; i < 5; i++)
	{
		if (i >= indices.size())
			break;
		auto j = symbols[exchange].begin();
		std::advance(j, indices[i]);
		search->SetString(i, j->first);
		search->AutoComplete(NULL);
	}
	
}

void DashBoard::OnDropDown(wxCommandEvent& event)
{
	auto val = search->GetValue();
}

void DashBoard::OnTxtChangeInSearchBar1()
{
	int depth = searchDepth, index = 0, nextIndex = 0;
	std::string searchstr = searchBar->getValue();
	for (int i = 0; i < searchstr.length(); i++)
	{
		searchstr[i] = std::tolower(searchstr[i]);
	}
	std::string exchange = exchangeDropdown->GetValue().ToStdString();

	std::vector<std::string> wordList;

	std::stringstream ss(searchstr);
	std::string item;
	while (std::getline(ss, item, ' '))
	{
		wordList.push_back(item);
	}

	std::vector<int> indices;

	for (std::vector<std::string>::iterator word = wordList.begin(); word != wordList.end(); word++)
	{
		std::shared_ptr<Node> node;
		node = nodeTree[exchange];
		for (int x = 0; x < word->size(); x++)
		{
			char ch = word->at(x);
			if (!node->nodes.contains(ch))
			{
				break;
			}
			node = node->nodes[ch];
		}
		auto temp = indices;
		for (auto it = node->indices.begin(); it != node->indices.end(); it++)
		{
			for (auto it1 = it->begin(); it1 != it->end(); it1++)
			{
				auto pos = std::find(temp.begin(), temp.end(), *it1);
				if (pos != temp.end())
				{
					indices.erase(std::find(indices.begin(), indices.end(), *it1));
					indices.insert(indices.begin(), *it1);
				}
				else
				{
					indices.push_back(*it1);
				}
			}

		}
	}

	auto it = symbols[exchange].begin();
	std::advance(it, index);

	for (int i = 0; i < 5; i++)
	{
		if (i >= indices.size())
			break;
		auto j = symbols[exchange].begin();
		std::advance(j, indices[i]);
		searchBar->setString(i, j->first);
	}
}

void DashBoard::OnTxtEnterInSearchBar(wxCommandEvent& event)
{
	std::string value = search->GetValue().ToStdString();
	std::string exchange = exchangeDropdown->GetValue().ToStdString();
	auto it = symbols[exchange].find(value);
	if (it != symbols[exchange].end())
	{
		RefreshDashboard(it->first,it->second);
	}
}

void DashBoard::OnTxtEnterInSearchBar1()
{
	std::string value = searchBar->getValue();
	std::string exchange = exchangeDropdown->GetValue().ToStdString();
	auto it = symbols[exchange].find(value);
	if (it != symbols[exchange].end())
	{
		RefreshDashboard(it->first, it->second);
	}
}



