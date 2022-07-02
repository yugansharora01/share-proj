#include "pch.h"
#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
/*EVT_BUTTON(10001, OnDiificultySubmit)
EVT_BUTTON(10002, OnNextQuestion)*/
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"App",wxPoint(100,100),wxSize(800,600), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	std::ifstream file;
	file.open("imageName.txt");
	std::string line;
	std::getline(file, line);
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);
	wxStaticBitmap* image;
	image = new wxStaticBitmap(this, wxID_ANY, wxBitmap(line, wxBITMAP_TYPE_PNG), wxPoint(50, 100), wxSize(100, 500));
}

cMain::~cMain()
{
}

