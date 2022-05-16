#pragma once

#include <string>
#include "TimepointFormat.h"
#include <regex>
#include "cpp11format.h"

namespace SubShift {

class Parser {
public:
    static bool parseLine(const std::string& line, std::pair<Timepoint, Timepoint>& startAndEndTime) {
        startAndEndTime = {}; //std::pair<Timepoint, Timepoint>();

        // TODO: This is for personal use of mine so I don't mind this being limited to just this specific format of .srt timestamps
        // but in the future this should probably be modified to accept and disregard whitespaces and so on (not sure if they are acceptable in proper .srt format)
        std::regex rgx("([0-9:,]+) --> ([0-9:,]+)");
        std::smatch matches;
        if (std::regex_search(line, matches, rgx)
            && matches.size() == 2)
        {
            startAndEndTime = std::pair<Timepoint, Timepoint>(Timepoint(matches[0]), Timepoint(matches[1]));
            return true;
        }
        return false;
    }

    static inline std::string intToPaddedString(int value, const size_t num, const char paddingChar = '0') {
        return paddedTo(std::to_string(value), num, paddingChar);
    }
    
    static inline std::string paddedTo(const std::string &str, const size_t num, const char paddingChar = ' ')
    {
        auto ret = str;
        if(num > str.size())
            ret.insert(0, num - str.size(), paddingChar);
    }

    static std::string getTimePointsString(std::pair<Timepoint, Timepoint>& startAndEndTime) {
        return string_format("{}:{}:{},{} --> {}:{}:{},{}", intToPaddedString(startAndEndTime.first.H, 2),
                                                          intToPaddedString(startAndEndTime.first.M, 2),
                                                          intToPaddedString(startAndEndTime.first.S, 2),
                                                          intToPaddedString(startAndEndTime.first.MS, 3),
                                                          intToPaddedString(startAndEndTime.second.H, 2),
                                                          intToPaddedString(startAndEndTime.second.M, 2),
                                                          intToPaddedString(startAndEndTime.second.S, 2),
                                                          intToPaddedString(startAndEndTime.second.MS, 3));  
    }

};

}