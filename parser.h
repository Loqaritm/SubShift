#pragma once

#include <string>
#include "TimepointFormat.h"
#include <regex>
#include "cpp11format.h"
#include "stringUtils.h"


namespace SubShift {
using namespace StringUtils;

class Parser {
public:
    static bool parseLine(const std::string& line, std::pair<Timepoint, Timepoint>& startAndEndTime) {
        startAndEndTime = {}; //std::pair<Timepoint, Timepoint>();

        // TODO: This is for personal use of mine so I don't mind this being limited to just this specific format of .srt timestamps
        // but in the future this should probably be modified to accept and disregard whitespaces and so on (not sure if they are acceptable in proper .srt format)
        std::regex rgx("([0-9:,]+) --> ([0-9:,]+)");
        std::smatch matches;
        if (std::regex_search(line, matches, rgx)
            && matches.size() == 3) // Matches == 3, because the first one is matching all
        {
            startAndEndTime = std::pair<Timepoint, Timepoint>(Timepoint(matches[1]), Timepoint(matches[2]));
            return true;
        }

        return false;
    }

    static std::string getTimePointsString(std::pair<Timepoint, Timepoint>& startAndEndTime) {
        return string_format("%s --> %s", startAndEndTime.first.toString().c_str(), startAndEndTime.second.toString().c_str());  
    }

};

}