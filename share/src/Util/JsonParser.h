#pragma once
#include <Poco/JSON/JSON.h>
#include <Poco/StreamCopier.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

class JsonParser
{
public:
	std::string parseFromFile(std::string filename,std::string targetFile);
	void GetMapofData(std::string filename, std::map<std::string, std::multimap<std::string, std::string>>& map);
private:
	Poco::Dynamic::Var parse(std::string filename);
	Poco::JSON::Object::Ptr GetObjectPtr(Poco::JSON::Object::Ptr JsonObject, std::string Key);
	std::string GetValue(Poco::JSON::Object::Ptr JsonObject, std::string Key);
};

