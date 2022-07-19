#include "pch.h"
#include "JsonParser.h"

std::string JsonParser::parseFromFile(std::string filename, std::string targetFile)
{
	int i;
	try 
	{
		Poco::Dynamic::Var ParsedJsonResult = parse(filename);

		// Get the JSON Object
		Poco::JSON::Object::Ptr ptr = ParsedJsonResult.extract<Poco::JSON::Object::Ptr>();

		Poco::JSON::Array::Ptr arr = ptr->getArray("data");
		Poco::JSON::Object::Ptr ptr1 = arr->getObject(0);

		Poco::JSON::Array::Ptr arr1 = ptr1->getArray("quotes");
		std::ofstream f(targetFile);

		Poco::JSON::Array::Ptr warr = new Poco::JSON::Array;
		std::ostringstream ss;

		for (i = 0; i < arr1->size(); i++)
		{
			Poco::JSON::Object::Ptr p = arr1->getObject(i);
			std::string longName = GetValue(p, "longName");
			std::string name;
			if (longName == "")
				name = GetValue(p, "shortName");
			else
				name = longName;
			if (name.size() == 0)
			{
				std::cout << "LOL";
			}
			std::string symbolofCompany = GetValue(p, "symbol");
			Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
			std::string exchange = GetValue(p, "exchange");
			json->set(name, symbolofCompany);
			json->set("exchange", exchange);
			warr->set(i,json);

		}
		Poco::JSON::Stringifier::stringify(warr, ss, 4, -1, Poco::JSON_PRESERVE_KEY_ORDER);
		f << ss.str();

		f.close();
		return "OK";

	}
	catch (Poco::Exception& ex)
	{
		return ex.displayText();
	}
}

void JsonParser::GetMapofData(std::string filename, std::map<std::string, std::multimap<std::string, std::string>>& map)
{
	try
	{
		Poco::Dynamic::Var ParsedJsonResult = parse(filename);
		Poco::JSON::Array::Ptr arr = ParsedJsonResult.extract<Poco::JSON::Array::Ptr>();

		for (int i = 0; i < arr->size(); i++)
		{
			Poco::JSON::Object::Ptr p = arr->getObject(i);
			
			std::string symbol = p->begin()->second.convert<std::string>();
			for (int i = 0; i < symbol.length(); i++)
			{
				symbol[i] = std::tolower(symbol[i]);
			}

			std::string companyName = p->begin()->first;

			for (int i = 0; i < companyName.length(); i++)
			{
				companyName[i] = std::tolower(companyName[i]);
			}

			std::string exchange = GetValue(p,"exchange");
			map[exchange].insert({ companyName,symbol });
		}

	}
	catch (Poco::Exception& ex)
	{
		std::cerr << ex.displayText();
	}
	catch (const std::exception& e)
	{
	}
	
}

Poco::Dynamic::Var JsonParser::parse(std::string filename)
{
	std::ifstream file(filename);
	std::ostringstream ostr;
	Poco::StreamCopier::copyStream(file, ostr);
	std::string str = ostr.str();
	file.close();

	Poco::JSON::Parser Parser;
	// Parse the JSON and get the Results
	Poco::Dynamic::Var ParsedJson = Parser.parse(str);
	return Parser.result();
}

Poco::JSON::Object::Ptr JsonParser::GetObjectPtr(Poco::JSON::Object::Ptr JsonObject, std::string Key)
{
	Poco::Dynamic::Var Variable;

	// Get the member Variable
	Variable = JsonObject->get(Key);

	// Get the Value from the Variable
	Poco::JSON::Object::Ptr ptr = Variable.extract<Poco::JSON::Object::Ptr>();
	return ptr;

}

std::string JsonParser::GetValue(Poco::JSON::Object::Ptr JsonObject, std::string Key)
{
	try
	{
		Poco::Dynamic::Var loVariable;
		std::string lsReturn;

		// Get the member Variable
		loVariable = JsonObject->get(Key);

		// Get the Value from the Variable
		lsReturn = loVariable.convert<std::string>();

		return lsReturn;
	}
	catch (Poco::Exception& ex)
	{
		std::cerr << ex.displayText();
		return std::string();
	}
	
}
