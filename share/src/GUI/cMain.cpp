#include "pch.h"
#include "cMain.h"
#include "Util/JsonParser.h"

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

	searchBar = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxPoint(10, 10), wxSize(200, 30));
	searchBar->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &cMain::OnSearch,this);
	t = new wxTextCtrl(this, wxID_ANY, wxEmptyString,wxPoint(220,10), wxSize(20, 20));
	button = new wxButton(this, wxID_ANY, wxEmptyString, wxPoint(250, 10), wxSize(20, 20));
	button->Bind(wxEVT_BUTTON, &cMain::OnButton, this);

	searchBar->ShowSearchButton(true);
	/*wxGridBagSizer* sizer = new wxGridBagSizer();
	sizer->Add(searchBar,wxGBPosition(1,10),wxGBSpan(3,20), wxALL);
	sizer->Add(t,wxGBPosition(1,31),wxGBSpan(2,2), wxALL);
	sizer->Add(button,wxGBPosition(1,35),wxGBSpan(2,2), wxALL);
	sizer->Add(image,wxGBPosition(10,3),wxGBSpan(50,80), wxALL);
	this->SetSizer(sizer);*/
}

cMain::~cMain()
{
}

void cMain::RefreshDashboard(std::string name)
{
	JsonParser j;
	j.parseFromFile("src/Assets/symbols/INDIAData.json", "src/Assets/symbols/IndiaSymbols.txt");
	if (name != getCurrentCompany())
	{
		
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

void cMain::OnSearch(wxCommandEvent& event)
{
	RefreshDashboard(event.GetString().ToStdString());
}

void cMain::OnButton(wxCommandEvent& event)
{
	if (searchBar->IsSearchButtonVisible())
	{
		t->SetValue("visible");
	}
	else
	{
		t->SetValue("Not Visible");
		searchBar->ShowSearchButton(true);
	}
	searchBar->ShowSearchButton(true);
}


