#pragma once
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

class Prices
{
public:
	std::map<std::string, std::string> GetPrice(std::string func, std::string symbol, std::string output);
	
	std::string GetValue(Poco::JSON::Object::Ptr aoJsonObject, std::string lsKey);

	std::map<std::string, std::string> GetAllValues(Poco::JSON::Object::Ptr aoJsonObject, std::string key);

	Poco::JSON::Object::Ptr GetObjectPtr(Poco::JSON::Object::Ptr aoJsonObject, std::string lsKey);
};

