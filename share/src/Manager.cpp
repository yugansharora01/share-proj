#include "pch.h"
#include "Manager.h"
#include "Util/Timer.h"
#include "ApiFiles/yfapi.h"

void Manager::make(std::string symbol, std::string startDate, std::string endDate)
{
	try 
	{
		std::string priceFileDirectory = "src/Assets/Graphs/";
		std::string fileInfo = getRequiredName(symbol,startDate,endDate);
		std::string priceFileName = fileInfo + "-Price.csv";
		std::string priceFilePath = priceFileDirectory + priceFileName;
		
		if (!checkIfFileExists(priceFilePath))
		{
			std::filesystem::path path = priceFileDirectory;
			path = path.parent_path();
			std::string fileToDelete;
			for (auto const& dir_entry : std::filesystem::directory_iterator{ path })
			{
				std::filesystem::path pathOfFile = std::filesystem::absolute(dir_entry);
				fileToDelete = pathOfFile.string();
				if (fileToDelete == fileInfo && pathOfFile.extension().string() != ".csv")
				{
					break;
				}
				fileToDelete = "";
			}
			yfapi::YahooFinanceAPI api;
			//TO DO: Throw error if unable to get data and exit this function with previous data displayed
			api.get_ticker_data(symbol, startDate, endDate, true, priceFilePath);
			std::filesystem::remove(fileToDelete);
			std::filesystem::remove(fileToDelete + "-Price.txt");
			std::string destination = priceFileDirectory + fileInfo + ".png";
			std::string command = "python src/Python/script.py " + priceFilePath + " " + destination;
			system(command.c_str());
			std::ofstream f("imageName.txt");
			f << destination;
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

}

bool Manager::checkIfFileExists(const std::string& filename)
{
	return std::filesystem::exists(filename);
}

std::string Manager::getRequiredName(std::string symbol, std::string startDate, std::string endDate)
{
	std::string str = symbol + "_" + startDate + "_" + endDate;
	return str;
}


