#pragma once
#include <wx/wx.h>
#include <wx/srchctrl.h>
#include <wx/gbsizer.h>
#include <wx/slider.h>
#include "SearchBar.h"

struct Node
{
	std::string str;
public:
	std::map<char, std::shared_ptr<Node>> nodes;
	std::vector<std::vector<int>> indices;
public:
	Node() = default;
	Node(std::string string)
	{
		setChar(string);
	}
	void setChar(std::string string)
	{
		str = string;
	}
};

class cMain : public wxFrame
{
public:
	SearchBar* searchBar;
	wxStaticBitmap* image;
	wxComboBox* exchangeDropdown,*search;
	std::map<std::string, std::multimap<std::string, std::string>> symbols;
	std::map<std::string, std::multimap<std::string, int>> mapOfStrings;
	std::map<std::string, std::shared_ptr<Node>> nodeTree;
public:
	cMain();
	~cMain();
	void RefreshDashboard(std::string companyName,std::string symbol);
	
public:
	void OnTxtChangeInSearchBar(wxCommandEvent& event);
	void OnDropDown(wxCommandEvent& event);
	void OnTxtChangeInSearchBar1();
	void OnTxtEnterInSearchBar(wxCommandEvent& event);
	void OnTxtEnterInSearchBar1();

	
private:
	std::string getCurrentCompany();
	void createSymbolMap();
private:
	int searchDepth = 4;
	wxDECLARE_EVENT_TABLE();
};