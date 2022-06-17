#include "pch.h"
#include "util.h"

Date::Date()
{
	m_date = 1;
	m_month = 1;
	m_year = 2000;
}

Date::Date(unsigned int date, unsigned int month, unsigned int year)
{
	Set(date, month, year);
}

Date::Date(std::string str)
{
	int n = 0;
	std::vector<unsigned int> vec;
	for (auto i = 0; i < str.size(); i++)
	{
		if (str[i] == '-')
		{
			std::string s = str.substr(n, i - 1);
			n = i;
			std::stringstream sstream(s);
			unsigned int val = 0;
			sstream >> val;
			vec.push_back(val);
		}
	}
	std::string s = str.substr(n, str.size() - 1);
	std::stringstream sstream(s);
	unsigned int val = 0;
	sstream >> val;
	vec.push_back(val);
	Set(vec[2], vec[1], vec[0]);
}

void Date::SetDate(unsigned int date)
{
	m_date = date;
}

void Date::SetMonth(unsigned int month)
{
	m_month = month;
}

void Date::SetYear(unsigned int year)
{
	m_year = year;
}

unsigned int Date::GetDate()
{
	return m_date;
}

unsigned int Date::GetMonth()
{
	return m_month;
}

unsigned int Date::GetYear()
{
	return m_year;
}

void Date::Set(unsigned int date, unsigned int month, unsigned int year)
{
	m_date = date;
	m_month = month;
	m_year = year;
}

std::tuple<unsigned int, unsigned int, unsigned int> Date::Get()
{
	return std::make_tuple(m_date,m_month,m_year);
}
