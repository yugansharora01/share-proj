#pragma once
#include <wx/wx.h>

enum EVENT
{
	TEXT = 0,
	TEXT_ENTER,
	BUTTON_CLICK
};

class SearchBar : public wxPanel
{
public:
	wxPanel* m_parent;
public:
	SearchBar(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);
	void setList(std::vector<std::string> list);
	void setString(unsigned int n, std::string str);
	void setValue(std::string str);
	void setSize(wxSize size);
	std::string getValue();
	void BindEvent(EVENT evt, std::function<void()> func);
private:
	void OnSize(wxSizeEvent& event);
	void OnDropDown(wxCommandEvent& event);
	void OnText(wxCommandEvent& event);
	void OnTextEnter(wxCommandEvent& event);
	void OnClickingChoices(wxMouseEvent& event);
	void OnHoverOnChoices(wxMouseEvent& event);
	void OnLeavingChoices(wxMouseEvent& event);
	void OnButtonHover(wxMouseEvent& event);
	void OnButtonLeave(wxMouseEvent& event);
	void OnKillFocus(wxFocusEvent& event);
private:
	wxBitmapButton* btn;
	wxTextCtrl* textCtrl;
	wxSize windowSize;
	bool isDropDown = false;
	std::vector<wxStaticText*> dropdown;
	std::vector<std::string> options;
	std::map<EVENT, std::function<void()>> mapOfFunc;
};

