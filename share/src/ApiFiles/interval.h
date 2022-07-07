#pragma once

enum Interval
{
    WEEKLY,
    MONTHLY,
    DAILY
};

std::string get_api_interval_value(int value);