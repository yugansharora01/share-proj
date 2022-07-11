#include "pch.h"
#include "JsonParser.h"

void JsonParser::parseFromFile(std::string filename, std::string targetFile)
{
	try 
	{
		std::ifstream file(filename);
		std::ostringstream ostr;
		Poco::StreamCopier::copyStream(file, ostr);
		std::string str = ostr.str();
		file.close();

		Poco::JSON::Parser Parser;
		// Parse the JSON and get the Results
		Poco::Dynamic::Var loParsedJson = Parser.parse(str);
		Poco::Dynamic::Var loParsedJsonResult = Parser.result();

		// Get the JSON Object
		Poco::JSON::Object::Ptr ptr = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();

		Poco::JSON::Array::Ptr arr = ptr->getArray("data");
		Poco::JSON::Object::Ptr ptr1 = arr->getObject(0);

		Poco::JSON::Array::Ptr arr1 = ptr1->getArray("quotes");
		std::ofstream f(targetFile);

		for (auto i = 0; i < arr1->size(); i++)
		{
			Poco::JSON::Object::Ptr p = arr1->getObject(i);
			std::string longName = GetValue(p, "longName");
			std::string name;
			if (longName == "")
				name = GetValue(p, "shortName");
			else
				name = longName;
			f << name << " --- " << GetValue(p,"symbol") <<"\n";

		}

		f.close();

	}
	catch (Poco::Exception& ex)
	{
		std::cerr << ex.displayText() << std::endl;
	}
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
	Poco::Dynamic::Var loVariable;
	std::string lsReturn;

	// Get the member Variable
	loVariable = JsonObject->get(Key);

	// Get the Value from the Variable
	lsReturn = loVariable.convert<std::string>();

	return lsReturn;
}
