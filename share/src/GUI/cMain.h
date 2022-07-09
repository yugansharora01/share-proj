#pragma once
#include <wx/wx.h>
#include <wx/srchctrl.h>

class cMain : public wxFrame
{
public:
	wxStaticBitmap* image;
	wxSearchCtrl* searchBar;
	wxTextCtrl* t;
	
public:
	cMain();
	~cMain();
	void RefreshDashboard(std::string name);
	std::string getCurrentCompany();
public:
	void OnSearch(wxCommandEvent& event);
	
private:
	
private:
	
	wxDECLARE_EVENT_TABLE();
};