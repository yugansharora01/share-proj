#include "pch.h"
#include "Console.h"

wxTextCtrl* Console::text = nullptr;
std::vector<std::pair<LogType, std::string>> Console::vec;

Console::Console() : wxFrame(nullptr, wxID_ANY, "Logging Console", wxPoint(100, 100), wxSize(200, 200), wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN)
{
	text = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(200, 200), wxTE_MULTILINE);
}

Console::~Console()
{
	text->Destroy();
}

void Console::add(LogType type, std::string str)
{
	vec.push_back({ type,str });
	wxColour col;
	switch (type)
	{
	case WARNING_STRING:col = wxColour(165, 160, 80);
		break;
	case ERROR_STRING:col = wxColour(84, 28, 30);
		break;
	default:
		break;
	}
	text->SetDefaultStyle(wxTextAttr(col));
	text->AppendText(str + "\n");
}
