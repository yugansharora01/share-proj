#include "pch.h"
#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	/*EVT_BUTTON(10001, OnDiificultySubmit)
	EVT_BUTTON(10002, OnNextQuestion)*/
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr,wxID_ANY,"Game",wxPoint(100,100),wxSize(800,600), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	
}

cMain::~cMain()
{
}

