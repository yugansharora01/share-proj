#pragma once
#include <wx/wx.h>
#include <wx/srchctrl.h>
#include <wx/gbsizer.h>

class cMain : public wxFrame
{
public:
	wxStaticBitmap* image;
	wxSearchCtrl* searchBar;
	wxTextCtrl* t;
	wxButton* button;
	
public:
	cMain();
	~cMain();
	void RefreshDashboard(std::string name);
	std::string getCurrentCompany();
public:
	void OnSearch(wxCommandEvent& event);
	void OnButton(wxCommandEvent& event);
	
private:
	
private:
	
	wxDECLARE_EVENT_TABLE();
};