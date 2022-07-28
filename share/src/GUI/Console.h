#pragma once
#include <wx/wx.h>

enum LogType
{
	WARNING_STRING,
	ERROR_STRING
};

class Console : public wxFrame
{
public:
	static wxTextCtrl* text;
public:
	Console();
	~Console();
	static void add(LogType type,std::string str);
private:
	static std::vector<std::pair<LogType, std::string>> vec;
};

