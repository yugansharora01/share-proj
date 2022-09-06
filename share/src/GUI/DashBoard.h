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

class DashBoard : public wxFrame
{
public:
	SearchBar* searchBar;
	wxStaticBitmap* image;
	wxComboBox* exchangeDropdown,*search;
	std::map<std::string, std::multimap<std::string, std::string>> symbols;
	std::map<std::string, std::multimap<std::string, int>> mapOfStrings;
	std::map<std::string, std::shared_ptr<Node>> nodeTree;
public:
	DashBoard(wxWindow* console);
	~DashBoard();
	void RefreshDashboard(std::string companyName,std::string symbol);
	
public:
	void OnTxtChangeInSearchBar(wxCommandEvent& event);
	void OnDropDown(wxCommandEvent& event);
	void OnTxtChangeInSearchBar1();
	void OnTxtEnterInSearchBar(wxCommandEvent& event);
	void OnTxtEnterInSearchBar1();
	void OnClose(wxCloseEvent& event);

	
private:
	std::string getCurrentCompany();
	void createSymbolMap();
private:
	int searchDepth = 4;
	wxWindow* Console;
	wxDECLARE_EVENT_TABLE();
};