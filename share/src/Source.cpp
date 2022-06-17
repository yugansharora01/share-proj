#include "pch.h"
#include "../vendor/matplotlib-cpp/matplotlib-cpp.h"
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <iostream>
#include <string>
#include <fstream>


std::string istreamToStr(std::istream &ifs)
{
    std::string s;
    size_t n = 0;
    ifs.read((char*)&n, 2);
    std::istream_iterator<char> isi(ifs), isiend;
    std::copy_n(isi, n, std::insert_iterator<std::string>(s, s.begin()));
    return s;
}

std::string GetValue(Poco::JSON::Object::Ptr aoJsonObject, std::string lsKey)
{
    Poco::Dynamic::Var loVariable;
    std::string lsReturn;

    // Get the member Variable
    //
    loVariable = aoJsonObject->get(lsKey);

    // Get the Value from the Variable
    //
    lsReturn = loVariable.convert<std::string>();

    return lsReturn;
}

std::map<std::string,std::string> GetAllValues(Poco::JSON::Object::Ptr aoJsonObject,std::string key)
{
    std::map<std::string, std::string> m;

    // Get the member Variable
    //
    for (auto i  = aoJsonObject->begin();i != aoJsonObject->end();i++)
    {
        std::cout << "Date :" << i->first <<" ";
        auto& obj = i->second.extract<Poco::JSON::Object::Ptr>();
        std::cout << "close :" << GetValue(obj, key) << std::endl;
        m.insert({ i->first, GetValue(obj, key) });
    }

    return m;
}

Poco::JSON::Object::Ptr GetObjectPtr(Poco::JSON::Object::Ptr aoJsonObject, std::string lsKey)
{
    Poco::Dynamic::Var loVariable;

    // Get the member Variable
    //
    loVariable = aoJsonObject->get(lsKey);

    // Get the Value from the Variable
    //
    return loVariable.extract<Poco::JSON::Object::Ptr>();

}

int main()
{
    try
    {
        // prepare session
        Poco::URI uri("https://www.alphavantage.co/query?");
        uri.addQueryParameter("function", "TIME_SERIES_DAILY");
        uri.addQueryParameter("symbol", "TATAPOWER.BSE");
        uri.addQueryParameter("outputsize", "compact");
        uri.addQueryParameter("apikey", "XJ3TKS9LL55045VQ");
        const Poco::Net::Context::Ptr context = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(),context);

        // prepare path
        std::string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        // send request
        Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path);
        req.setKeepAlive(false);
        session.sendRequest(req);

        // get response
        Poco::Net::HTTPResponse res;

        // print response
        std::istream& is = session.receiveResponse(res);
        std::cout << res.getStatus() << " " << res.getReason() << std::endl;
        std::ostringstream ostr;
        Poco::StreamCopier::copyStream(is, ostr);
        std::string str = ostr.str();

        Poco::JSON::Parser loParser;
        // Parse the JSON and get the Results
        Poco::Dynamic::Var loParsedJson = loParser.parse(str);
        Poco::Dynamic::Var loParsedJsonResult = loParser.result();

        // Get the JSON Object
        //
        Poco::JSON::Object::Ptr loJsonObject = loParsedJsonResult.extract<Poco::JSON::Object::Ptr>();

        // Get the values for the member variables
        //
        //
        std::cout << "Meta Data " << GetValue(GetObjectPtr(loJsonObject,"Time Series (Daily)"), "2022-04-22") << std::endl;

        auto m = GetAllValues(GetObjectPtr(loJsonObject, "Time Series (Daily)"),"4. close");
        
        for (auto i = m.begin(); i != m.end(); i++)
        {
            std::cout << "Date :" << i->first << " ";
            std::cout << "close :" << i->second << std::endl;
        }

    }
    catch (Poco::Exception& ex)
    {
        std::cerr << ex.displayText() << std::endl;
        return -1;
    }
    //https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=demo
    //https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY_EXTENDED&symbol=IBM&interval=15min&slice=year1month1&apikey=demo
    //XJ3TKS9LL55045VQ
    
    return 0;

}