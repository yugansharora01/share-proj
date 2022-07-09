#include "pch.h"
#include "cMain.h"
#include "wx/xrc/xmlres.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"App",wxPoint(100,100),wxSize(800,600), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	wxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
	wxSizer* hsizer = new wxBoxSizer(wxHORIZONTAL);
	wxSizer* hsizer2 = new wxBoxSizer(wxHORIZONTAL);
	std::ifstream file;
	file.open("imageName.txt");
	std::string line;
	std::getline(file, line);
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(line, wxBITMAP_TYPE_PNG), wxPoint(50, 100), wxSize(100, 500));

	searchBar = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 20), wxSize(20, 100));
	searchBar->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &cMain::OnSearch,this);
	t = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(100, 50), wxSize(20, 20));
	
	hsizer->Add(searchBar, wxEXPAND | wxALL);
	hsizer->Add(t, wxEXPAND | wxALL);
	hsizer2->Add(image, wxEXPAND | wxALL);

	vsizer->Add(hsizer);
	vsizer->Add(hsizer2);
	this->SetSizer(vsizer);
}

cMain::~cMain()
{
}

void cMain::RefreshDashboard(std::string name)
{
	t->SetValue(name);
}

std::string cMain::getCurrentCompany()
{
	std::ifstream file;
	file.open("imageName.txt");
	std::string line;
	std::getline(file, line);
	std::filesystem::path p(line);
	line = p.filename().string();


	return std::string();
}

void cMain::OnSearch(wxCommandEvent& event)
{
	RefreshDashboard(event.GetString().ToStdString());
}


