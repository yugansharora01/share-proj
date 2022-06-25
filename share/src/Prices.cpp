#include "pch.h"
#include "Prices.h"

Prices::Prices()
{
	std::ifstream file("src/Util/ApiKey.txt");
	std::getline(file, apiKey);
}

std::map<std::string, std::string>& Prices::GetPriceAsMap(std::string func, std::string symbol, std::string output)
{
	try
	{
		const Poco::JSON::Object::Ptr& loJsonObject = GetPrice(func, symbol, output);
		
		// Get the values for the member variables
		return GetAllValues(GetObjectPtr(loJsonObject, "Time Series (Daily)"), "4. close");
	}
	catch (Poco::Exception& ex)
	{
		std::cerr << ex.displayText() << std::endl;
	}
	
}

std::string Prices::GetValue(Poco::JSON::Object::Ptr aoJsonObject, std::string lsKey)
{
	Poco::Dynamic::Var loVariable;
	std::string lsReturn;

	// Get the member Variable
	loVariable = aoJsonObject->get(lsKey);

	// Get the Value from the Variable
	lsReturn = loVariable.convert<std::string>();

	return lsReturn;
}

std::map<std::string, std::string>& Prices::GetAllValues(Poco::JSON::Object::Ptr aoJsonObject, std::string key)
{
	std::map<std::string, std::string> m;

	// Get the member Variable
	for (auto i = aoJsonObject->begin(); i != aoJsonObject->end(); i++)
	{
		auto& obj = i->second.extract<Poco::JSON::Object::Ptr>();
		m.insert({ i->first, GetValue(obj, key) });
	}

	return m;
}

void Prices::WritePriceInFile(std::string func, std::string symbol, std::string output,std::string filename, std::vector<std::string> format)
{
	try
	{
		Poco::JSON::Object::Ptr loJsonObject = GetPrice(func, symbol, output);

		Poco::JSON::Object::Ptr ptr = GetObjectPtr(loJsonObject, "Time Series (Daily)");

		std::ofstream file(filename);

		for (auto i = ptr->begin(); i != ptr->end(); i++)
		{
			auto& obj = i->second.extract<Poco::JSON::Object::Ptr>();
			for (auto& j : format)
			{
				if (j != "Date")
					file << GetValue(obj, j) << " ";
				else
					file << i->first << " ";
			}
			file << "\n";
			
		}
	}
	catch (Poco::Exception& ex)
	{
		std::cerr << ex.displayText() << std::endl;
	}
}

Poco::JSON::Object::Ptr Prices::GetObjectPtr(Poco::JSON::Object::Ptr aoJsonObject, std::string lsKey)
{
	Poco::Dynamic::Var loVariable;

	// Get the member Variable
	loVariable = aoJsonObject->get(lsKey);

	// Get the Value from the Variable
	Poco::JSON::Object::Ptr ptr = loVariable.extract<Poco::JSON::Object::Ptr>();
	return ptr;

}

Poco::JSON::Object::Ptr Prices::GetPrice(std::string func, std::string symbol, std::string output)
{
	// prepare session
	Poco::URI uri("https://www.alphavantage.co/query?");
	uri.addQueryParameter("function", func);
	uri.addQueryParameter("symbol", symbol);
	uri.addQueryParameter("outputsize", output);
	uri.addQueryParameter("apikey", apiKey);
	const Poco::Net::Context::Ptr context = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
	Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), context);

	// prepare path
	std::string path(uri.getPathAndQuery());
	if (path.empty()) path = "/";

	// send request
	Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path);
	req.setKeepAlive(false);
	session.sendRequest(req);

	// get response
	Poco::Net::HTTPResponse res;

	std::istream& is = session.receiveResponse(res);
	std::ostringstream ostr;
	Poco::StreamCopier::copyStream(is, ostr);
	std::string str = ostr.str();

	Poco::JSON::Parser loParser;
	// Parse the JSON and get the Results
	Poco::Dynamic::Var loParsedJson = loParser.parse(str);
	Poco::Dynamic::Var loParsedJsonResult = loParser.result();

	// Get the JSON Object
	return loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();

}
