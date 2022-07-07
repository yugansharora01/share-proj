#include "pch.h"
#include "interval.h"

static const std::string EnumAPIValues[]{ "1wk", "1mo", "1d" };

std::string get_api_interval_value(int value)
{
    return EnumAPIValues[value];
}