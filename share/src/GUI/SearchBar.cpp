#include "pch.h"
#include "SearchBar.h"

SearchBar::SearchBar(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
	:wxPanel(parent, id, pos, size, style, name)
{
	auto handler = wxImage::FindHandler(wxBITMAP_TYPE_PNG);
	if (!handler)
	{
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
	}
	std::string pathToIcon = "src/Assets/Icons/arrow-down-black.png";
	btn = new wxBitmapButton(this, wxID_ANY, wxBitmap(pathToIcon, wxBITMAP_TYPE_PNG), wxPoint(size.GetWidth() - 20, 0), wxSize(20, size.GetHeight()), wxBORDER_NONE);
	btn->Bind(wxEVT_BUTTON, &SearchBar::OnDropDown,this);
	btn->Bind(wxEVT_ENTER_WINDOW, &SearchBar::OnButtonHover,this);
	btn->Bind(wxEVT_LEAVE_WINDOW, &SearchBar::OnButtonLeave,this);
	
	textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(size.GetWidth() - 20, size.GetHeight()), wxTE_PROCESS_ENTER);
	textCtrl->Bind(wxEVT_TEXT, &SearchBar::OnText, this);
	textCtrl->Bind(wxEVT_TEXT_ENTER, &SearchBar::OnTextEnter, this);
	
	Bind(wxEVT_SIZE, &SearchBar::OnSize, this);
	Bind(wxEVT_KILL_FOCUS, &SearchBar::OnKillFocus, this);
	windowSize = size;
}

void SearchBar::setList(std::vector<std::string> list)
{
	size_t s = dropdown.size();

	if (dropdown.size() < list.size())
		dropdown.resize(list.size());


	for (auto j = 0; j < s; j++)
	{
		dropdown[j]->SetLabel(list[j]);
	}

	if (dropdown.size() > s)
	{
		for (auto j = s; j < dropdown.size(); j++)
		{
			dropdown[j] = new wxStaticText(this, wxID_ANY, list[j], wxPoint(0, (j + 1) * windowSize.GetHeight()), windowSize, wxST_ELLIPSIZE_END);
			dropdown[j]->Bind(wxEVT_LEFT_DOWN, &SearchBar::OnClickingChoices, this);
			dropdown[j]->Bind(wxEVT_ENTER_WINDOW, &SearchBar::OnHoverOnChoices, this);
			dropdown[j]->Bind(wxEVT_LEAVE_WINDOW, &SearchBar::OnLeavingChoices, this);
			wxFont font;
			font.SetPointSize(windowSize.GetHeight() - 10);
			dropdown[j]->SetFont(font);
		}
	}
	else
	{
		for (auto j = dropdown.size(); j < s; j++)
		{
			dropdown[j]->Destroy();
		}
	}

	options = list;
}

void SearchBar::setString(unsigned int n, std::string str)
{
	if (dropdown.size() > n)
	{
		dropdown[n]->SetLabel(str);
		options[n] = str;
	}
}

void SearchBar::setValue(std::string str)
{
	textCtrl->SetValue(str);
}

void SearchBar::setSize(wxSize size)
{
	windowSize = size;
	this->SetSize(size);
}

std::string SearchBar::getValue()
{
	return textCtrl->GetValue().ToStdString();
}

void SearchBar::BindEvent(EVENT evt, std::function<void()> func)
{
	mapOfFunc.insert({ evt,func });
}

void SearchBar::OnSize(wxSizeEvent& event)
{
	textCtrl->SetSize(windowSize.x - 20, windowSize.y);
}

void SearchBar::OnDropDown(wxCommandEvent& event)
{
	if (mapOfFunc.contains(EVENT::BUTTON_CLICK))
	{
		auto& func = mapOfFunc[EVENT::BUTTON_CLICK];
		func();
	}

	isDropDown = !isDropDown;

	if (isDropDown)
	{
		wxSize size(windowSize.GetWidth(), windowSize.GetHeight() + (dropdown.size() * windowSize.GetHeight()));
		this->SetSize(size);
	}
	else
	{
		this->SetSize(windowSize);
	}
}

void SearchBar::OnText(wxCommandEvent& event)
{
	if (mapOfFunc.contains(EVENT::TEXT))
	{
		auto& func = mapOfFunc[EVENT::TEXT];
		func();
	}
}

void SearchBar::OnTextEnter(wxCommandEvent& event)
{
	if (mapOfFunc.contains(EVENT::TEXT_ENTER))
	{
		auto& func = mapOfFunc[EVENT::TEXT_ENTER];
		func();
	}
}

void SearchBar::OnClickingChoices(wxMouseEvent& event)
{
	wxStaticText* s = (wxStaticText*)event.GetEventObject();
	textCtrl->SetValue(s->GetLabel());
}

void SearchBar::OnHoverOnChoices(wxMouseEvent& event)
{
	wxStaticText* s = (wxStaticText*)event.GetEventObject();
	s->SetForegroundColour(wxColour(*wxWHITE));
	s->SetBackgroundColour(wxColour(0, 120, 215));
	s->Refresh();
}

void SearchBar::OnLeavingChoices(wxMouseEvent& event)
{
	wxStaticText* s = (wxStaticText*)event.GetEventObject();
	s->SetForegroundColour(wxColour(*wxBLACK));
	s->SetBackgroundColour(wxColour(*wxWHITE));
	s->Refresh();
}

void SearchBar::OnButtonHover(wxMouseEvent& event)
{
	btn->SetWindowStyle(0);
}

void SearchBar::OnButtonLeave(wxMouseEvent& event)
{
	btn->SetWindowStyle(wxBORDER_NONE);
}

void SearchBar::OnKillFocus(wxFocusEvent& event)
{
	isDropDown = false;
	this->SetSize(windowSize);
}

