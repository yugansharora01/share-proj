#pragma once
class Manager
{
public:
	void make(std::string func, std::string symbol, std::string output);
	bool checkIfFileExists(const std::string& filename);
private:
	std::string getRequiredName(std::string func, std::string symbol, std::string output);
};

