#pragma once
#include <vector>
#include <string>
#include <tuple>

class Date
{
public:
	Date();
	Date(unsigned int date, unsigned int month, unsigned int year);
	Date(std::string str);
	void SetDate(unsigned int date);
	void SetMonth(unsigned int month);
	void SetYear(unsigned int year);
	unsigned int GetDate();
	unsigned int GetMonth();
	unsigned int GetYear();
	void Set(unsigned int date, unsigned int month, unsigned int year);
	std::tuple<unsigned int, unsigned int, unsigned int> Get();
private:
	unsigned int m_date, m_month, m_year;
};
