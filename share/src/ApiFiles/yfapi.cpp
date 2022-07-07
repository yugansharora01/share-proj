#include "pch.h"
#include "yfapi.h"
#include "interval.h"

namespace yfapi
{
    YahooFinanceAPI::YahooFinanceAPI()
    {
        this->_base_url =
            "https://query1.finance.yahoo.com/v7/finance/download/{ticker}?period1={start_time}&period2={end_time}&interval={interval}&events=history";
        this->_interval = DAILY;
        this->_col_name = "Open";
    }

    std::string YahooFinanceAPI::timestamp_from_string(std::string date)
    {
        struct std::tm time = { 0,0,0,0,0,0,0,0,0 };
        std::istringstream ss(date);
        ss >> std::get_time(&time, "%Y-%m-%d");
        if (ss.fail())
        {
            std::cerr << "ERROR: Cannot parse date string (" << date << "); required format %Y-%m-%d" << std::endl;
            exit(1);
        }
        time.tm_hour = 0;
        time.tm_min = 0;
        time.tm_sec = 0;
        std::time_t epoch = std::mktime(&time);

        return std::to_string(epoch);
    }

    bool YahooFinanceAPI::string_replace(std::string& str, const std::string from, const std::string to)
    {
        size_t start = str.find(from);
        if (start == std::string::npos)
        {
            return false;
        }
        str.replace(start, from.length(), to);
        return true;
    }

    std::string YahooFinanceAPI::build_url(std::string ticker, std::string start, std::string end)
    {
        std::string url = this->_base_url;
        string_replace(url, "{ticker}", ticker);
        string_replace(url, "{start_time}", timestamp_from_string(start));
        string_replace(url, "{end_time}", timestamp_from_string(end));
        string_replace(url, "{interval}", get_api_interval_value(this->_interval));
        return url;
    }


    void YahooFinanceAPI::set_interval(Interval interval)
    {
        this->_interval = interval;
    }

    void YahooFinanceAPI::set_col_name(std::string name)
    {
        this->_col_name = name;
    }

    void YahooFinanceAPI::download_file(std::string url, std::string filename)
    {
        //CURL* curl;
        //FILE* fp;
        //CURLcode res;
        //curl = curl_easy_init();
        //if (curl)
        //{
        //    fp = fopen(filename.c_str(), "wb");
        //    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        //    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        //    res = curl_easy_perform(curl);

        //    /* always cleanup */
        //    curl_easy_cleanup(curl);
        //    fclose(fp);
        //}

        // prepare session

        Poco::URI uri(url.c_str());
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
        std::ofstream file(filename);
        std::ostringstream ostr;
        Poco::StreamCopier::copyStream(is, file);
        //std::string str = ostr.str();
    }

    /*
     * Returns a DataTable containing data downloaded from YahooFinance.
     * By default this method will delete the tmp file created by the
     * download.
     */
     //datatable::DataTable YahooFinanceAPI::get_ticker_data(std::string ticker, std::string start, std::string end, bool keep_file)
    void YahooFinanceAPI::get_ticker_data(std::string ticker, std::string start, std::string end, bool keep_file, std::string filename)
    {
        std::string url = build_url(ticker, start, end);
        //datatable::DataTable dt;
        std::time_t now = std::time(0); // now
        if (filename == "")
            filename = ticker + "_" + std::to_string(now) + ".csv";
        if (!keep_file)
            filename = "tmp_" + filename;

        download_file(url, filename);
        //dt = datatable::DataTable(output_file_name, this->_col_name, true);

        if (!keep_file)
            std::remove(filename.c_str());
        //return dt;
    }

    /*
     * Downloads the historical stock data and returns the name of the file
     * created by the download.
     */
    std::string YahooFinanceAPI::download_ticker_data(std::string ticker, std::string start, std::string end)
    {
        std::string url = build_url(ticker, start, end);
        std::time_t now = std::time(0);
        std::string output_file_name = ticker + "_" + std::to_string(now) + ".csv";

        download_file(url, output_file_name);

        return output_file_name;
    }
}