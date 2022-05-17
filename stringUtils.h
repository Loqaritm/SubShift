#pragma once
#include <string>

namespace SubShift {
namespace StringUtils {

std::string paddedTo(const std::string &str, const size_t num, const char paddingChar = ' ')
{
    auto ret = str;
    if(num > str.size())
        ret.insert(0, num - str.size(), paddingChar);
    return ret;
}

std::string intToPaddedString(int value, const size_t num, const char paddingChar = '0') {
    return paddedTo(std::to_string(value), num, paddingChar);
}

}
}