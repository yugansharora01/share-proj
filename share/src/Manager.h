#pragma once
class Manager
{
public:
	void make(std::string symbol, std::string startDate, std::string endDate);
	bool checkIfFileExists(const std::string& filename);
private:
	std::string getRequiredName(std::string symbol, std::string startDate, std::string endDate);
};

