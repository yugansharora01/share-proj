#pragma once
#include <Poco/JSON/JSON.h>
#include <Poco/StreamCopier.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

class JsonParser
{
public:
	void parseFromFile(std::string filename,std::string targetFile);
private:
	Poco::JSON::Object::Ptr GetObjectPtr(Poco::JSON::Object::Ptr JsonObject, std::string Key);
	std::string GetValue(Poco::JSON::Object::Ptr JsonObject, std::string Key);
};

