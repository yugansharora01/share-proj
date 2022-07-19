#pragma once
#include <wx/wx.h>
#include <wx/srchctrl.h>
#include <wx/gbsizer.h>
#include <wx/slider.h>

class cMain : public wxFrame
{
public:
	wxStaticBitmap* image;
	wxComboBox* exchangeDropdown,*search;
	std::map<std::string, std::multimap<std::string, std::string>> symbols;
	std::map<std::string, std::multimap<std::string, int>> mapOfStrings;
public:
	cMain();
	~cMain();
	void RefreshDashboard(std::string companyName,std::string symbol);
	
public:
	void OnTxtChangeInSearchBar(wxCommandEvent& event);
	void OnTxtEnterInSearchBar(wxCommandEvent& event);
	
private:
	std::string getCurrentCompany();
	void createSymbolMap();
private:
	int searchDepth = 4;
	wxDECLARE_EVENT_TABLE();
};