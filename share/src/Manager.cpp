#include "pch.h"
#include "Manager.h"
#include "Prices.h"
#include "Util/Date.h"
#include "Util/Timer.h"

void Manager::make(std::string func, std::string symbol, std::string output)
{
	try 
	{
		Timer t;
		std::vector<std::string> vec = { "4. close","Date" };
		std::string priceFileDirectory = "src/Python/";
		std::string fileInfo = getRequiredName(func, symbol, output);
		std::string priceFileName = fileInfo + "-Price.txt";
		std::string priceFilePath = priceFileDirectory + priceFileName;
		
		if (!checkIfFileExists(priceFilePath))
		{
			Prices p;
			t.Mark();
			p.WritePriceInFile(func, symbol, output, priceFilePath, vec);
			std::cout << "Time taken to write in file : " << t.Mark() << std::endl;

			std::string destination = "src/Python/" + fileInfo + ".png";
			std::string command = "python src/Python/main.py " + priceFilePath + " " + destination;
			t.Mark();
			system(command.c_str());
			std::cout << "time taken to run python script : " << t.Mark() << std::endl;
		}
		
	}
	catch (Poco::Exception& ex)
	{
		std::cerr << ex.displayText() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
	}
	
	//https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=demo
	//https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY_EXTENDED&symbol=IBM&interval=15min&slice=year1month1&apikey=demo
	//XJ3TKS9LL55045VQ

}

bool Manager::checkIfFileExists(const std::string& filename)
{
	return std::filesystem::exists(filename);
}

std::string Manager::getRequiredName(std::string func, std::string symbol, std::string output)
{
	Date d;
	d.setAsTodayDate();
	std::string todaysDate = d.getAsString();
	if (output == "compact")
		output = "c";
	else
		output = "f"; // for full outputsize
	if (func == "TIME_SERIES_DAILY")
		func = "Daily";
	else
	{
		if (func == "TIME_SERIES_INTRADAY")
			func = "Intra";
	}
	std::string path = symbol + "-" + func + "-" + output + "-" + todaysDate;
	return path;
}


