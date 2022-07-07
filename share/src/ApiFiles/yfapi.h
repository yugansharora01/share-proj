#pragma once

//#define CURL_STATICLIB
//#include "curl/curl.h"
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <stdio.h>

#include "interval.h"

namespace yfapi
{
    class YahooFinanceAPI
    {
    public:
        YahooFinanceAPI();
        void set_interval(Interval interval);
        void set_col_name(std::string col_name);
        //datatable::DataTable get_ticker_data(std::string ticker, std::string start_date, std::string end_date, bool keep_file = false);
        void get_ticker_data(std::string ticker, std::string start_date, std::string end_date, bool keep_file = false,std::string filename = "");
        std::string download_ticker_data(std::string ticker, std::string start_date, std::string end_date);

    private:
        std::string _base_url;
        Interval _interval;
        std::string _col_name;

        std::string build_url(std::string ticker, std::string start_date, std::string end_date);
        bool string_replace(std::string& str, const std::string from, const std::string to);
        std::string timestamp_from_string(std::string date);
        void download_file(std::string url, std::string filename);
    };

    
}
